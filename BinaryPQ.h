// Project identifier: 0E04A31E0D60C01986ACB20081C9D8722A1899B6

#ifndef BINARYPQ_H
#define BINARYPQ_H


#include <algorithm>
#include "Eecs281PQ.h"

// A specialized version of the priority queue ADT implemented as a binary
// heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Description: Construct an empty PQ with an optional comparison functor.
    // Runtime: O(1)
    explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function, or verify that it is already done

        /// already done
    } // BinaryPQ


    // Description: Construct a PQ out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp },data{ start, end } {
        // TODO: Implement this function
        heapify();
    } // BinaryPQ

    /// DEBUG FUNCTION
    BinaryPQ(const std::vector<TYPE>& v, COMP_FUNCTOR comp = COMP_FUNCTOR()):
        BaseClass{ comp } {
            std::vector<TYPE> temp(v.begin(),v.end());
            data = temp;
            heapify();
        }



    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automatically.
    virtual ~BinaryPQ() {
    } // ~BinaryPQ()


    // Description: Assumes that all elements inside the heap are out of
    //              order and 'rebuilds' the heap by fixing the heap
    //              invariant.
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        heapify();
    } // updatePriorities()


    // Description: Add a new element to the PQ.
    // Runtime: O(log(n))
    virtual void push(const TYPE &val) {
        // TODO: Implement this function.
        data.push_back(val);
        fixUp(data.size());
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the PQ.
    // Note: We will not run tests on your code that would require it to pop
    //       an element when the PQ is empty. Though you are welcome to if
    //       you are familiar with them, you do not need to use exceptions in
    //       this project.
    // Runtime: O(log(n))
    virtual void pop() {
        // TODO: Implement this function.
        std::swap(getElement(1), getElement(data.size()));
        data.pop_back();
        fixDown(1);
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the PQ. This should be a reference for speed. It MUST
    //              be const because we cannot allow it to be modified, as
    //              that might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function.
        return data[0];
    } // top()


    // Description: Get the number of elements in the PQ.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function. Might be very simple,
        return data.size();
    } // size()


    // Description: Return true if the PQ is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        // TODO: Implement this function. Might be very simple,
        return data.empty();
    } // empty()


private:
    // Note: This vector *must* be used for your PQ implementation.
    std::vector<TYPE> data;
    // NOTE: You are not allowed to add any member variables. You don't need
    //       a "heapSize", since you can call your own size() member
    //       function, or check data.size().

    // TODO: Add any additional member functions you require here. For
    //       instance, you might add fixUp() and fixDown().

    // Utility: getElement, O(1)
    const TYPE &getElement(size_t idx) const{
        return data[idx - 1];
    }
    TYPE &getElement(size_t idx){
        return data[idx - 1];
    }

    // FixDown, O(log n)
    void fixDown(size_t idx){
        while( idx * 2 <= data.size() ){
            size_t j = idx * 2;
            if ( j < data.size() && this->compare(getElement(j),getElement(j+1)) )
                j++;
            if ( this->compare(getElement(j),getElement(idx)) )
                break;
            std::swap(getElement(idx), getElement(j));
            idx = j;
        }
    }

    // FixUp, O(log n)
    void fixUp(size_t idx){
        while( idx > 1 && this->compare(getElement(idx / 2), getElement(idx))){
            std::swap(getElement(idx), getElement(idx / 2));
            idx /= 2;
        }
    }

    // heapify, O(n)
    void heapify(){
        for(size_t idx = data.size(); idx >= 1 ; idx -- ){
            // continue at leaf node
            if (idx * 2 > data.size())
                continue;
            fixDown(idx);
        }
    }

}; // BinaryPQ


#endif // BINARYPQ_H
