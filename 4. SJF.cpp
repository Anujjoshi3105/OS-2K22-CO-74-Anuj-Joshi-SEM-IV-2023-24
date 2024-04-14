#include <iostream>
#include <algorithm>
using namespace std;

void calculateWaitingTime(int processIDs[], int n, int burstTimes[], int waitingTimes[])
{
    waitingTimes[0] = 0; // Waiting time for the first process is 0
    for (int i = 1; i < n; i++)
        waitingTimes[i] = burstTimes[i - 1] + waitingTimes[i - 1];
}

void calculateTurnAroundTime(int processIDs[], int n, int burstTimes[], int waitingTimes[], int turnaroundTimes[])
{
    for (int i = 0; i < n; i++)
        turnaroundTimes[i] = burstTimes[i] + waitingTimes[i]; // Turnaround time = Burst time + Waiting time
}

void calculateAverageTime(int processIDs[], int n, int burstTimes[])
{
    int waitingTimes[n], turnaroundTimes[n], totalWaitingTime = 0, totalTurnaroundTime = 0;
    calculateWaitingTime(processIDs, n, burstTimes, waitingTimes);
    calculateTurnAroundTime(processIDs, n, burstTimes, waitingTimes, turnaroundTimes);
    cout << "ProcessID  BurstTime  WaitingTime  TurnaroundTime\n";
    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += waitingTimes[i];
        totalTurnaroundTime += turnaroundTimes[i];
        cout << processIDs[i] << "\t\t" << burstTimes[i] << "\t\t" << waitingTimes[i] << "\t\t" << turnaroundTimes[i] << endl;
    }
    cout << "Average waiting time = " << (float)totalWaitingTime / (float)n;
    cout << "\nAverage turnaround time = " << (float)totalTurnaroundTime / (float)n;
}

int main()
{
    int processIDs[] = {1, 2, 3, 4};
    int n = sizeof processIDs / sizeof processIDs[0];
    int burstTimes[] = {7, 4, 1, 4};

    // Sorting processes according to their Burst Time.
    sort(burstTimes, burstTimes + n);

    calculateAverageTime(processIDs, n, burstTimes);
    return 0;
}
