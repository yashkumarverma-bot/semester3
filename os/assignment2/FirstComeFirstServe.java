
/**
 * @author: YashKumarVerma
 * @description: First Come first serve implementation in JAVA
 */
import java.text.ParseException;
import java.util.Scanner;

class FirstComeFirstServe {

    /** Function to find the waiting time for all processes */
    static void findWaitingTime(int processes[], int n, int burstTime[], int waitingTime[]) {
        /** first process is loaded instantly */
        waitingTime[0] = 0;

        /** calculating waiting time */
        for (int i = 1; i < n; i++) {
            waitingTime[i] = burstTime[i - 1] + waitingTime[i - 1];
        }
    }

    /** Calculating turn around time of process */
    static void findTurnAroundTime(int processes[], int n, int burstTime[], int waitingTime[], int turnAroundTime[]) {
        /** turnAroundTime(i) = burstTime(i) + waitingTime(i) */
        for (int i = 0; i < n; i++) {
            turnAroundTime[i] = burstTime[i] + waitingTime[i];
        }
    }

    /** calculating average time */
    static void findAverageTime(int processes[], int n, int burstTime[]) {
        int waitingTime[] = new int[n], turnoutTime[] = new int[n];
        int totalWaitingTime = 0, totalTurnoutTime = 0;

        /** calculating total waiting time */
        findWaitingTime(processes, n, burstTime, waitingTime);

        /** calculating total turn-around time */
        findTurnAroundTime(processes, n, burstTime, waitingTime, turnoutTime);

        /** displaying all details */
        System.out.printf("Processes Burst time Waiting" + " time Turn around time\n");

        /** calculate total waiting time and total turn-around time */
        for (int i = 0; i < n; i++) {
            totalWaitingTime = totalWaitingTime + waitingTime[i];
            totalTurnoutTime = totalTurnoutTime + turnoutTime[i];
            System.out.printf(" %d ", (i + 1));
            System.out.printf("     %d ", burstTime[i]);
            System.out.printf("     %d", waitingTime[i]);
            System.out.printf("     %d\n", turnoutTime[i]);
        }

        float s = (float) totalWaitingTime / (float) n;
        int t = totalTurnoutTime / n;
        System.out.printf("Average waiting time = %f\n", s);
        System.out.printf("Average turn around time = %d ", t);
        System.out.println();
    }

    /** driver code */
    public static void main(String[] args) throws ParseException {
        Scanner handler = new Scanner(System.in);

        System.out.print("Enter the number of processes :");
        int n = handler.nextInt();
        int temp;
        int processes[] = new int[n];
        int burstTime[] = new int[n];

        for (int i = 0; i < n; i++) {
            System.out.print("Enter Burst Time for process #" + i + " : ");
            processes[i] = i;
            burstTime[i] = handler.nextInt();
        }

        findAverageTime(processes, n, burstTime);
    }
}