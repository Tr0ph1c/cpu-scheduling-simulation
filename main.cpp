#include <iostream>
#include <fstream>
#include <cstring>

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

void SaveResults () {
    ifstream outputs(OUTPUT_FILE);

    if (!outputs.is_open()) { 
        cerr << "Error opening the file!" << endl;
        exit(1);
    }

    // Put results in file
    cout << "Saved results";

    outputs.close();
}

int main () {
    LoadAllInputs();

    StartSimulation(raw_data);

    SaveResults();
}