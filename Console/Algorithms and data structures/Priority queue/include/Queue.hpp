#pragma once
#include <vector>
#include <functional>
#include <initializer_list>
#include <exception>
#include <algorithm>

template <class T, class Compare = std::less<typename std::vector<T>::value_type>>

class PriorityQueue{
        typedef typename std::vector<T>::value_type valueType;
        typedef typename std::vector<T>::size_type sizeType;
        typedef typename std::vector<T>::reference reference;
        typedef typename std::vector<T>::const_reference constReference;

    public:
                        PriorityQueue(){}
                        PriorityQueue(std::initializer_list<T> init) : _data{init} {};
                        ~PriorityQueue(){}
        void            push(valueType const &value) {
                            _data.push_back(value);
                            std::make_heap(std::begin(_data), std::end(_data), _comparer);
                        };
        void            pop(){
                            std::pop_heap(std::begin(_data), std::end(_data), _comparer);
                            _data.pop_back();
                        };  
        constReference  top()const {return _data.front();}

        void            swap(PriorityQueue &other) noexcept{
                            swap(_data, other._data);
                            swap(_comparer, other._comparer);
                        }
        size_t          size()const noexcept {return _data.size();}
        bool            isEmpty()const noexcept {return _data.empty();}

    private:
        std::vector<T>  _data;
        Compare         _comparer;
};



template <class T, class Compare>
void swap(PriorityQueue<T, Compare> &lhs, 
          PriorityQueue<T, Compare> &rhs) 
          noexcept(noexcept(lhs.swap(rhs))){
    lhs.swap(rhs);
}