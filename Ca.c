#include <stdio.h>
#include <stdlib.h>

struct Process {
  int id;
  int arrivalTime;
  int burstTime;
  int priority;
  int waitingTime;  
};

int arrivalCompare(const void* a, const void* b) {
  struct Process* p1 = (struct Process*)a;
  struct Process* p2 = (struct Process*)b;
  return p1->arrivalTime - p2->arrivalTime;
}

int main() {

  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  struct Process* processes = malloc(n * sizeof(struct Process));

  for(int i=0; i<n; i++) {
    printf("Enter arrival time for P%d: ", i+1);
    scanf("%d", &processes[i].arrivalTime);
    printf("Enter burst time for P%d: ", i+1);
    scanf("%d", &processes[i].burstTime);
    processes[i].id = i+1;
    processes[i].priority = 0;
  }

 
  qsort(processes, n, sizeof(struct Process), arrivalCompare);

  int currentTime = 0;
  int completed = 0;
  int prevExecuted = -1;  

  while(completed != n) {

    int idx = -1;
    int maxPriority = -1;

    for(int i=0; i<n; i++) {
      if(processes[i].arrivalTime <= currentTime && 
         processes[i].burstTime > 0) {
        if(processes[i].priority > maxPriority) {
          maxPriority = processes[i].priority;
          idx = i;
        }
      }
    }

    if(idx != -1) {
      if(prevExecuted != idx) {
        processes[idx].priority += 1;
      }

      processes[idx].burstTime--;
      currentTime++;

      if(processes[idx].burstTime == 0) {
        processes[idx].waitingTime = currentTime - processes[idx].arrivalTime - 1;
        completed++;
        prevExecuted = idx;
      }

    } else {
      for(int i=0; i<n; i++) {
        if(processes[i].arrivalTime <= currentTime &&
           processes[i].burstTime > 0) {
           processes[i].priority += 2;
        }
      }
      currentTime++;
    }
  }

  float totalWaitingTime = 0;
  for(int i=0; i<n; i++) {
    totalWaitingTime += processes[i].waitingTime;
  }

  printf("Average waiting time: %.2f\n", totalWaitingTime/n);

  return 0;
 }
