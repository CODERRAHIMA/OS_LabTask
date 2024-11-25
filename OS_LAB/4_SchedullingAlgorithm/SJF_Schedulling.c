#include <stdio.h>
void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    int completion_time[n];
    completion_time[0] = bt[0];
    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        completion_time[i] = completion_time[i-1] + bt[i-1];
        wt[i] = completion_time[i] - bt[i];
    }
}

void findTurnaroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAverageTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n];
    findWaitingTime(processes, n, bt, wt);
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

    findAverageTime(processes, n, burst_time);
    return 0;
}

// output:
// Process   Burst Time   Waiting Time   Turnaround Time
// 1         6            0              6
// 3         7            6              13
// 2         8            13             21

// Average Waiting Time: 6.33
// Average Turnaround Time: 13.33
