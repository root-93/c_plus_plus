#include <iostream>
#include <aliases.h>
#include "Queue.hpp"

using namespace std;


int main() {
    cout << "Priority queue - simple usage" << endl;
    PriorityQueue<int> queue {5,3,6,4,7,2,8,1,10,0};
    

    cout << "queue size: "<<queue.size() << "\n\n";

    while(!queue.isEmpty()){
        cout << queue.top() << ", ";
        queue.pop();
    } 
    
    queue.push(22);
    cout << "\n\nqueue size: "<<queue.size() << "\n\n";
}