
import java.util.Scanner;

public class RoundRobbin {
    /** calculate waiting time for all processes */
    static void findWaitingTime(int processes[], int n, int burstTime[], int waitingTime[], int quantum) {
        int t = 0;
        int remainingBurstTime[] = new int[n];
        for (int i = 0; i < n; i++) {
            remainingBurstTime[i] = burstTime[i];
        }

        /** Keep traversing processes in round robin manner until all not done. */
        while (true) {
            boolean done = true;

            /** traverse all processes one by one */
            for (int i = 0; i < n; i++) {
                /** if burst time of a process is greater than 0, only then process it */
                if (remainingBurstTime[i] > 0) {
                    /** processing still pending */
                    done = false;

                    if (remainingBurstTime[i] > quantum) {
                        /** increase the value of t, shows how much time has been passed */
                        t += quantum;

                        /** decrease the burst time of current process */
                        remainingBurstTime[i] -= quantum;
                    }

                    /** if burst time <= quantum, last cycle for this process */
                    else {
                        /**
                         * increase the value of t, i.e. shows how much time a process has been
                         * processed
                         */
                        t = t + remainingBurstTime[i];

                        /** waiting time is current time - time used by this process */
                        waitingTime[i] = t - burstTime[i];

                        /** as the process gets fully executed, set remaining burst time to 0 */
                        remainingBurstTime[i] = 0;
                    }
                }
            }

            /** processing complete */
            if (done == true)
                break;
        }
    }

    /** calculating turn-around time */
    static void findTurnAroundTime(int processes[], int n, int burstTime[], int waitingTime[], int turnAroundTime[]) {
        for (int i = 0; i < n; i++) {
            turnAroundTime[i] = burstTime[i] + waitingTime[i];
        }
    }

    /** calculating average time */
    static void fineAverageTime(int processes[], int n, int burstTime[], int quantum) {
        int waitingTime[] = new int[n], turnAroundTime[] = new int[n];
        int total_wt = 0, total_tat = 0;

        /** find waiting time of all processes */
        findWaitingTime(processes, n, burstTime, waitingTime, quantum);

        /** find turn-around time of all processes */
        findTurnAroundTime(processes, n, burstTime, waitingTime, turnAroundTime);

        /** display processes along with all details */
        System.out.println("Processes " + " Burst time " + " Waiting time " + " Turn around time");

        /** calculate total times */
        for (int i = 0; i < n; i++) {
            total_wt = total_wt + waitingTime[i];
            total_tat = total_tat + turnAroundTime[i];
            System.out.println(
                    " " + (i + 1) + "\t\t" + burstTime[i] + "\t " + waitingTime[i] + "\t\t " + turnAroundTime[i]);
        }

        System.out.println("Average waiting time = " + (float) total_wt / (float) n);
        System.out.println("Average turn around time = " + (float) total_tat / (float) n);
    }

    // Driver Method
    public static void main(String[] args) {
        Scanner handler = new Scanner(System.in);
        System.out.print("Enter the quantum of time : ");
        int quantum = handler.nextInt();

        System.out.print("Enter the number of processes : ");
        int n = handler.nextInt();

        int processes[] = new int[n];
        int burstTime[] = new int[n];

        for (int i = 0; i < n; i++) {
            System.out.print("Enter burst time of process : #" + (i + 1) + " => ");
            processes[i] = i;
            burstTime[i] = handler.nextInt();
        }

        fineAverageTime(processes, n, burstTime, quantum);
    }
}