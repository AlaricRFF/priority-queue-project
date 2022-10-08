// Project identifier: 0E04A31E0D60C01986ACB20081C9D8722A1899B6

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>

// A specialized version of the priority queue ADT implemented as a pairing
// heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node {
        public:
            // TODO: After you add add one extra pointer (see below), be sure
            //       to initialize it here.
            explicit Node(const TYPE &val)
                : elt{ val }, child{ nullptr }, sibling{ nullptr }, previous{ nullptr }
            {}

            // Description: Allows access to the element at that Node's
            //              position. There are two versions, getElt() and a
            //              dereference operator, use whichever one seems
            //              more natural to you.
            // Runtime: O(1) - this has been provided for you.
            const TYPE &getElt() const { return elt; }
            const TYPE &operator*() const { return elt; }

            // The following line allows you to access any private data
            // members of this Node class from within the PairingPQ class.
            // (ie: myNode.elt is a legal statement in PairingPQ's add_node()
            // function).
            friend PairingPQ;

        private:
            TYPE elt;
            Node *child;
            Node *sibling;
            Node *previous;
    }; // Node


    // Description: Construct an empty pairing heap with an optional
    //              comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }{
        // TODO: Implement this function.
        this->root = nullptr;
        this->count = 0;
    }; // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function.
        for(auto i = start; i != end; i++){
            this->push(*i);
        }
//        std::deque<TYPE> storage(start,end);
//        while(!storage.empty()){
//            this->push(storage.front());
//            storage.pop_front();
//        }
    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) :
        BaseClass{ other.compare } {
        // TODO: Implement this function.
        std::deque<Node *> dest;
        if (!other.root) return; /// if 'other' is empty, return directly
        dest.push_back(other.root);
        while(!dest.empty()){
            Node *cur = dest.front();
            dest.pop_front();
            if (cur->child)
                dest.push_back(cur->child);
            if (cur->sibling)
                dest.push_back(cur->sibling);
            Node *newNode = new Node(cur->elt);
            this->push(newNode);
        }

    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ &operator=(const PairingPQ &rhs) {
        // TODO: Implement this function.
        PairingPQ<TYPE> temp(rhs);
        this->compare = rhs.compare;
        std::swap(this->count,temp.count);
        std::swap(this->root,temp.root);
        return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        // TODO: Implement this function.
        if (!root) return; /// pitfall happens here !!!
        std::deque<Node *> dest;
        dest.push_back(root);
        while(!dest.empty()){
            Node *cur = dest.front();
            dest.pop_front();
            if (cur->child)
                dest.push_back(cur->child);
            if (cur->sibling)
                dest.push_back(cur->sibling);
            delete cur;
        }
        root = nullptr;
        count = 0;
    } // ~PairingPQ()


    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant. You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        if (!root) return; /// no element, return
        /// during the whole process, count doesn't change !!!
        Node *oddRoot = root;
        root = nullptr;
        std::deque<Node*> dest;
        dest.push_back(oddRoot);
        while(!dest.empty()){
            Node *cur = dest.front();
            dest.pop_front();
            if (cur->child)
                dest.push_back(cur->child);
            if (cur->sibling)
                dest.push_back(cur->sibling);
            cur->sibling = cur->child = cur->previous = nullptr;
            root = meld(root,cur);
        }
    } // updatePriorities()


    // Description: Add a new element to the pairing heap. This is already
    //              done. You should implement push functionality entirely in
    //              the addNode() function, and this function calls
    //              addNode().
    // Runtime: O(1)
    virtual void push(const TYPE &val) {
        addNode(val);
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the pairing heap.
    // Note: We will not run tests on your code that would require it to pop
    //       an element when the pairing heap is empty. Though you are
    //       welcome to if you are familiar with them, you do not need to use
    //       exceptions in this project.
    // Runtime: Amortized O(log(n))
    // TODO: make sure when the heap is empty, the root is a nullptr
    virtual void pop() {
        // TODO: Implement this function.
        std::deque<Node*> merger;
        Node *leftSib = root->child;
        // TODO: remove root
        delete root;
        root = nullptr; /// pitfall happens here !!!
        // TODO: decrease count
        count -- ;
        // TODO: if count == 1, only root get removed, then return after deleting
        if (!leftSib) return;
        merger.push_back(leftSib);
        // TODO: add all first level siblings
        while(leftSib->sibling){
            Node *temp = leftSib;
            leftSib = leftSib->sibling;
            temp->sibling = nullptr; /// remove the sibling in order to meld
            temp->previous = nullptr;
            merger.push_back(leftSib);
        }
        // TODO: if after pop(), there is only one element left, then set
        //  root equal to this node and NULL previous and sibling pointer
        merger.back()->previous = nullptr; /// pitfall happens here !!!
        if (merger.size() == 1){
            root = merger.front();
            root->previous = root->sibling = nullptr;
            return;
        }
        // TODO: after pop(),  count >= 2
        while(merger.size() > 1){
            Node *first = merger.front();
            merger.pop_front();
            Node *second = merger.front();
            merger.pop_front();
            merger.push_back(meld(first,second));
        }
        root = merger.front();
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function
        return root->elt;
    } // top()


    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        return count;
    } // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        return count == 0;
    } // empty()


    // Description: Updates the priority of an element already in the pairing
    //              heap by replacing the element refered to by the Node with
    //              new_value. Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more
    //               extreme (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    void updateElt(Node* node, const TYPE &new_value) {
        // TODO: Implement this function
        node->elt = new_value;
        if (node == root) return;
        // todo: is it the leftmost ?
        if (node->previous->child == node){ /// yes, I'm the leftmost !
            /// testing, maybe dont need this @@
            if (!this->compare(node->previous->elt,node->elt))
                return;
            /// testing, maybe dont need this @@
            Node *parent = node->previous;
            Node *oldSib = node->sibling;
            parent->child = oldSib;
            if (oldSib) /// NOTE: nullptr !!!
                oldSib->previous = parent;
            node->sibling = node->previous = nullptr;
            root = meld(root,node);
        }
        else{
            Node *prevSib = node->previous;
            Node *pastSib = node->sibling;
            prevSib->sibling = pastSib;
            if (pastSib) /// NOTE: nullptr !!!
                pastSib->previous = prevSib;
            node->sibling = node->previous = nullptr;
            root = meld(root,node);
        }

    } // updateElt()


    // Description: Add a new element to the pairing heap. Returns a Node*
    //              corresponding to the newly added element.
    // NOTE: Whenever you create a node, and thus return a Node *, you must
    //       be sure to never move or copy/delete that node in the future,
    //       until it is eliminated by the user calling pop(). Remember this
    //       when you implement updateElt() and updatePriorities().
    // Runtime: O(1)
    Node* addNode(const TYPE &val) {
        // TODO: Implement this function
        auto newNode = new Node(val);
        root = (count == 0 ? newNode : meld(root,newNode));
        count ++;
        return root;
    } // addNode()


private:
    // TODO: Add any additional member variables or member functions you
    //       require here.
    // TODO: We recommend creating a 'meld' function (see the Pairing Heap
    //       papers).
    Node *root = nullptr;
    size_t count = 0;


    // meld two heap into one
    // no parent, no sibling
    // return the current higher priority one
    Node *meld(Node *na, Node *nb) {
        /// debug
        if (na->previous || na->sibling || nb->previous || nb->sibling) {
            std::cerr << "invalid meld!\n";
            exit(-1);
        }
        /// debug
        if (this->compare(na->elt, nb->elt)) { // nb has higher priority
            if (nb->child) {
                Node *bChild = nb->child;
                bChild->previous = na; // child of b has left sibling a
                na->sibling = bChild; // bChild becomes a's right sibling
                na->previous = nb; // b becomes a's previous
                nb->child = na; // a becomes b's child
            } else {
                nb->child = na;
                na->previous = nb;
            }
            return nb;
        }
        else{
            if (na->child){
                Node *aChild = na->child;
                aChild->previous = nb;
                nb->sibling = aChild;
                nb->previous = na;
                na->child = nb;
            }
            else{
                na->child = nb;
                nb->previous = na;
            }
            return na;
        }
    }
    // NOTE: For member variables, you are only allowed to add a "root
    //       pointer" and a "count" of the number of nodes. Anything else
    //       (such as a deque) should be declared inside of member functions
    //       as needed.
};


#endif // PAIRINGPQ_H
