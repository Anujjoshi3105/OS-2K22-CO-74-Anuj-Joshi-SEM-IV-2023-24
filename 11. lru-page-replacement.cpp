#include <iostream>
using namespace std;

int framesCount, referencesCount, pageFaults = 0;
int ref[50], frames[50], recent[10], lruCalculations[50];

// Function to get the victim page using LRU
int getLruVictim();

int main() {
    cout << "\n\t\t\t LRU PAGE REPLACEMENT ALGORITHM" << endl;

    // Input number of frames and reference string
    cout << "Enter the number of frames: ";
    cin >> framesCount;
    cout << "Enter the size of reference string: ";
    cin >> referencesCount;
    cout << "Enter the reference string (separated by space): ";
    for (int i = 0; i < referencesCount; i++) 
        cin >> ref[i];

    // Initialize arrays
    for (int i = 1; i <= framesCount; i++) {
        frames[i] = -1;
        lruCalculations[i] = 0;
    }

    for (int i = 0; i < 10; i++) 
        recent[i] = 0;

    // Process the reference string
    cout << "\n\n\t\t LRU PAGE REPLACEMENT ALGORITHM\n";
    cout << "\nReference String\t\tPage Frames\n";

    for (int i = 0; i < referencesCount; i++) {
        int flag = 0;
        cout << "\n\t " << ref[i] << "\t \t \t \t ";

        // Check if page already in frames
        for (int j = 0; j < framesCount; j++) {
            if (frames[j] == ref[i]) {
                flag = 1;
                break;
            }
        }

        // Page fault handling
        if (flag == 0) {
            pageFaults++;

            // Find victim page using LRU
            int victim = getLruVictim();
            frames[victim] = ref[i];

            // Update recent array
            recent[ref[i]] = i;

            // Display current page frames
            for (int j = 0; j < framesCount; j++) 
                cout << frames[j] << "\t";
        }
    }

    // Print total number of page faults
    cout << "\n\n\t No. of page faults: " << pageFaults << endl;
    return 0;
}

// Function to get the victim page using LRU
int getLruVictim() {
    int temp1, temp2;
    
    // Calculate LRU for each frame
    for (int i = 0; i < framesCount; i++) {
        temp1 = frames[i];
        lruCalculations[i] = recent[temp1];
    }

    // Find the page with minimum recent value (LRU)
    temp2 = lruCalculations[0];
    for (int j = 1; j < framesCount; j++) {
        if (temp2 > lruCalculations[j]) {
            temp2 = lruCalculations[j];
        }
    }

    // Find the victim page index
    for (int i = 0; i < framesCount; i++) {
        if (ref[temp2] == frames[i]) {
            return i;
        }
    }
    return 0;
}
