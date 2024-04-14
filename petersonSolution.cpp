#include <iostream>
#include <thread>
#include <vector>

const int NUM_THREADS = 2; 

std::vector<bool> ready(NUM_THREADS, false); 
int current = 0; 

void producer(int prodID) {
    do {
        ready[prodID] = true; 
        current = 1 - prodID;      
        while (ready[1 - prodID] && current == 1 - prodID) {
        }

        // Critical Section: Producer produces an item and puts it into the buffer

        ready[prodID] = false; 

        // Remainder Section: Additional actions after critical section
    } while (true); 
}

void consumer(int consID) {
    do {
        ready[consID] = true; 
        current = consID;           
        while (ready[1 - consID] && current == consID) {
        }

        // Critical Section: Consumer consumes an item from the buffer

        ready[consID] = false; 

        // Remainder Section: Additional actions after critical section
    } while (true); 
}

int main() {
    std::thread prodThread(producer, 0); 
    std::thread consThread(consumer, 1); 

    prodThread.join(); 
    consThread.join(); 

    return 0;
}
