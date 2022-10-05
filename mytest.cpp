#include <cassert>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "BinaryPQ.h"
#include "Eecs281PQ.h"
#include "PairingPQ.h"
#include "SortedPQ.h"
#include "UnorderedPQ.h"
using namespace std;
struct IntPtrComp {
    bool operator()(int const* a, int const* b) const { return *a < *b; }
};


int main(){
    SortedPQ<int> pq;
    pq.push(1);
    pq.push(3);
    pq.push(6);
    pq.push(2);
    pq.push(5);
    while(!pq.empty()){
        cout << pq.top() << ' ';
        pq.pop();
    }
    cout << endl;
    vector<int> v;
    for (int i = 0; i < 16; ++i) {
        pq.push(i);
        v.push_back(i);
    }
    while(!pq.empty()){
        cout << pq.top() << ' ';
        pq.pop();
    }

    SortedPQ<int> myq(v.begin(),v.end());
    while(!pq.empty()){
        cout << pq.top() << ' ';
        pq.pop();
    }
    return 0;
}

