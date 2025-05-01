#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 100

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int waiting_time;
    int turnaround_time;
} Process;

void input_processes(Process processes[], int *n, int with_priority, int with_remaining_time) {
    printf("Enter number of processes: ");
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        processes[i].process_id = i + 1;
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        if (with_priority) {
            printf("Priority (lower is higher): ");
            scanf("%d", &processes[i].priority);
        } else {
            processes[i].priority = 0;
        }
        if (!with_remaining_time) {
            processes[i].remaining_time = 0;
        }
    }
}

void print_results(Process processes[], int n, float total_waiting_time, float total_turnaround_time, int with_priority) {
    printf("\nProcess\tArrival\tBurst");
    if (with_priority) printf("\tPriority");
    printf("\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d", 
               processes[i].process_id, 
               processes[i].arrival_time,
               processes[i].burst_time);
        if (with_priority) printf("\t%d", processes[i].priority);
        printf("\t%d\t%d\n", 
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }
    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

void fcfs(Process processes[], int n) {
    int current_time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        current_time += processes[i].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    printf("\nFCFS Scheduling Results:");
    print_results(processes, n, total_waiting_time, total_turnaround_time, 0);
}

void sjf(Process processes[], int n) {
    int current_time = 0, completed = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;
    int remaining_time[n];

    for (int i = 0; i < n; i++) remaining_time[i] = processes[i].burst_time;

    while (completed != n) {
        int shortest = -1, min_time = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && 
                remaining_time[i] > 0 && 
                remaining_time[i] < min_time) {
                shortest = i;
                min_time = remaining_time[i];
            }
        }
        if (shortest == -1) {
            current_time++;
            continue;
        }
        remaining_time[shortest]--;
        if (remaining_time[shortest] == 0) {
            completed++;
            int finish_time = current_time + 1;
            processes[shortest].waiting_time = finish_time - processes[shortest].burst_time - processes[shortest].arrival_time;
            processes[shortest].turnaround_time = finish_time - processes[shortest].arrival_time;

            total_waiting_time += processes[shortest].waiting_time;
            total_turnaround_time += processes[shortest].turnaround_time;
        }
        current_time++;
    }
    printf("\nSJF Scheduling Results:");
    print_results(processes, n, total_waiting_time, total_turnaround_time, 0);
}

void priority_scheduling(Process processes[], int n) {
    int current_time = 0, completed = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    while (completed < n) {
        int highest_priority = INT_MAX, selected = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && 
                processes[i].priority < highest_priority && 
                processes[i].remaining_time > 0) {
                highest_priority = processes[i].priority;
                selected = i;
            }
        }
        if (selected == -1) {
            current_time++;
            continue;
        }
        processes[selected].remaining_time--;
        if (processes[selected].remaining_time == 0) {
            completed++;
            int finish_time = current_time + 1;
            processes[selected].waiting_time = finish_time - processes[selected].burst_time - processes[selected].arrival_time;
            processes[selected].turnaround_time = finish_time - processes[selected].arrival_time;

            total_waiting_time += processes[selected].waiting_time;
            total_turnaround_time += processes[selected].turnaround_time;
        }
        current_time++;
    }
    printf("\nPriority Scheduling Results:");
    print_results(processes, n, total_waiting_time, total_turnaround_time, 1);
}

void round_robin(Process processes[], int n, int quantum) {
    int current_time = 0, completed = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                done = 0;
                int exec_time = (processes[i].remaining_time < quantum) ? processes[i].remaining_time : quantum;
                processes[i].remaining_time -= exec_time;
                current_time += exec_time;
                if (processes[i].remaining_time == 0) {
                    completed++;
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    total_waiting_time += processes[i].waiting_time;
                    total_turnaround_time += processes[i].turnaround_time;
                }
            }
        }
        if (done) break;
    }
    printf("\nRound Robin Scheduling Results:");
    print_results(processes, n, total_waiting_time, total_turnaround_time, 0);
}

int main() {
    Process processes[MAX_PROCESSES];
    int n, choice;

    printf("Select Scheduling Algorithm:\n");
    printf("1. FCFS\n2. SJF\n3. Priority\n4. Round Robin\nEnter choice (1-4): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            input_processes(processes, &n, 0, 0);
            fcfs(processes, n);
            break;
        case 2:
            input_processes(processes, &n, 0, 1);
            sjf(processes, n);
            break;
        case 3:
            input_processes(processes, &n, 1, 1);
            priority_scheduling(processes, n);
            break;
        case 4: {
            int quantum;
            printf("Enter Time Quantum: ");
            scanf("%d", &quantum);
            input_processes(processes, &n, 0, 1);
            round_robin(processes, n, quantum);
            break;
        }
        default:
            printf("Invalid choice.\n");
    }
    return 0;
}