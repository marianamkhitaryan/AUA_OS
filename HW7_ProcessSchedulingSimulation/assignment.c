#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
} Process;

void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time ||
                (p[j].arrival_time == p[j + 1].arrival_time &&
                 p[j].pid > p[j + 1].pid)) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void printResults(Process p[], int n, const char *algorithm,
                  int order[], int start[], int finish[]) {
    double totalWT = 0, totalTAT = 0, totalRT = 0;

    printf("\n=== %s ===\n", algorithm);

    printf("Gantt Chart:\n");
    for (int i = 0; i < n; i++)
        printf("+--------");
    printf("+\n");

    for (int i = 0; i < n; i++)
        printf("|   P%-4d", p[order[i]].pid);
    printf("|\n");

    for (int i = 0; i < n; i++)
        printf("+--------");
    printf("+\n");

    printf("%-8s %-7s %-7s %-7s %-7s %-7s\n",
           "PID", "AT", "BT", "WT", "TAT", "RT");

    // Display results in original PID order.
    for (int pid = 1; pid <= n; pid++) {
        for (int i = 0; i < n; i++) {
            if (p[i].pid == pid) {
                printf("%-8d %-7d %-7d %-7d %-7d %-7d\n",
                       p[i].pid, p[i].arrival_time, p[i].burst_time,
                       p[i].waiting_time, p[i].turnaround_time,
                       p[i].response_time);

                totalWT += p[i].waiting_time;
                totalTAT += p[i].turnaround_time;
                totalRT += p[i].response_time;
                break;
            }
        }
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Response Time: %.2f\n", totalRT / n);

    printf("\nTimeline:\n");
    printf("%d", start[0]);
    for (int i = 0; i < n; i++)
        printf("\t%d", finish[i]);
    printf("\n");
}

void fcfs(Process processes[], int n) {
    Process p[MAX_PROCESSES];
    int order[MAX_PROCESSES], start[MAX_PROCESSES];
    int finish[MAX_PROCESSES];
    int current_time = 0;

    for (int i = 0; i < n; i++)
        p[i] = processes[i];

    sortByArrival(p, n);

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time)
            current_time = p[i].arrival_time;

        order[i] = i;
        start[i] = current_time;

        p[i].waiting_time = current_time - p[i].arrival_time;
        p[i].response_time = p[i].waiting_time;

        current_time += p[i].burst_time;
        finish[i] = current_time;

        p[i].turnaround_time = current_time - p[i].arrival_time;
    }

    printResults(p, n, "First Come First Served (FCFS)",
                 order, start, finish);
}

void sjf(Process processes[], int n) {
    Process p[MAX_PROCESSES];
    int order[MAX_PROCESSES], start[MAX_PROCESSES];
    int finish[MAX_PROCESSES];
    int completed[MAX_PROCESSES] = {0};
    int current_time = 0;

    for (int i = 0; i < n; i++)
        p[i] = processes[i];

    for (int count = 0; count < n; count++) {
        int shortest = -1;

        for (int i = 0; i < n; i++) {
            if (!completed[i] &&
                p[i].arrival_time <= current_time) {
                if (shortest == -1 ||
                    p[i].burst_time < p[shortest].burst_time ||
                    (p[i].burst_time == p[shortest].burst_time &&
                     (p[i].arrival_time < p[shortest].arrival_time ||
                      (p[i].arrival_time == p[shortest].arrival_time &&
                       p[i].pid < p[shortest].pid)))) {
                    shortest = i;
                }
            }
        }

        // If no process has arrived, move time to the next arrival.
        if (shortest == -1) {
            int next = -1;

            for (int i = 0; i < n; i++) {
                if (!completed[i] &&
                    (next == -1 ||
                     p[i].arrival_time < p[next].arrival_time ||
                     (p[i].arrival_time == p[next].arrival_time &&
                      p[i].pid < p[next].pid))) {
                    next = i;
                }
            }

            current_time = p[next].arrival_time;
            count--;
            continue;
        }

        completed[shortest] = 1;
        order[count] = shortest;
        start[count] = current_time;

        p[shortest].waiting_time =
            current_time - p[shortest].arrival_time;
        p[shortest].response_time = p[shortest].waiting_time;

        current_time += p[shortest].burst_time;
        finish[count] = current_time;

        p[shortest].turnaround_time =
            current_time - p[shortest].arrival_time;
    }

    // Reorder the process array for displaying results by PID.
    Process results[MAX_PROCESSES];
    for (int i = 0; i < n; i++)
        results[i] = p[i];

    printResults(results, n, "Shortest Job First (SJF)",
                 order, start, finish);
}

int main(void) {
    Process processes[MAX_PROCESSES];
    int n;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_PROCESSES) {
        printf("Invalid number of processes. Use 1-%d.\n",
               MAX_PROCESSES);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;

        printf("Enter the arrival time and burst time for process %d: ",
               i + 1);

        if (scanf("%d %d",
                  &processes[i].arrival_time,
                  &processes[i].burst_time) != 2 ||
            processes[i].arrival_time < 0 ||
            processes[i].burst_time <= 0) {
            printf("Invalid input. Arrival must be >= 0 and "
                   "burst time must be > 0.\n");
            return 1;
        }
    }

    fcfs(processes, n);
    sjf(processes, n);

    return 0;
}
