
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        cerr << "Error: Fork failed" << endl;
        return 1;
    }
    else if (pid == 0)
    {
        cout << "Child process: My PID is " << getpid() << endl;
        cout << "Child process: My parent's PID is " << getppid() << endl;

        // Perform child-specific operations here

        return 0;
    }
    else
    {
        cout << "Parent process: I have a child with PID " << pid << endl;
        cout << "Parent process: My PID is " << getpid() << endl;

        // Perform parent-specific operations here

        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}
