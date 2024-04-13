#include <iostream>
using namespace std;

#define MAX_FRAMES 50
#define MAX_REFERENCE_STR 50

int numFrames, numReferences, pageFaults = 0;
int reference[MAX_REFERENCE_STR], frames[MAX_FRAMES], optCalculations[MAX_FRAMES], recent[10], count = 0;

// Function to find the victim page using the Optimal algorithm
int getOptimalVictim(int index);

int main() {
    cout << "\nOPTIMAL PAGE REPLACEMENT ALGORITHM\n";

    // Input number of frames and reference string
    cout << "Enter the number of frames: ";
    cin >> numFrames;
    cout << "Enter the size of reference string: ";
    cin >> numReferences;
    cout << "Enter the reference string (separated by space): ";
    for (int i = 0; i < numReferences; i++)
        cin >> reference[i];

    cout << "\nOPTIMAL PAGE REPLACEMENT ALGORITHM\n";
    cout << "\nReference String\tPage Frames\n";

    // Initialize arrays
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
        optCalculations[i] = 0;
    }

    for (int i = 0; i < 10; i++)
        recent[i] = 0;

    // Process the reference string
    for (int i = 0; i < numReferences; i++) {
        int flag = 0;
        cout << reference[i] << "\t\t\t\t";

        // Check if page already in frames
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == reference[i]) {
                flag = 1;
                break;
            }
        }

        // Page fault handling
        if (flag == 0) {
            pageFaults++;

            // Find victim page using Optimal algorithm
            int victim = getOptimalVictim(i);
            frames[victim] = reference[i];

            // Display current page frames
            for (int j = 0; j < numFrames; j++)
                cout << frames[j] << "\t";
        }
    }

    // Print total number of page faults
    cout << "\n\nNumber of page faults: " << pageFaults << endl;
    return 0;
}

// Function to find the victim page using the Optimal algorithm
int getOptimalVictim(int index) {
    int notFound, temp;
    for (int i = 0; i < numFrames; i++) {
        notFound = 1;
        for (int j = index; j < numReferences; j++) {
            if (frames[i] == reference[j]) {
                notFound = 0;
                optCalculations[i] = j;
                break;
            }
        }
        if (notFound == 1)
            return i;
    }
    temp = optCalculations[0];
    for (int i = 1; i < numFrames; i++) {
        if (temp < optCalculations[i])
            temp = optCalculations[i];
    }
    for (int i = 0; i < numFrames; i++)
        if (frames[temp] == frames[i])
            return i;
    return 0;
}
