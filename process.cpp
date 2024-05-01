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
};

class Node {
    public:
    Process* data;
    Node* next;

    Node () {
        data = nullptr;
        next = nullptr;
    }

    Node (Process* _data, Node* _next) {
        data = _data;
        next = _next;
    }

    ~Node () {
        delete data;
        delete next;
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
        while (front != rear) {
            Node* toDelete = front;
            front = front->next;
            delete toDelete;
        }
    }

    bool isEmpty () { return !front; }

    void Enqueue (Process* p) {
        Node* newNode = new Node(p, nullptr);

        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }

    Process* Dequeue () {
        if (isEmpty()) throw "Queue is empty";

        Process* ptr = front->data;
        Node* temp = front;
        front = front->next;

        if (front == nullptr) rear = nullptr;

        delete temp;
        return ptr;
    }
};