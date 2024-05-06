//Name: Daniel Mahler, Course: CISC 361-010 Operating Systems

/*
 * Compilation Instructions:
 * To compile this program, use the following command:
 * g++ -std=c++11 -o project project.cpp
 * 
 * Execution Instructions:
 * To run the compiled program, execute:
 * ./project
 * 
 * Description:
 * This program simulates three types of CPU scheduling algorithms:
 * 1. First-Come, First-Served (FCFS)
 * 2. Shortest Job First (SJF)
 * 3. Round Robin (RR)
 * 
 * The user is prompted to choose one of the three scheduling algorithms.
 * The program then simulates the selected scheduling algorithm by creating 100 tasks.
 * Each task has a unique task ID, creation time, and burst time.
 * After selecting the simulation method, the program makes each unique task, sleeping for 1 second between tasks.
 * After 100 seconds, the program will display the tasks in the order they were processed.
*/

#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <chrono>
#include <cstdlib> // For rand() and srand()
#include <thread>  // For sleep_for()

using namespace std;

// Task structure to hold information about each task
struct TaskStruct {
    time_t creationTime; // Time when the task was created
    int taskid;          // Unique identifier for the task
    int burstTime;       // Duration the task needs to run (used in SJF and RR)
};

// Comparator for prioritizing tasks based on burst time (Shortest Job First)
struct Comparator {
    bool operator()(const TaskStruct& t1, const TaskStruct& t2) {
        return t1.burstTime > t2.burstTime;
    }
};

// Simulates First-Come, First-Served (FCFS) scheduling
void FCFS() {
    queue<TaskStruct> queue;
    for (int i = 0; i < 100; i++) {
        TaskStruct task;
        chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
        task.creationTime = chrono::system_clock::to_time_t(now);
        task.taskid = rand() % 100 + 1;
        queue.push(task);
        this_thread::sleep_for(chrono::seconds(1)); // Ensure unique creation times
    }

    while (!queue.empty()) {
        TaskStruct task = queue.front();
        queue.pop();
        cout << "Working on task ID " << task.taskid << " received at time " << ctime(&task.creationTime);
    }
}

// Simulates Shortest Job First (SJF) scheduling
void SJF() {
    priority_queue<TaskStruct, vector<TaskStruct>, Comparator> queue;
    for (int i = 0; i < 100; i++) {
        TaskStruct task;
        chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
        task.creationTime = chrono::system_clock::to_time_t(now);
        task.taskid = rand() % 100 + 1;
        task.burstTime = rand() % 6 + 1;
        queue.push(task);
        this_thread::sleep_for(chrono::seconds(1));
    }

    while (!queue.empty()) {
        TaskStruct task = queue.top();
        queue.pop();
        cout << "Working on task ID " << task.taskid << " with burst time " << task.burstTime << " at time " << ctime(&task.creationTime);
    }
}

// Simulates Round Robin (RR) scheduling
void RR() {
    int quantum;
    cout << "Enter the time slice (quantum) for RR: ";
    cin >> quantum;

    queue<TaskStruct> queue;
    for (int i = 0; i < 100; i++) {
        TaskStruct task;
        chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
        task.creationTime = chrono::system_clock::to_time_t(now);
        task.taskid = rand() % 100 + 1;
        task.burstTime = rand() % 6 + 1;
        queue.push(task);
        this_thread::sleep_for(chrono::seconds(1));
    }

    while (!queue.empty()) {
        TaskStruct task = queue.front();
        queue.pop();
        cout << "Working on task ID " << task.taskid << " with remaining burst time " << task.burstTime << " at time " << ctime(&task.creationTime);
        if (task.burstTime > quantum) {
            task.burstTime -= quantum;
            queue.push(task);
            cout << "Task ID " << task.taskid << " will Get Back to it LATER\n";
        } else {
            cout << "Task ID " << task.taskid << " is DONE\n";
        }
    }
}

// Main function to drive the simulation
int main() {
    srand(static_cast<unsigned>(time(nullptr)));  // Seed the random number generator
    cout << "Choose your simulation\n1. FCFS\n2. SJF\n3. RR\nEnter your selection: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            FCFS();
            break;
        case 2:
            SJF();
            break;
        case 3:
            RR();
            break;
        default:
            cout << "Invalid choice" << endl;
    }
    return 0;
}
