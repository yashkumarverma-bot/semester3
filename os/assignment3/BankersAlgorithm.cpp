/**
 * @author YashKumarVerma / 19BCE2669
 * @for: Lab Digital Assignment 3
 * @description: Implementation of Bankers Algorithm
 */

#include <bits/stdc++.h>

using namespace std;

/** Class to handle all operating and keep data **/
class BankerAlgorithm {
public:
  int p;
  bool come;
  int keepOn;
  int Max[10][3];
  int current[3];
  int need[10][3];
  bool executed[10];
  int available[10][3];
  int allocation[10][3];

  BankerAlgorithm() { int keepOn = 1; }

  void TakeInput() {
    cout << "Enter No. of processes: ";
    cin >> p;
    cout << "\n";
    cout << "Enter the current resources: ";
    cin >> current[0] >> current[1] >> current[2];

    for (int i = 0; i < p; ++i) {
      cout << "[19BCE2669] \t\t > Process P" << i + 1 << " Details" << endl;
      cout << "Enter Allocation : ";
      cin >> allocation[i][0] >> allocation[i][1] >> allocation[i][2];
      cout << "Enter Max :";
      cin >> Max[i][0] >> Max[i][1] >> Max[i][2];
      need[i][0] = Max[i][0] - allocation[i][0];
      need[i][1] = Max[i][1] - allocation[i][1];
      need[i][2] = Max[i][2] - allocation[i][2];
    }

    cout << "[19BCE2669] \t\t > Table for Bankers Algo" << endl << endl;
    cout << "Initial Resources: " << current[0] << " " << current[1] << " "
         << current[2] << endl
         << endl;
    cout << "Process    Max    Allocation    Need" << endl;

    for (int i = 0; i < p; ++i) {
      cout << "  P" << i + 1 << "    "
           << "  " << Max[i][0] << " " << Max[i][1] << " " << Max[i][2]
           << "     "
           << " " << allocation[i][0] << " " << allocation[i][1] << " "
           << allocation[i][2] << "     "
           << " " << need[i][0] << " " << need[i][1] << " " << need[i][2]
           << endl;
    }
  }

  void ProcessData() {
    Calculate();
    while (keepOn) {
      int val, pro;
      cout << "\n\nSelect Below oprations:" << endl << endl;
      cout << "1.Change Max of process: " << endl;
      cout << "2.Change Allocation of process" << endl;
      cout << "3.Change Initial Resources" << endl;
      cout << "4.Exit" << endl;
      cin >> val;

      if (val == 1) {
        cout << "\n\nEnter Process No: ";
        cin >> pro;
        cout << "\nEnter New Max: ";
        cin >> Max[pro - 1][0] >> Max[pro - 1][1] >> Max[pro - 1][2];
      } else if (val == 2) {
        cout << "\n\nEnter Process No: ";
        cin >> pro;
        cout << "\nEnter New Allocation: ";
        cin >> allocation[pro - 1][0] >> allocation[pro - 1][1] >>
            allocation[pro - 1][2];
      } else if (val == 3) {
        cout << "\nEnter Initial Resources: ";
        cin >> current[0] >> current[1] >> current[2];
      } else {
        break;
      }
    }
    Calculate();
  }

  void Calculate() {
    IMP();
    int i, j;
    for (i = 0; i < p; ++i) {
      for (j = 0; j < p; ++j) {
        while (executed[j] && j < p - 1) {
          j++;
        }
        if (need[j][0] <= current[0] && need[j][1] <= current[1] &&
            need[j][2] <= current[2]) {
          if (!executed[j]) {
            executed[j] = true;
            current[0] += allocation[j][0];
            current[1] += allocation[j][1];
            current[2] += allocation[j][2];
            cout << "\nProcess P" << j + 1;
            cout << "\nCurrent: " << current[0] << " " << current[1] << " "
                 << current[2] << "\n";
            cout << "\nProcess executed without deadlock";
            come = true;
            break;
          }
        }
      }
      if (!come) {
        cout << "\n\t\t\tDead lock\n\n";
        break;
      } else {
        come = false;
      }
    }
  }

  void IMP() {
    come = false;
    for (int i = 0; i < 10; ++i) {
      executed[i] = false;
    }
  }
};

int main() { 
    BankerAlgorithm handler = BankerAlgorithm();
    handler.TakeInput();
    handler.ProcessData();
    return 0; }
