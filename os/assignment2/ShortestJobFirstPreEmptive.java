/** class to materialize a process, and store all its details */
class Process {
    int processId;
    int burstTime;
    int arrivalTime;

    public Process(int processId, int burstTime, int arrivalTime) {
        this.processId = processId;
        this.burstTime = burstTime;
        this.arrivalTime = arrivalTime;
    }
}

public class ShortestJobFirstPreEmptive {
    /** calculate the waiting time of all processes */
    static void findWaitingTime(Process proc[], int n, int waitingTime[]) {
        int rt[] = new int[n];

        for (int i = 0; i < n; i++)
            rt[i] = proc[i].burstTime;

        int complete = 0, t = 0, minimum = Integer.MAX_VALUE;
        int shortest = 0, finish_time;
        boolean check = false;

        /** Process until all processes gets completed */
        while (complete != n) {

            /**
             * finding process with minimum remaining time among the processes that arrives
             * till the current time
             */
            for (int j = 0; j < n; j++) {
                if ((proc[j].arrivalTime <= t) && (rt[j] < minimum) && rt[j] > 0) {
                    minimum = rt[j];
                    shortest = j;
                    check = true;
                }
            }

            if (check == false) {
                t++;
                continue;
            }

            /** Reduce remaining time by one */
            rt[shortest]--;

            /** update minimum */
            minimum = rt[shortest];
            if (minimum == 0)
                minimum = Integer.MAX_VALUE;

            /** If a process gets completely executed */
            if (rt[shortest] == 0) {
                complete++;
                check = false;

                /** Find finish time of current process */
                finish_time = t + 1;

                /** calculate the waiting time */
                waitingTime[shortest] = finish_time - proc[shortest].burstTime - proc[shortest].arrivalTime;

                if (waitingTime[shortest] < 0)
                    waitingTime[shortest] = 0;
            }
            t++;
        }
    }

    /** calculate turn-around time of all processes */
    static void findTurnAroundTime(Process proc[], int n, int waitingTime[], int tat[]) {
        for (int i = 0; i < n; i++)
            tat[i] = proc[i].burstTime + waitingTime[i];
    }

    /** calculate average runtime of all processes */
    static void findavgTime(Process proc[], int n) {
        int waitingTime[] = new int[n], tat[] = new int[n];
        int total_wt = 0, total_tat = 0;

        /** Function to find waiting time of all processes */
        findWaitingTime(proc, n, waitingTime);

        /** Function to find turn around time for all processes */
        findTurnAroundTime(proc, n, waitingTime, tat);

        /** Display processes along with all details */
        System.out.println("Processes " + " Burst time " + " Waiting time " + " Turn around time");

        /** Calculate total waiting time and total turn-around time */
        for (int i = 0; i < n; i++) {
            total_wt = total_wt + waitingTime[i];
            total_tat = total_tat + tat[i];
            System.out.println(
                    " " + proc[i].processId + "\t\t" + proc[i].burstTime + "\t\t " + waitingTime[i] + "\t\t" + tat[i]);
        }

        System.out.println("Average waiting time = " + (float) total_wt / (float) n);
        System.out.println("Average turn around time = " + (float) total_tat / (float) n);
    }

    /** driver function */
    public static void main(String[] args) {
        Process proc[] = { new Process(1, 6, 1), new Process(2, 8, 1), new Process(3, 7, 2), new Process(4, 3, 3) };
        findavgTime(proc, proc.length);
    }
}