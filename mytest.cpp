#include <cassert>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>
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
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 66); // define the range
    PairingPQ<int> v;
    return 0;
}


//vector<int> v;
//SortedPQ<int> pq(v.begin(),v.end());
//for (int i = 0; i < 10; ++i) {
//int a = distr(gen);
//cout << a << " ";
//v.push_back(a);
//pq.push(a);
//}
//cout << endl;
//
//while(!pq.empty()){
//cout << pq.top() << ' ';
//pq.pop();
}