#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // Incoming page reference stream
    vector<int> incomingStream = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

    // Number of frames
    int frames = 3;

    // Initialize frame array with -1 (indicating empty frame)
    vector<int> temp(frames, -1);

    // Initialize page faults counter
    int pageFaults = 0;

    // Process incoming page references
    for (int i = 0; i < incomingStream.size(); ++i)
    {
        int page = incomingStream[i];
        bool pageFound = false;

        // Check if page is already in a frame
        for (int j = 0; j < frames; ++j)
        {
            if (temp[j] == page)
            {
                pageFound = true;
                break;
            }
        }

        // If page not found in frames, perform page replacement
        if (!pageFound)
        {
            // Increment page faults
            pageFaults++;

            // Find the frame to replace using FIFO (First-In-First-Out) algorithm
            int replaceIndex = i % frames;

            // Replace page in frame
            temp[replaceIndex] = page;
        }

        // Print current frame state
        cout << "Incoming Page: " << page << "\tFrames: ";
        for (int j = 0; j < frames; ++j)
        {
            if (temp[j] != -1)
                cout << temp[j] << " ";
            else
                cout << "- ";
        }
        cout << endl;
    }

    // Print total page faults
    cout << "\nTotal Page Faults: " << pageFaults << endl;

    return 0;
}
