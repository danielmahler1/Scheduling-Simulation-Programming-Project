#include <iostream>

// #include "project.hpp"

using namespace std;

void FCFS() {
    cout << "FCFS" << endl;
}

void SJF() {
    cout << "SJF" << endl;
}

void RR() {
    cout << "RR" << endl;
}

int main() {
    cout << "Choose your simulation\n1. FCFS\n2. SJF\n3. RR\nEnter your selection: " << endl;
    int choice;
    cin >> choice;
    if(choice == 1)
        FCFS();
    else if(choice == 2)
        SJF();
    else if(choice == 3)
        RR();
    else
        cout << "Invalid choice" << endl;
    return 0;
}
