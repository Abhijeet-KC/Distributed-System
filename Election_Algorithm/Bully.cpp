#include <iostream>
#include <vector>
using namespace std;

const int MAX_NODES = 10;
int n; // number of processes
vector<int> processes(MAX_NODES);
vector<bool> alive(MAX_NODES, true);
int coordinator = -1;

// Function to start election from process id (index)
void startElection(int id) {
    cout << "\nProcess " << processes[id] << " starts an election.\n";
    bool higherExists = false;

    // Send election message to all higher processes
    for (int i = id + 1; i < n; i++) {
        if (alive[i]) {
            cout << "Process " << processes[id] << " sends election message to Process " << processes[i] << ".\n";
            higherExists = true;
        }
    }

    if (higherExists) {
        cout << "Process " << processes[id] << " waits for responses...\n";
        // Assume higher processes take over election
        for (int i = id + 1; i < n; i++) {
            if (alive[i]) {
                startElection(i);
                return;
            }
        }
    }

    // No higher process alive, declare self as coordinator
    coordinator = processes[id];
    cout << "Process " << processes[id] << " becomes the coordinator.\n";
}

// Utility to show current coordinator
void showCoordinator() {
    if (coordinator == -1) {
        cout << "\nNo coordinator elected.\n";
    } else {
        cout << "\nCurrent coordinator is Process " << coordinator << ".\n";
    }
}

int main() {
    cout << "Enter number of processes (max " << MAX_NODES << "): ";
    cin >> n;
    
    cout << "Enter process IDs (in increasing order):\n";
    for (int i = 0; i < n; i++) {
        cin >> processes[i];
        alive[i] = true; // all processes start as alive
    }

    coordinator = processes[n - 1]; // highest ID is coordinator at start
    cout << "\nInitially, Process " << coordinator << " is the coordinator.\n";

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Fail a process\n";
        cout << "2. Recover a process\n";
        cout << "3. Start election from a process\n";
        cout << "4. Show coordinator\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        int pid, index;
        switch (choice) {
            case 1:
                cout << "Enter process ID to fail: ";
                cin >> pid;
                index = -1;
                for (int i = 0; i < n; i++) {
                    if (processes[i] == pid) {
                        index = i;
                        break;
                    }
                }
                if (index != -1) {
                    alive[index] = false;
                    cout << "Process " << pid << " failed.\n";
                    if (pid == coordinator) {
                        cout << "Coordinator failed! Need election.\n";
                    }
                } else {
                    cout << "Process ID not found.\n";
                }
                break;

            case 2:
                cout << "Enter process ID to recover: ";
                cin >> pid;
                index = -1;
                for (int i = 0; i < n; i++) {
                    if (processes[i] == pid) {
                        index = i;
                        break;
                    }
                }
                if (index != -1) {
                    alive[index] = true;
                    cout << "Process " << pid << " recovered.\n";
                    startElection(index);
                } else {
                    cout << "Process ID not found.\n";
                }
                break;

            case 3:
                cout << "Enter process ID to start election: ";
                cin >> pid;
                index = -1;
                for (int i = 0; i < n; i++) {
                    if (processes[i] == pid) {
                        index = i;
                        break;
                    }
                }
                if (index != -1) {
                    if (alive[index]) {
                        startElection(index);
                    } else {
                        cout << "Process " << pid << " is failed, cannot start election.\n";
                    }
                } else {
                    cout << "Process ID not found.\n";
                }
                break;

            case 4:
                showCoordinator();
                break;

            case 5:
                cout << "Exiting.\n";
                break;

            default:
                cout << "Invalid choice.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
