#include <stdio.h>
#include <stdbool.h> //for using bool data type

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Function to check if resources can be allocated to a process
bool canAllocate(int need[], int available[], int numResources) {
    for (int i = 0; i < numResources; i++) {
        if (need[i] > available[i])
            return false;
    }
    return true;
}

// Safety Algorithm
bool isSafeState(int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES],
                 int available[], int numProcesses, int numResources,
                 int safeSequence[]) {
    int need[MAX_PROCESSES][MAX_RESOURCES];   //to store the resources each process still needs.
    bool finish[MAX_PROCESSES] = {false};   //to track whether each process has finished execution.
    int work[MAX_RESOURCES];   //to simulate the available resources during the algorithm's steps.

    // Calculate Need matrix
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }            //current resource need = max need - allocated resources
    }

    // Initialize work with available resources
    for (int i = 0; i < numResources; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < numProcesses) {   //continues until all processes are checked
        bool foundProcess = false;     //keeps track if a process is found in the current iteration that can finish.
        
        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i] && canAllocate(need[i], work, numResources)) {   //If the process i is not finished (!finish[i]) and its need can be satisfied by the current work resources (canAllocate), it is simulated as "finished."
                // If we can allocate to process i, assume allocation
                for (int j = 0; j < numResources; j++) {
                    work[j] += allocation[i][j];    //Updates work by adding back the resources allocated to process i.
                }
                safeSequence[count++] = i;    //Adds process i to the safeSequence array.
                finish[i] = true;         //Marks the process as finished (finish[i] = true) 
                foundProcess = true;       //sets foundProcess = true.
            }
        }

        // If no process can proceed, the system is in an unsafe state, and the function exits returning false.
        if (!foundProcess) return false;
    }

    // If we finished all processes, we are in a safe state
    return true;
}

int main() {
    int numProcesses, numResources;  //5 3
    int max[MAX_PROCESSES][MAX_RESOURCES];  //max[5][3]
    int allocation[MAX_PROCESSES][MAX_RESOURCES]; //allocation[5][3]
    int available[MAX_RESOURCES];   //available[3]
    int safeSequence[MAX_PROCESSES];   //safeSequence[5]

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    printf("Enter the Max matrix:\n");           
    for (int i = 0; i < numProcesses; i++) {     
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &max[i][j]);       
        }
    }

    printf("Enter the Allocation matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Available resources vector:\n");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    if (isSafeState(max, allocation, available, numProcesses, numResources, safeSequence)) {
        printf("The system is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < numProcesses; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    return 0;
}


// input:
// Enter the number of processes: 5
// Enter the number of resources: 3
// Enter the Max matrix:
// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3
// Enter the Allocation matrix:
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2
// Enter the Available resources vector:
// 3 3 2

// output:
// The system is in a safe state.
// Safe sequence is: P1 P3 P4 P0 P2