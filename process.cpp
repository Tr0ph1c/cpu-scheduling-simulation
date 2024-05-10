#include <iostream>

using namespace std;

class Process {
    public:
    size_t pid = 0;
    size_t burst_time = 0;
    size_t burst_time_left = 0;
    size_t arrival_time = 0;
    size_t completion_time = 0;
    size_t waiting_time = 0;
    size_t turnaround_time = 0;
    size_t response_time = -1;
    bool queued = false;

    // overloading comparision operator to be able to sort with std::sort
    bool operator< (Process p2) {
        return (this->arrival_time < p2.arrival_time)? true : false;
    }
};

class Node {
    public:
    Process data;
    Node* next;

    Node (Process _data) {
        data = _data;
        next = nullptr;
    }

    ~Node () {
        delete next;
    }

    void Destroy () {
        next = nullptr;
        delete this;
    }
};

class Queue {
    public:
    Node* front;
    Node* rear;

    Queue () {
        front = nullptr;
        rear = nullptr;
    }

    ~Queue () {
        delete front; // recursively deletes all nodes ~Node()
    }

    bool isEmpty () { return !front; }

    void Enqueue (Process p) {

        Node* newNode = new Node(p);

        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }

    Process Dequeue () {
        if (isEmpty()) throw "Queue is empty";

        Process p = front->data;
        Node* temp = front;
        front = front->next;

        if (front == nullptr) rear = nullptr;

        temp->Destroy();
        return p;
    }
};