#include <iostream>

using namespace std;

struct process {
    size_t pid;
    size_t burst_time;
    size_t arrival_time;
    size_t completion_time;
    size_t waiting_time;
    size_t turnaround_time;
    size_t response_time;
};

struct Node {
    process data;
    Node* next;
};

struct Queue {
    Node* front;
    Node* rear;
};

Queue* createQueue() {
    Queue* q = new Queue;
    q->front = q->rear = nullptr;
    return q;
}

void Enqueue(Queue* q, process p) {
    Node* newNode = new Node;
    newNode->data = p;
    newNode->next = nullptr;

    if (q->rear == nullptr) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

process Dequeue(Queue* q) {
    if (q->front == nullptr)
        throw "Queue is empty";

    Node* temp = q->front;
    process p = temp->data;
    q->front = q->front->next;

    if (q->front == nullptr)
        q->rear = nullptr;

    delete temp;
    return p;
}
