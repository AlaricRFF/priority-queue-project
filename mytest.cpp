#include <cassert>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>
#include "Eecs281PQ.h"
#include "PairingPQ.h"
using namespace std;
struct IntPtrComp {
    bool operator()(int const* a, int const* b) const { return *a < *b; }
};


int main(){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 6666); // define the range
    vector<int> v;
    for (int i = 0; i < 10000; ++i) {
        int a = distr(gen);
        cout << a << " ";
        v.push_back(a);
    }
//    v.push_back(10);
//    v.push_back(1);
//    v.push_back(12);
//    v.push_back(9);
//    v.push_back(10);
    cout << endl;
    PairingPQ<int> pairing(v.begin(),v.end());
    int smaller, bigger;
    bigger = pairing.top();
    cout << bigger << ' ';
    pairing.pop();
    while(!pairing.empty()){
        smaller = pairing.top();
        if (bigger < smaller){
            cerr << "wrong ans!\n";
            exit(9);
        }
        cout << pairing.top() << ' ';
        pairing.pop();
        bigger = smaller;
    }
    cout << endl;
    bigger = v.back();
    v.pop_back();
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
