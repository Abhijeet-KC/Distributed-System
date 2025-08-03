#include <iostream>
#include <vector>
using namespace std;

// Function to get the maximum of two numbers
int getMax(int a, int b) {
    return (a > b) ? a : b;
}

// Function to print the logical timestamps
void showClocks(int count1, int count2, const vector<int>& clk1, const vector<int>& clk2) {
    cout << "\nTimestamps of events in Process 1:\n";
    for (int i = 0; i < count1; i++) {
        cout << clk1[i] << " ";
    }

    cout << "\nTimestamps of events in Process 2:\n";
    for (int i = 0; i < count2; i++) {
        cout << clk2[i] << " ";
    }
    cout << endl;
}

// Function to calculate Lamport Logical Clocks
void LamportClock(int eventsP1, int eventsP2, int relation[][3]) {
    vector<int> clk1(eventsP1, 1);  // initialize clocks to 1
    vector<int> clk2(eventsP2, 1);

    // Update clocks for process 1 (increment by 1 for each event)
    for (int i = 1; i < eventsP1; i++) {
        clk1[i] = clk1[i - 1] + 1;
    }

    // Update clocks for process 2 (increment by 1 for each event)
    for (int i = 1; i < eventsP2; i++) {
        clk2[i] = clk2[i - 1] + 1;
    }

    // Adjust clocks based on the relation matrix
    for (int i = 0; i < eventsP1; i++) {
        for (int j = 0; j < eventsP2; j++) {
            if (relation[i][j] == 1) {
                // Event in process 1 happened before event in process 2
                clk2[j] = getMax(clk2[j], clk1[i] + 1);
                // Update subsequent clocks in process 2 to maintain order
                for (int k = j + 1; k < eventsP2; k++) {
                    clk2[k] = getMax(clk2[k], clk2[k - 1] + 1);
                }
            }
        }
    }

    showClocks(eventsP1, eventsP2, clk1, clk2);
}

int main() {
    int eventsP1 = 5, eventsP2 = 3;
    int relation[5][3] = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, -1}
    };

    LamportClock(eventsP1, eventsP2, relation);

    return 0;
}
