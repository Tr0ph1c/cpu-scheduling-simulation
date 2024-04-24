#include <iostream>
#include <fstream>
#include <string>

#include "simul.cpp"

#define INPUT_FILE "./inputs"
#define OUTPUT_FILE "./outputs"

using namespace std;

void LoadAllProccesses () {
    ifstream inputs(INPUT_FILE);

    if (!inputs.is_open()) { 
        cerr << "Error opening the file!" << endl;
        exit(1);
    }

    string line;

    while (getline(inputs, line)) {
        // Load the line as a process
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
    LoadAllProccesses();

    StartSimulation();

    SaveResults();
}