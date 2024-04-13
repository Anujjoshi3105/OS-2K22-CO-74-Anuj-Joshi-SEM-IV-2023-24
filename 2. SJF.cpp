#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

bool compareArrival(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

bool compareBurst(Process a, Process b) {
    return a.remainingTime < b.remainingTime;
}

void calculateAverageTimeNonPreemptive(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrival);
    int n = processes.size();
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    vector<int> waitingTimes(n, 0);
    vector<int> turnaroundTimes(n, 0);

    waitingTimes[0] = 0;
    turnaroundTimes[0] = processes[0].burstTime;

    for (int i = 1; i < n; i++) {
        waitingTimes[i] = processes[i - 1].burstTime + waitingTimes[i - 1];
        turnaroundTimes[i] = waitingTimes[i] + processes[i].burstTime;
    }

    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTimes[i];
        totalTurnaroundTime += turnaroundTimes[i];
    }

    cout << "Non-Preemptive SJF Schedule:" << endl;
    cout << "ProcessID  ArrivalTime  BurstTime  WaitingTime  TurnaroundTime" << endl;
    for (int i = 0; i < n; i++) {
        cout << "\t" << processes[i].id << "\t\t\t" << processes[i].arrivalTime << "\t\t\t"
             << processes[i].burstTime << "\t\t\t " << waitingTimes[i] << "\t\t\t " << turnaroundTimes[i] << endl;
    }
    cout << "Average waiting time = " << (float)totalWaitingTime / n << endl;
    cout << "Average turnaround time = " << (float)totalTurnaroundTime / n << endl;
}

void calculateAverageTimePreemptive(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrival);
    int n = processes.size();
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    vector<int> waitingTimes(n, 0);
    vector<int> turnaroundTimes(n, 0);

    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int minRemainingTime = INT_MAX;
        int shortestIndex = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < minRemainingTime && processes[i].remainingTime > 0) {
                minRemainingTime = processes[i].remainingTime;
                shortestIndex = i;
            }
        }
        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        processes[shortestIndex].remainingTime--;

        if (processes[shortestIndex].remainingTime == 0) {
            completed++;
            turnaroundTimes[shortestIndex] = currentTime + 1 - processes[shortestIndex].arrivalTime;
            waitingTimes[shortestIndex] = turnaroundTimes[shortestIndex] - processes[shortestIndex].burstTime;
            totalWaitingTime += waitingTimes[shortestIndex];
            totalTurnaroundTime += turnaroundTimes[shortestIndex];
        }
        currentTime++;
    }

    cout << "\nPreemptive SJF Schedule:" << endl;
    cout << "ProcessID  ArrivalTime  BurstTime  WaitingTime  TurnaroundTime" << endl;
    for (int i = 0; i < n; i++) {
        cout << "\t" << processes[i].id << "\t\t\t" << processes[i].arrivalTime << "\t\t\t"
             << processes[i].burstTime << "\t\t\t " << waitingTimes[i] << "\t\t\t " << turnaroundTimes[i] << endl;
    }
    cout << "Average waiting time = " << (float)totalWaitingTime / n << endl;
    cout << "Average turnaround time = " << (float)totalTurnaroundTime / n << endl;
}

int main() {
    vector<Process> processes = {{1, 0, 7, 7}, {2, 2, 4, 4}, {3, 4, 1, 1}, {4, 6, 4, 4}};
    
    cout << "Number of Processes: " << processes.size() << endl << endl;
    calculateAverageTimeNonPreemptive(processes);
    cout << endl;
    calculateAverageTimePreemptive(processes);

    return 0;
}
