#include <iostream>
#include <thread>

using namespace std;

void threadFunction() {
    cout << "Hello from thread!" << endl;
}

int main() {
    // Create a thread object
    thread myThread(threadFunction);

    // Thread running concurrently with the main thread
    cout << "Hello from main thread!" << endl;

    // Wait for the thread to finish
    myThread.join();

    return 0;
}
