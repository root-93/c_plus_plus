#include <algorithm>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <limits>
#include <map>

template <typename K, typename V>
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;

public:
    std::map<K, V> m_map;
    // constructor associates whole range of K with val
    interval_map(V const& val) : m_valBegin(val) {}

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.

    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        // validation ==========================================
        if (not(keyBegin < keyEnd)) {
            return;
        }

        // insert end element (in a special case first)=========
        const auto lowerBound{m_map.lower_bound(keyBegin)};

        if (m_map.empty() or (lowerBound == m_map.cend())) {
            if (not(val == m_valBegin)) {
                m_map.emplace(keyBegin, val);
                m_map.emplace(keyEnd, m_valBegin);
            }
            return;
        }

        // insert beginKey =====================================
        auto current{m_map.begin()};
        V currentValue{m_valBegin};

        if (lowerBound == m_map.cbegin()) {
            if (not(val == m_valBegin)) {
                currentValue = lowerBound->second;
                current = m_map.insert_or_assign(keyBegin, val).first;
            }
        }
		else {
            const auto prev{std::prev(lowerBound)};

            if (not(prev->second == val)) {
                currentValue = prev->second;
                current = m_map.insert_or_assign(keyBegin, val).first;
            } else {
                currentValue = prev->second;
                current = prev;
            }
        }

        // erase intervals in scope =============================        
		if (current->second == val) {
			std::advance(current, 1);
        }
        while (current != m_map.cend() and current->first < keyEnd) {
            currentValue = current->second;
            current = m_map.erase(current);
        }

        // insert keyEnd ========================================
        if (current == m_map.cend() and not m_map.empty()) {
            m_map.emplace(keyEnd, m_valBegin);
        } else if (keyEnd < current->first) {
            if (not(currentValue == val)) {
                m_map.emplace(keyEnd, currentValue);
            }
        } else {
            if ((val == current->second)) {
                m_map.erase(current);
            }
        }
    }

    // look-up of the value associated with key
    V const& operator[](K const& key) const {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin()) {
            return m_valBegin;
        } else {
            return (--it)->second;
        }
    }
    auto size() { return m_map.size(); }
    auto& get() { return m_map; }
    void clear() { m_map.clear(); }
};

void print(interval_map<int, char>& map) {
    std::cout << "size[" << map.m_map.size() << "] current data:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "[" << i << ":" << map[i] << "]";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

class IntervalMapTest : public ::testing::Test {
public:
    void SetUp() override {}

    void TearDown() override { map.clear(); }

protected:
    interval_map<int, char> map{'A'};
};

TEST_F(IntervalMapTest, addFirstValidElement) {
    std::map<int, char> expected{{3, 'B'}, {5, 'A'}};
    map.assign(3, 5, 'B');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, addFirstInvalidElement) {
    std::map<int, char> expected{};
    map.assign(3, 5, 'A');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, addInvalidScopeToEmptyMap) {
    std::map<int, char> expected{};
    map.assign(3, 3, 'B');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, addInvalidScopeToNotEmptyMap) {
    std::map<int, char> expected{{3, 'B'}, {5, 'A'}};
    map.assign(3, 5, 'B');
    map.assign(8, 8, 'C');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, addTwoElementsInDifferentScopes) {
    std::map<int, char> expected{{3, 'B'}, {5, 'A'}, {6, 'C'}, {8, 'A'}};
    map.assign(3, 5, 'B');
    map.assign(6, 8, 'C');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, addTheSameValueTwice) {
    std::map<int, char> expected{{3, 'B'}, {5, 'A'}};
    map.assign(3, 5, 'B');
    map.assign(3, 5, 'B');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, addTwoDifferentElementsInTheSameScope) {
    std::map<int, char> expected{{3, 'C'}, {5, 'A'}};
    map.assign(3, 5, 'B');
    map.assign(3, 5, 'C');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, addSecondDifferentElementsWithTheSameKeyBeginAndHigherEnd) {
    std::map<int, char> expected{{3, 'C'}, {8, 'A'}};
    map.assign(3, 5, 'B');
    map.assign(3, 8, 'C');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, addSecondDifferentElementsWithTheSameKeyBeginAndLowerEnd) {
    std::map<int, char> expected{{3, 'C'}, {5, 'B'}, {8, 'A'}};
    map.assign(3, 8, 'B');
    map.assign(3, 5, 'C');
    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, addSecondDifferentElementsWithLowerKeyBeginAndLowerEnd) {
    std::map<int, char> expected{{2, 'C'}, {5, 'B'}, {8, 'A'}};
    map.assign(3, 8, 'B');
    map.assign(2, 5, 'C');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, addSecondDifferentElementsIntTheMiddle) {
    std::map<int, char> expected{{3, 'B'}, {5, 'C'}, {6, 'B'}, {9, 'A'}};
    map.assign(3, 9, 'B');
    map.assign(5, 6, 'C');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, addSecondSameElementsIntTheMiddle) {
    std::map<int, char> expected{{3, 'B'}, {9, 'A'}};
    map.assign(3, 9, 'B');
    map.assign(5, 6, 'B');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, addbegginValueAsFirstToNotEmptyMap) {
    std::map<int, char> expected{{4, 'B'}, {5, 'C'}, {7, 'D'}, {8, 'A'}};
    map.assign(3, 6, 'B');
    std::map<int, char> expected1{{3, 'B'}, {6, 'A'}};
    EXPECT_EQ(map.get(), expected1);

    map.assign(5, 7, 'C');
    std::map<int, char> expected2{{3, 'B'}, {5, 'C'}, {7, 'A'}};
    EXPECT_EQ(map.get(), expected2);

    map.assign(7, 8, 'D');
    std::map<int, char> expected3{{3, 'B'}, {5, 'C'}, {7, 'D'}, {8, 'A'}};
    EXPECT_EQ(map.get(), expected3);

    map.assign(2, 4, 'A');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, ClearNotEmptyMapWithBeginValue) {
    std::map<int, char> expected{};
    map.assign(3, 6, 'B');
    map.assign(5, 7, 'C');
    map.assign(7, 8, 'D');
    map.assign(3, 8, 'A');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, ClearNotEmptyMapWithBeginValueBegin) {
    std::map<int, char> expected{};
    map.assign(3, 6, 'B');
    map.assign(5, 7, 'C');
    map.assign(7, 8, 'B');
    map.assign(3, 10, 'A');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, ClearNotEmptyMapWithBeginValueEnd) {
    std::map<int, char> expected{};
    map.assign(3, 6, 'B');
    map.assign(3, 5, 'C');
    map.assign(8, 9, 'D');
    map.assign(-1, 9, 'A');

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, RandonTest1) {

    map.assign(3, 4, 'B');
    std::map<int, char> expected1{{3, 'B'}, {4, 'A'}};
    EXPECT_EQ(map.get(), expected1);
    map.assign(6, 8, 'C');
    std::map<int, char> expected2{{3, 'B'}, {4, 'A'}, {6, 'C'}, {8, 'A'}};
    EXPECT_EQ(map.get(), expected2);
    map.assign(4, 6, 'D');
    std::map<int, char> expected3{{3, 'B'}, {4, 'D'}, {6, 'C'}, {8, 'A'}};
    EXPECT_EQ(map.get(), expected3);
    map.assign(2, 6, 'B');
    std::map<int, char> expected4{{2, 'B'}, {6, 'C'}, {8, 'A'}};
    EXPECT_EQ(map.get(), expected4);
    map.assign(2, 6, 'B');
    std::map<int, char> expected5{{2, 'B'}, {6, 'C'}, {8, 'A'}};
    EXPECT_EQ(map.get(), expected5);
    map.assign(3, 7, 'A');
    std::map<int, char> expected6{{2, 'B'}, {3, 'A'}, {7, 'C'}, {8, 'A'}};
    EXPECT_EQ(map.get(), expected6);
    map.assign(7, 9, 'E');
    std::map<int, char> expected{{2, 'B'}, {3, 'A'}, {7, 'E'}, {9, 'A'}};

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

TEST_F(IntervalMapTest, RandonTest2) {

    map.assign(3, 8, 'B');
    std::map<int, char> expected1{{3, 'B'}, {8, 'A'}};
    EXPECT_EQ(map.get(), expected1);
    map.assign(4, 7, 'C');
    std::map<int, char> expected2{{3, 'B'}, {4, 'C'}, {7, 'B'}, {8, 'A'}};
    EXPECT_EQ(map.get(), expected2);
    map.assign(3, 4, 'B');
    std::map<int, char> expected3{{3, 'B'}, {4, 'C'}, {7, 'B'}, {8, 'A'}};
    EXPECT_EQ(map.get(), expected3);
    map.assign(4, 7, 'B');
    std::map<int, char> expected4{{3, 'B'}, {8, 'A'}};
    EXPECT_EQ(map.get(), expected4);
    map.assign(3, 8, 'C');
    std::map<int, char> expected5{{3, 'C'}, {8, 'A'}};
    EXPECT_EQ(map.get(), expected5);
    map.assign(2, 3, 'A');
    std::map<int, char> expected6{{3, 'C'}, {8, 'A'}};
    EXPECT_EQ(map.get(), expected6);
    map.assign(3, 8, 'A');
    std::map<int, char> expected{};

    EXPECT_EQ(map.size(), expected.size());
    EXPECT_EQ(map.get(), expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}