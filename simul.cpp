#include <iostream>
#include <vector>

#include "process.cpp"

Queue* ready_queue;
Queue* finished_queue;

vector<float> StartSimulation (int* raw_data) {
	// Set variables (QT, NOP, OUT_ARRAY)
	size_t QT = static_cast<size_t>(raw_data[0]);
	size_t NOP = static_cast<size_t>(raw_data[1]);
    vector<float> OUT_ARRAY = vector(3 + 3*NOP, 0.0f);

	// Load data into processes
	Process* processes = new Process[NOP];
    for (int i = 0; i < NOP; ++i) {
        processes[i].pid = i;
        processes[i].burst_time = raw_data[2 + i * 2];
        processes[i].arrival_time = raw_data[3 + i * 2];
        processes[i].completion_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].response_time = -1; 
    }

	// Init queues and vars
	ready_queue = createQueue();
    finished_queue = createQueue();
	size_t current_time = 0;
    int remaining_processes = NOP;
    int current_process_index = 0;

	// Loop over ready queue and push back as necessary
	// while setting each process's data according to simulation
	// and when a process is done insert it into finished queue
	while (remaining_processes > 0) {
        for (int i = 0; i < NOP; ++i) {
            if (processes[i].arrival_time >= current_time) {
                Enqueue(ready_queue, processes[i]);
            }
        }

        if (!isEmpty(ready_queue)) {
            Process current_process = Dequeue(ready_queue);

            if (current_process.response_time == -1) {
                current_process.response_time = current_time - current_process.arrival_time;
            }

            size_t execution_time = std::min(QT, current_process.burst_time);
            current_process.burst_time -= execution_time;
            current_time += execution_time;

           if (current_process.burst_time == 0) {
                current_process.completion_time = current_time;
                current_process.turnaround_time = current_process.completion_time - current_process.arrival_time;
                current_process.waiting_time = current_process.turnaround_time - current_process.burst_time;
                Enqueue(finished_queue, current_process); 
                remaining_processes--;

				// FORMAT:
				// avg. Waiting T
				// avg. Turnaround T
				// avg. Response T
				// Pn WT
				// Pn TAT
				// Pn RT
                OUT_ARRAY[3 + current_process.pid * 3] = current_process.waiting_time;
				OUT_ARRAY[4 + current_process.pid * 3] = current_process.turnaround_time;
				OUT_ARRAY[5 + current_process.pid * 3] = current_process.response_time;

				OUT_ARRAY[0] += current_process.waiting_time;
				OUT_ARRAY[1] += current_process.turnaround_time;
				OUT_ARRAY[2] += current_process.response_time;
            } else {
                Enqueue(ready_queue, current_process); 
            }
        } else {
            current_time++; 
        }
    }

	// Finish calculation of averages
	OUT_ARRAY[0] /= NOP;
	OUT_ARRAY[1] /= NOP;
	OUT_ARRAY[2] /= NOP;

	// Dealloc memory
	delete[] processes;
	delete ready_queue;   	// Individual nodes not dealloced
	delete finished_queue;  // hopefully system handles memory leaks

	return OUT_ARRAY;
}