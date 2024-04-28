#include <iostream>

using namespace std;

typedef struct s_Process {
    size_t pid;
    size_t burst_time;
    size_t arrival_time;
    size_t completion_time;
    size_t waiting_time;
    size_t turnaround_time;
    size_t response_time;
} Process;

typedef struct s_Node {
    Process data;
    Node* next;
} Node;

typedef struct s_Queue {
    Node* front;
    Node* rear;
} Queue;

Queue* createQueue() {
    Queue* q = new Queue;
    q->front = q->rear = nullptr;
    return q;
}

void Enqueue(Queue* q, Process p) {
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

Process Dequeue(Queue* q) {
    if (q->front == nullptr)
        throw "Queue is empty";

    Node* temp = q->front;
    Process p = temp->data;
    q->front = q->front->next;

    if (q->front == nullptr)
        q->rear = nullptr;

    delete temp;
    return p;
}
