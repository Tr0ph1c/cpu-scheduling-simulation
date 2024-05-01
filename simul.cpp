#include <iostream>
#include <algorithm>
#include <vector>

#include "process.cpp"

Queue* ready_queue    = new Queue();
Queue* finished_queue = new Queue();

void printGantt(vector<int> &vec) {
	for (int e : vec) {
		if (e != -1) cout << e << ",";
	}
}

vector<float> StartSimulation (int* raw_data) {
	// Set variables (QT, NOP, OUT_ARRAY)
	size_t QT = static_cast<size_t>(raw_data[0]);
	size_t NOP = static_cast<size_t>(raw_data[1]);
    vector<float> OUT_ARRAY = vector(3 + 3*NOP, 0.0f);
	vector<int> GANTT_ARRAY = vector(300, -1);

	// Load data into standby queue
	Process* processes = new Process[NOP];
    for (int i = 0; i < NOP; ++i) {
        processes[i].pid = i;
        processes[i].burst_time = raw_data[2 + i * 2];
        processes[i].burst_time_left = processes[i].burst_time;
        processes[i].arrival_time = raw_data[3 + i * 2];
    }

	std::sort(processes, processes + NOP);

	// Init vars
	size_t current_time = 0;
    size_t remaining_processes = NOP;
	size_t quantum_time_left = 0;
	Process current_process;

	// Loop over ready queue and push back as necessary
	// while setting each process's data according to simulation
	// and when a process is done insert it into finished queue
	while (remaining_processes > 0) {
        for (int i = 0; i < NOP; ++i) {
            if (processes[i].arrival_time <= current_time && !processes[i].queued) {
				processes[i].queued = true;
                ready_queue->Enqueue(processes[i]);
            }
        }

        if (!ready_queue->isEmpty() && quantum_time_left == 0) {
            current_process = ready_queue->Dequeue();
			quantum_time_left = QT;
			GANTT_ARRAY.push_back(current_process.pid);
			GANTT_ARRAY.push_back(current_time);
		}

		if (current_process.response_time == -1) {
			current_process.response_time = current_time - current_process.arrival_time;
		}

		current_time++;

		if (quantum_time_left) {
			quantum_time_left--;
			current_process.burst_time_left--;

			if (current_process.burst_time_left == 0) {
				quantum_time_left = 0;

				current_process.completion_time = current_time;
				current_process.turnaround_time = current_process.completion_time - current_process.arrival_time;
				current_process.waiting_time = current_process.turnaround_time - current_process.burst_time;
				finished_queue->Enqueue(current_process);
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

				GANTT_ARRAY.push_back(current_time);
			} else if (quantum_time_left == 0) {
				ready_queue->Enqueue(current_process);

				GANTT_ARRAY.push_back(current_time);
			}
		}
    }

	// Finish calculation of averages
	OUT_ARRAY[0] /= NOP;
	OUT_ARRAY[1] /= NOP;
	OUT_ARRAY[2] /= NOP;

	// Dealloc memory
  //delete[] processes;     // Processes now self deallocs from stack
	delete ready_queue;   	// Now properly destructs
	delete finished_queue;  // and deallocs all nodes

	printGantt(GANTT_ARRAY);
	return OUT_ARRAY;
}