#include <iostream>
#include <vector>
using namespace std;

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int num_processes, num_resources;
int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int safeSequence[MAX_PROCESSES];

void calculateNeed() {
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

bool isSafeState() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int count = 0;

    // Initialize work = available
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    while (count < num_processes) {
        bool found = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < num_resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

int main() {
    cout << "Enter number of processes: ";
    cin >> num_processes;
    cout << "Enter number of resources: ";
    cin >> num_resources;

    cout << "Enter available resources:\n";
    for (int i = 0; i < num_resources; i++) {
        cin >> available[i];
    }

    cout << "Enter maximum demand matrix:\n";
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            cin >> maximum[i][j];
        }
    }

    cout << "Enter allocation matrix:\n";
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            cin >> allocation[i][j];
        }
    }

    calculateNeed();

    if (isSafeState()) {
        cout << "The system is in a safe state.\nSafe sequence is: ";
        for (int i = 0; i < num_processes; i++) {
            cout << "P" << safeSequence[i];
            if (i < num_processes - 1)
                cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "The system is in an unsafe state.\n";
    }

    return 0;
}
