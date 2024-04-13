#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Process {
    int id;
    int burstTime;
    int remainingTime;
    int arrivalTime;
};

void calculateAverageTimeNonPreemptive(vector<Process>& processes, int quantum) {
    int n = processes.size();
    queue<Process> readyQueue;
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    int currentTime = 0;

    for (int i = 0; i < n; ++i) {
        readyQueue.push(processes[i]);
    }

    while (!readyQueue.empty()) {
        Process currentProcess = readyQueue.front();
        readyQueue.pop();

        if (currentProcess.burstTime <= quantum) {
            currentTime += currentProcess.burstTime;
            turnaroundTime[currentProcess.id] = currentTime;
        } else {
            currentTime += quantum;
            currentProcess.burstTime -= quantum;
            readyQueue.push(currentProcess);
        }
    }

    // Calculating waiting time
    for (int i = 0; i < n; ++i) {
        waitingTime[i] = turnaroundTime[i] - processes[i].burstTime - processes[i].arrivalTime;
    }

    // Display results
    cout << "Non-Preemptive Round Robin Schedule:" << endl;
    cout << "ProcessID  BurstTime  WaitingTime  TurnaroundTime" << endl;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; ++i) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
        cout << "\t" << processes[i].id << "\t\t\t" << processes[i].burstTime << "\t\t\t" << waitingTime[i] << "\t\t\t " << turnaroundTime[i] << endl;
    }
    cout << "Average waiting time = " << totalWaitingTime / n << endl;
    cout << "Average turnaround time = " << totalTurnaroundTime / n << endl;
}

void calculateAverageTimePreemptive(vector<Process>& processes, int quantum) {
    int n = processes.size();
    queue<Process> readyQueue;
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    int currentTime = 0;

    for (int i = 0; i < n; ++i) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    while (true) {
        bool done = true;
        for (int i = 0; i < n; ++i) {
            if (processes[i].remainingTime > 0) {
                done = false;
                if (processes[i].remainingTime > quantum) {
                    currentTime += quantum;
                    processes[i].remainingTime -= quantum;
                } else {
                    currentTime += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                    turnaroundTime[i] = currentTime;
                }
            }
        }
        if (done) break;
    }

    // Calculating waiting time
    for (int i = 0; i < n; ++i) {
        waitingTime[i] = turnaroundTime[i] - processes[i].burstTime - processes[i].arrivalTime;
    }

    // Display results
    cout << "\nPreemptive Round Robin Schedule:" << endl;
    cout << "ProcessID  BurstTime  WaitingTime  TurnaroundTime" << endl;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; ++i) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
        cout << "\t" << processes[i].id << "\t\t\t" << processes[i].burstTime << "\t\t\t" << waitingTime[i] << "\t\t\t" << turnaroundTime[i] << endl;
    }
    cout << "Average waiting time = " << totalWaitingTime / n << endl;
    cout << "Average turnaround time = " << totalTurnaroundTime / n << endl;
}

int main() {
    vector<Process> processes = {{0, 7, 0}, {1, 9, 0}, {2, 6, 0}, {3, 3, 0}}; // Processes with their burst times and arrival times
    int quantum = 3; // Time quantum

    calculateAverageTimeNonPreemptive(processes, quantum);
    calculateAverageTimePreemptive(processes, quantum);

    return 0;
}
