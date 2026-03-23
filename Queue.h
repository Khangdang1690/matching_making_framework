#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

// Templated Queue class implemented using a circularly linked list.
// The tail node's next pointer wraps around to the front node,
// forming a circular structure. This allows O(1) enqueue and dequeue.
template <typename T>
class Queue {
private:
    // Node structure for the circularly linked list
    struct Node {
        T data;         // The element stored in this node
        Node* next;     // Pointer to the next node in the circular list

        // Construct a node with the given data
        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* m_tail;   // Points to the last node; m_tail->next is the front
    int   m_size;   // Number of elements currently in the queue

public:
    // Constructor: initializes an empty queue
    Queue() : m_tail(nullptr), m_size(0) {}

    // Destructor: frees all nodes in the circular list
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Copy constructor: performs a deep copy of another queue
    Queue(const Queue& other) : m_tail(nullptr), m_size(0) {
        if (other.isEmpty()) return;

        // Walk the circular list starting from the front
        Node* current = other.m_tail->next; // front of the other queue
        for (int i = 0; i < other.m_size; ++i) {
            enqueue(current->data);
            current = current->next;
        }
    }

    // Copy assignment operator: deep copies using copy-and-swap idiom
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            // Clear current contents
            while (!isEmpty()) {
                dequeue();
            }
            // Copy elements from other
            if (!other.isEmpty()) {
                Node* current = other.m_tail->next;
                for (int i = 0; i < other.m_size; ++i) {
                    enqueue(current->data);
                    current = current->next;
                }
            }
        }
        return *this;
    }

    // Adds an element to the back of the queue
    void enqueue(const T& item) {
        Node* newNode = new Node(item);

        if (isEmpty()) {
            // Single node points to itself to form the circular link
            newNode->next = newNode;
            m_tail = newNode;
        } else {
            // Insert new node after tail, before front
            newNode->next = m_tail->next;  // new node points to front
            m_tail->next = newNode;        // old tail points to new node
            m_tail = newNode;              // new node becomes the new tail
        }
        ++m_size;
    }

    // Removes and returns the element at the front of the queue
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot dequeue from an empty queue");
        }

        Node* frontNode = m_tail->next;  // The front node
        T data = frontNode->data;

        if (m_size == 1) {
            // Only one node — queue becomes empty
            m_tail = nullptr;
        } else {
            // Skip over the front node
            m_tail->next = frontNode->next;
        }

        delete frontNode;
        --m_size;
        return data;
    }

    // Returns a reference to the front element without removing it
    T& front() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return m_tail->next->data;
    }

    // Returns a const reference to the front element without removing it
    const T& front() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return m_tail->next->data;
    }

    // Returns true if the queue has no elements
    bool isEmpty() const {
        return m_tail == nullptr;
    }

    // Returns the number of elements in the queue
    int size() const {
        return m_size;
    }

    // Prints all elements in the queue from front to back.
    // Requires that T supports the << operator.
    void display(std::ostream& os = std::cout) const {
        if (isEmpty()) return;

        Node* current = m_tail->next;  // Start at front
        for (int i = 0; i < m_size; ++i) {
            os << "  " << *(current->data) << "\n";
            current = current->next;
        }
    }
};

#endif // QUEUE_H
