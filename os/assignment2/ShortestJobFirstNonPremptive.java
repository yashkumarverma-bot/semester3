import java.util.*;

public class ShortestJobFirstNonPremptive {

    /** store data about process */
    static int[][] processData = new int[10][6];

    /** sort processes based shortest first */
    static void arrangeArrival(int num, int[][] processData) {
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num - i - 1; j++) {
                if (processData[j][1] > processData[j + 1][1]) {
                    for (int k = 0; k < 5; k++) {
                        int temp = processData[j][k];
                        processData[j][k] = processData[j + 1][k];
                        processData[j + 1][k] = temp;
                    }
                }
            }
        }
    }

    /** calculating completion time */
    static void completionTime(int num, int[][] processData) {
        int temp, val = -1;
        processData[0][3] = processData[0][1] + processData[0][2];
        processData[0][5] = processData[0][3] - processData[0][1];
        processData[0][4] = processData[0][5] - processData[0][2];

        for (int i = 1; i < num; i++) {
            temp = processData[i - 1][3];
            int low = processData[i][2];
            for (int j = i; j < num; j++) {
                if (temp >= processData[j][1] && low >= processData[j][2]) {
                    low = processData[j][2];
                    val = j;
                }
            }

            processData[val][3] = temp + processData[val][2];
            processData[val][5] = processData[val][3] - processData[val][1];
            processData[val][4] = processData[val][5] - processData[val][2];
            for (int k = 0; k < 6; k++) {
                int tem = processData[val][k];
                processData[val][k] = processData[i][k];
                processData[i][k] = tem;
            }
        }
    }

    /** driver code */
    public static void main(String[] args) {
        int num;
        Scanner handler = new Scanner(System.in);

        System.out.print("Enter number of Process: ");
        num = handler.nextInt();

        /** enter data about processes from terminal */
        System.out.println("Enter the process details : ");
        for (int i = 0; i < num; i++) {
            System.out.println("Process " + (i + 1) + "...");
            System.out.print("Enter Process Id: ");
            processData[i][0] = handler.nextInt();
            System.out.print("Enter Arrival Time: ");
            processData[i][1] = handler.nextInt();
            System.out.print("Enter Burst Time: ");
            processData[i][2] = handler.nextInt();
        }

        System.out.println("Before Arrange...");
        System.out.println("Process ID\tArrival Time\tBurst Time");
        for (int i = 0; i < num; i++) {
            System.out.printf("%d\t\t%d\t\t%d\n", processData[i][0], processData[i][1], processData[i][2]);
        }

        arrangeArrival(num, processData);
        completionTime(num, processData);
        System.out.println("Final Result...");
        System.out.println("Process ID\tArrival Time\tBurst" + " Time\tWaiting Time\tTurnaround Time");
        for (int i = 0; i < num; i++) {
            System.out.printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processData[i][0], processData[i][1], processData[i][2],
                    processData[i][4], processData[i][5]);
        }
        handler.close();
    }
}