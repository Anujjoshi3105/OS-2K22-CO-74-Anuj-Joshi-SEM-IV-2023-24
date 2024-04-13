#include <iostream>
#include <vector>

using namespace std;

int main() {
  const int MAX_FRAMES = 50;
  int frames[MAX_FRAMES];
  vector<int> reference = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
  int numFrames = 3;
  int numReferences = reference.size();
  int numPageFaults = 0;
  int frameIndex = 0;

  cout << "FIFO Page Replacement Algorithm" << endl << endl;
  cout << "Reference String\tPage Frames" << endl;

  for (int i = 0; i < numReferences; i++) {
    bool pageFound = false;
    int page = reference[i];

    for (int j = 0; j < numFrames; j++) {
      if (frames[j] == page) {
        pageFound = true;
        break;
      }
    }

    if (!pageFound) {
      frames[frameIndex] = page;
      frameIndex = (frameIndex + 1) % numFrames;
      numPageFaults++;
    }

    cout << page << "\t\t";
    for (int j = 0; j < numFrames; j++) {
      cout << frames[j] << "\t";
    }
    cout << endl;
  }

  cout << endl << "Total number of page faults: " << numPageFaults << endl;

  return 0;
}
