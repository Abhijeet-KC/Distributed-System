#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class RingElection {
private:
    int n;
    vector<int> processes;
    vector<bool> alive;
    int coordinator;

public:
    RingElection() : coordinator(-1) {}

    void initialize() {
        cout << "Enter number of processes: ";
        cin >> n;
        processes.resize(n);
        alive.resize(n, true);

        cout << "Enter process IDs (any order):\n";
        for (int i = 0; i < n; ++i) {
            cin >> processes[i];
        }

        // Set initial coordinator to process with highest ID
        coordinator = *max_element(processes.begin(), processes.end());
        cout << "\nInitially, Process " << coordinator << " is the coordinator.\n";
    }

    void startElection(int startIndex) {
        cout << "\nProcess " << processes[startIndex] << " starts an election.\n";
        vector<int> electionIDs;

        int index = startIndex;
        do {
            if (alive[index]) {
                electionIDs.push_back(processes[index]);
                cout << "Process " << processes[index] << " adds its ID to election message.\n";
            }
            index = (index + 1) % n;
        } while (index != startIndex);

        coordinator = *max_element(electionIDs.begin(), electionIDs.end());
        cout << "Process " << coordinator << " becomes the coordinator.\n";
    }

    void showCoordinator() const {
        if (coordinator == -1) {
            cout << "\nNo coordinator elected.\n";
        } else {
            cout << "\nCurrent coordinator is Process " << coordinator << ".\n";
        }
    }

    void failProcess() {
        int pid;
        cout << "Enter process ID to fail: ";
        cin >> pid;

        int index = findProcessIndex(pid);
        if (index == -1) {
            cout << "Invalid process ID.\n";
            return;
        }

        alive[index] = false;
        cout << "Process " << pid << " failed.\n";

        if (pid == coordinator) {
            cout << "Coordinator failed! Need election.\n";
        }
    }

    void recoverProcess() {
        int pid;
        cout << "Enter process ID to recover: ";
        cin >> pid;

        int index = findProcessIndex(pid);
        if (index == -1) {
            cout << "Invalid process ID.\n";
            return;
        }

        alive[index] = true;
        cout << "Process " << pid << " recovered.\n";
        startElection(index);
    }

    void manualElection() {
        int pid;
        cout << "Enter process ID to start election: ";
        cin >> pid;

        int index = findProcessIndex(pid);
        if (index == -1) {
            cout << "Invalid process ID.\n";
            return;
        }

        if (alive[index]) {
            startElection(index);
        } else {
            cout << "Process " << pid << " is failed, cannot start election.\n";
        }
    }

    void menu() {
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

            switch (choice) {
                case 1: failProcess(); break;
                case 2: recoverProcess(); break;
                case 3: manualElection(); break;
                case 4: showCoordinator(); break;
                case 5: cout << "Exiting.\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    }

private:
    int findProcessIndex(int pid) const {
        for (int i = 0; i < n; ++i) {
            if (processes[i] == pid) return i;
        }
        return -1;
    }
};

int main() {
    RingElection ring;
    ring.initialize();
    ring.menu();
    return 0;
}
