IF NOT EXIST "inputs" type nul > "inputs"
IF NOT EXIST "outputs" type nul > "outputs"

g++ main.cpp -o main -g