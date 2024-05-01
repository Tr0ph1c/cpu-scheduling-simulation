#include <iostream>
#include <fstream>
#include <vector>

#include "simul.cpp"

#define INPUT_FILE "./inputs"
#define OUTPUT_FILE "./outputs"

using namespace std;

int raw_data[202];

void LoadAllInputs () {
    ifstream inputs(INPUT_FILE);

    if (!inputs.is_open()) { 
        cerr << "Error opening the file!" << endl;
        exit(1);
    }

    string line;

    getline(inputs, line);
    raw_data[0] = stoi(line);
    getline(inputs, line);
    raw_data[1] = stoi(line);

    for (size_t i = 0; getline(inputs, line); ++i) {
        raw_data[2+i] = stoi(line);
    }

    inputs.close();
}

void SaveResults (vector<float> raw_out_data) {
    ofstream outputs(OUTPUT_FILE);

    if (!outputs.is_open()) { 
        cerr << "Error opening the file!" << endl;
        exit(1);
    }

    cout << "\n";

    for (float i : raw_out_data) {
        std::cout << i << "\n";
        outputs << i << "\n";
    }

    outputs.close();
}

int main () {
    LoadAllInputs();

    vector<float> raw_out_data = StartSimulation(raw_data);

    SaveResults(raw_out_data);
}