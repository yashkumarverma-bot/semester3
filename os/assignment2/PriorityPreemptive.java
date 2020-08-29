import java.util.Scanner;
import java.util.Arrays;

public class PriorityPreemptive {
    class Process {
        int at, bt, pr, ct, ta, wt;
        String pro_id;
    }

    Boolean compare(Process a, Process b) {
        return a.at < b.at;
    }

    Boolean compare2(Process a, Process b) {
        return a.pr > b.pr;
    }

    public static void main(String args[]) {
        Process pro[] = new Process[10];
        Scanner handler = new Scanner(System.in);
        System.out.print("Enter the number of processes : ");

        int n = handler.nextInt();
        System.out.print("Enter the process id rival time burst time and priority : ");

        for (int i = 0; i < n; i++) {
            pro[i].pro_id = handler.nextLine();
            pro[i].at = handler.nextInt();
            pro[i].bt = handler.nextInt();
            pro[i].pr = handler.nextInt();
        }

        pro[0].ct = pro[0].bt + pro[0].at;
        pro[0].ta = pro[0].ct - pro[0].at;
        pro[0].wt = pro[0].ta - pro[0].bt;

        int i = 1;

        while (i < n - 1) {

            for (int j = i; j < n; j++) {
                if (pro[j].at > pro[i - 1].ct)
                    break;
            }
            // sort(pro+i,pro+i+(j-i),compare2);
            pro[i].ct = pro[i - 1].ct + pro[i].bt;
            pro[i].ta = pro[i].ct - pro[i].at;
            pro[i].wt = pro[i].ta - pro[i].bt;
            i++;
        }
        pro[i].ct = pro[i - 1].ct + pro[i].bt;
        pro[i].ta = pro[i].ct - pro[i].at;
        pro[i].wt = pro[i].ta - pro[i].bt;

        System.out.println("ProID \t Atime \t Btime \t Ctime \t Ttime \t Wtime \t Priority\n");

        for (i = 0; i < n; i++) {
            System.out.println(pro[i].pro_id + "\t" + pro[i].at + "\t" + pro[i].bt + "\t" + pro[i].ct + "\t" + pro[i].ta
                    + "\t" + pro[i].wt + "\t" + pro[i].pr);
        }
    }
}