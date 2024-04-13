#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
using namespace std;

const int BUFFER_SIZE = 1; 
vector<int> buffer; // Shared buffer
mutex mtx; // Mutex for critical section
condition_variable prod_cv, cons_cv; // Condition variables for synchronization
bool buffer_full = false, buffer_empty = true; // Flags to track buffer state

void producer(int prodID) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        prod_cv.wait(lock, [] { return !buffer_full; }); // Wait until buffer is not full

        // Critical Section: Producer produces an item and puts it into the buffer
        buffer.push_back(prodID);
        cout << "Producer " << prodID << " produced item " << prodID << endl;

        buffer_empty = false; // Buffer is not empty now
        if (buffer.size() >= BUFFER_SIZE) // If buffer is full
            buffer_full = true;

        // Signal consumer to consume
        cons_cv.notify_one();
    }
}

void consumer(int consID) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cons_cv.wait(lock, [] { return !buffer_empty; }); // Wait until buffer is not empty

        // Critical Section: Consumer consumes an item from the buffer
        int item = buffer.back();
        buffer.pop_back();
        cout << "Consumer " << consID << " consumed item " << item << endl;

        buffer_full = false; // Buffer is not full now
        if (buffer.empty()) // If buffer is empty
            buffer_empty = true;

        // Signal producer to produce
        prod_cv.notify_one();
    }
}

int main() {
    thread prodThread(producer, 0);
    thread consThread(consumer, 1);

    prodThread.join();
    consThread.join();

    return 0;
}
