#include <iostream>
using namespace std;

int main() {
    int storage[10], size, front = -1, rear = -1, itemProduced, itemConsumed, choice = 0;

    cout << "Enter storage size: ";
    cin >> size;

    cout << "\n1. Produce\t2. Consume\t3. Exit\n";

    while(choice != 3) {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                if ((rear + 1) % size == front)
                    cout << "\nStorage is Full\n";
                else {
                    cout << "\nEnter the value to produce: ";
                    cin >> itemProduced;
                    rear = (rear + 1) % size;
                    storage[rear] = itemProduced;
                    if (front == -1)
                        front = 0;
                }
                break;
            case 2:
                if (front == -1)
                    cout << "\nStorage is Empty\n";
                else {
                    itemConsumed = storage[front];
                    cout << "\nThe consumed value is " << itemConsumed;
                    if (front == rear)
                        front = rear = -1;
                    else
                        front = (front + 1) % size;
                }
                break;
        }
    }
    return 0;
}
