#include <stdio.h>
void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum) {
    int remaining_bt[n];  //to hold remaining burst time for each process
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];  //Initialize remaining burst time to the initial burst time
    }

    int time = 0;   // Current time variable
    while (1) {    // Infinite loop until all processes are completed
        int done = 1;   // Flag to check if all processes are completed
        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0) {   // If the process still has remaining burst time
                done = 0;   // Mark that at least one process is still running
                if (remaining_bt[i] > quantum) {
                    time += quantum;   // Process gets executed for a quantum time
                    remaining_bt[i] -= quantum;    // Decrease the remaining burst time
                } else {
                    time += remaining_bt[i];    // Process completes execution
                    wt[i] = time - bt[i];     // Calculate waiting time (time - burst time)
                    remaining_bt[i] = 0;    // Mark the process as finished (remaining burst time becomes 0)
                }
            }
        }
        if (done) break;   // If all processes are done (remaining_bt[i] = 0 for all), break the loop
    }
}

void findTurnaroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];  // Turnaround time = Burst time + Waiting time
    }
}

void findAverageTime(int processes[], int n, int bt[], int quantum) {
    int wt[n], tat[n];
    findWaitingTime(processes, n, bt, wt, quantum);
    findTurnaroundTime(processes, n, bt, wt, tat);

    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = {6, 8, 7};
    int quantum = 4; // Time quantum

    findAverageTime(processes, n, burst_time, quantum);
    return 0;
}

// output:

// Process Burst Time      Waiting Time    Turnaround Time
// 1               6               8               14
// 2               8               10              18
// 3               7               14              21

// Average Waiting Time: 10.67
// Average Turnaround Time: 17.67


