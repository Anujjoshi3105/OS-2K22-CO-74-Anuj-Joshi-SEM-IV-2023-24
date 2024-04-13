#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id;
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
};

bool comparePriority(Process a, Process b) {
    return a.priority < b.priority;
}

void calculateWaitingTimeTurnaroundTime(vector<Process>& processes) {
    processes[0].waitingTime = 0;
    processes[0].turnaroundTime = processes[0].burstTime;

    for (int i = 1; i < processes.size(); ++i) {
        processes[i].waitingTime = processes[i - 1].burstTime + processes[i - 1].waitingTime;
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
    }
}

void calculateAverageTime(vector<Process>& processes) {
    float totalWaitingTime = 0;
    float totalTurnaroundTime = 0;

    for (int i = 0; i < processes.size(); ++i) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    cout << "ProcessID  BurstTime  Priority  WaitingTime  TurnaroundTime" << endl;
    for (int i = 0; i < processes.size(); ++i) {
        cout << "\t" << processes[i].id << "\t\t\t" << processes[i].burstTime << "\t\t\t" << processes[i].priority << "\t\t\t"
             << processes[i].waitingTime << "\t\t\t" << processes[i].turnaroundTime << endl;
    }
    cout << "Average waiting time = " << totalWaitingTime / processes.size() << endl;
    cout << "Average turnaround time = " << totalTurnaroundTime / processes.size() << endl;
}

int main() {
    vector<Process> processes = {{1, 7, 2}, {2, 4, 1}, {3, 1, 3}, {4, 4, 4}}; // Processes with their burst times and priorities

    // Sort processes based on priority
    sort(processes.begin(), processes.end(), comparePriority);

    calculateWaitingTimeTurnaroundTime(processes);
    calculateAverageTime(processes);

    return 0;
}
