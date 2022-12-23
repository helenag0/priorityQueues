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
            : elt{ val }, child{ nullptr }, sibling{ nullptr }, parent { nullptr }
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
            // TODO: Add one extra pointer (parent or previous) as desired.
            Node *parent;
    }; // Node


    // Description: Construct an empty pairing heap with an optional
    //              comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function.
            this->count = 0;
            this->root_ptr = nullptr;
            this->root_ptr->parent = nullptr;
            this->root_ptr->child = nullptr;
            this->root_ptr->sibling = nullptr;
    } // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function.
            this->count = static_cast<int>(end - start);
            new Node *n;
            n->root_ptr = nullptr;
            int second_count = (count - 2) / 2;
            }
    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) :
        BaseClass{ other.compare } {
        // TODO: Implement this function.
        // NOTE: The structure does not have to be identical to the original,
        //       but it must still be a valid pairing heap.
            
    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ &operator=(const PairingPQ &rhs) {
        // TODO: Implement this function.
        // HINT: Use the copy-swap method from the "Arrays and Containers"
        //       lecture.
        Node* temp = *rhs;
        count = rhs.count;
        temp = new Node[count];
        for(size_t i = 0; i < count; ++i) {
            std::swap(rhs.count, temp->count);
            std::swap(rhs.parent, temp->parent);
            
        }
        if(this != &rhs) {
            
        }

        return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        // TODO: Implement this function.
        root_ptr->elt = nullptr;
        Node * curr = root_ptr->child;
        Node * next;
        for(auto& it : count) {
            curr = next;
            if(curr->sibling == nullptr) {
                next = curr->child;
                curr = nullptr;
            }
            else {
                next = curr->sibling;
                curr = nullptr;
            }
        }
        count = 0;
    } // ~PairingPQ()


    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant. You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        std::deque<Node*> dq;
        dq.push_back(root_ptr);
        Node * curr = root_ptr->child;
        for(auto& it : count) {
            dq.push_back(meld(root_ptr, curr));
            if(curr->sibling == nullptr) {
                curr = curr->child;
            }
            else {
                curr = curr->sibling;
            }
            
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
    virtual void pop() {
        // TODO: Implement this function.
        if(count == 1) {
            root_ptr = nullptr;
        }
        
        count--;
        // delete node
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function
        return root_ptr;
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
        if(this->compare(node->elt, new_value)){
            node->elt = new_value;
        }
        updatePriorities();
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
        Node * n = new Node(val);
        n->elt = val;
        count++;
        if(count == 0) {
            root_ptr = n;
        }
        if(count > 0) {
            meld(root_ptr, n);
        }
        return n;
    } // addNode()


private:
    // TODO: Add any additional member variables or member functions you
    //       require here.
    int count;
    Node* root_ptr;
    // TODO: We recommend creating a 'meld' function (see the Pairing Heap
    //       papers).
    Node * meld(Node *pa, Node *pb) {
        assert(pa->parent == nullptr && pb->parent == nullptr &&
               pa->sibling == nullptr && pb->sibling == nullptr);
            if(this->compare(pa->elt, pb->elt)) {
                pb->child = pa;
                pa->parent = pb;
                return pb;
            }
            else {
                pa->child = pb;
                pb->parent = pa;
                return pa;
            }
        
    }

    // NOTE: For member variables, you are only allowed to add a "root
    //       pointer" and a "count" of the number of nodes. Anything else
    //       (such as a deque) should be declared inside of member functions
    //       as needed.
};


#endif // PAIRINGPQ_H

