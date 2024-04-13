// C++ Program to Creating 
// Multiple processes 
// Using a fork 
#include <iostream> 
#include <unistd.h> 
using namespace std; 

int main() 
{ 
    fork(); 
    fork(); 
    cout << "GeeksforGeeks" << endl; 

    return 0; 
}
