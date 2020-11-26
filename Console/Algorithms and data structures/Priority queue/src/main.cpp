#include <iostream>

#include "Queue.hpp"

using namespace std;


int main() {
    cout << "Priority queue - simple usage" << endl;
    PriorityQueue<int> queue {1,2,3,4,5,6,7,8,9,10};

    cout << "queue size: "<<queue.size() << "\n\n";

    while(!queue.isEmpty()){
        cout << queue.top() << ", ";
        queue.pop();
    } 
    
    queue.push(22);
    cout << "\n\nqueue size: "<<queue.size() << "\n\n";
}