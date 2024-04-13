#include <iostream>
using namespace std;

// Function to check if a process can finish with current available resources
bool canFinish(int process, int maxResources[][4], int available[], int numProcesses, int numResources) {
  for (int j = 0; j < numResources; j++) {
    if (maxResources[process][j] > available[j]) {
      return false; // Process needs more resources than available
    }
  }
  return true;
}

int main() {
  // Number of processes and resources
  int numProcesses = 5;  // Processes (P0, P1, P2, P3, P4)
  int numResources = 4;  // Resources (R0, R1, R2, R3)

  // Allocation matrix (represents resources currently held by each process)
  int allocationMatrix[5][4] = {
    {3, 1, 2, 1},  // P0
    {2, 0, 0, 2},  // P1
    {1, 3, 2, 1},  // P2
    {2, 1, 1, 0},  // P3
    {0, 0, 2, 0}   // P4
  };

  // Maximum matrix (represents maximum resource needs of each process)
  int maxResources[5][4] = {
    {7, 5, 3, 4},  // P0
    {4, 2, 2, 2},  // P1
    {5, 4, 2, 2},  // P2
    {2, 2, 2, 1},  // P3
    {4, 3, 3, 2}   // P4
  };

  // Available resources (initially available)
  int availableResources[4] = {3, 3, 2, 1};

  // Finished processes (stores process IDs in safe sequence)
  int finishedProcesses[numProcesses] = {0};

  // Number of finished processes
  int numFinished = 0;

  // Loop until all processes are finished or a deadlock is detected
  while (numFinished < numProcesses) {
    int isSafe = 0; // Flag to check if any process can finish in this iteration

    // Check for each process if it can finish with current available resources
    for (int i = 0; i < numProcesses; i++) {
      if (finishedProcesses[i] == 0 && canFinish(i, maxResources, availableResources, numProcesses, numResources)) {
        // Process can finish, update resources and mark as finished
        for (int j = 0; j < numResources; j++) {
          availableResources[j] += allocationMatrix[i][j];
        }
        finishedProcesses[i] = 1;
        isSafe = 1;
      }
    }

    // If no process can finish, deadlock detected
    if (isSafe == 0) {
      cout << "Deadlock detected. System is in unsafe state." << endl;
      break;
    }

    numFinished++;  // Increment finished process count
  }

  // If all processes finished, print the safe sequence
  if (numFinished == numProcesses) {
    cout << "Following is the SAFE Sequence" << endl;
    for (int i = 0; i < numProcesses - 1; i++) {
      cout << " P" << i << " ->";
    }
    cout << " P" << numProcesses - 1 << endl;
  }

  return 0;
}
