#include<stdio.h>

#define SIZE 7
int full = 0;
int a[21], n;
int frame[SIZE];
static int f = 0;
int repptr;
int count = 0;
int display() {
    int i;
    printf("\nThe elements in the frame are\n");
    for (i = 0; i < full; i++)
        printf("%d\n", frame[i]);
}
int Longestopt() {
    int temp[SIZE] = {
        0
    };
    int c = 0;
    int id, i, k, j = SIZE;
    id = 0;
    for (i = f + 1; i < n; i++) {
        for (k = 0; k < j; k++) {
            if (a[i] == frame[k]) {
                if (temp[k] != 1) {
                    temp[k] = 1;
                    c++;
                }

                break;
            }
        }
        if (c == 2)
            break;
    }
    id = 2;
    while (id != 0) {
        if (temp[id] == 0)
            break;
        id--;
    }
    repptr = id;
    return repptr;
}
int Pagerep(int ele) {
    int temp;
    repptr = Longestopt();
    temp = frame[repptr];
    frame[repptr] = ele;
    return temp;
}
int Pagefault(int ele) {
    if (full != SIZE)
        frame[full++] = ele;
    else
        printf("The page replaced is %d", Pagerep(ele));
}
int Search(int ele) {
    int i, flag;
    flag = 0;
    if (full != 0) {
        for (i = 0; i < full; i++)
            if (ele == frame[i]) {
                flag = 1;
                break;
            }
    }
    return flag;
}
int main() {
    int i;
    FILE * fp;
    fp = fopen("input.txt", "r");
    printf("The number of elements in the reference string are :");
    fscanf(fp, "%d", & n);
    printf("%d", n);
    for (i = 0; i < n; i++)
        fscanf(fp, "%d", & a[i]);
    printf("\nThe elements present in the string are\n");
    for (i = 0; i < n; i++)
        printf("%d  ", a[i]);
    printf("\n\n");
    for (i = 0; i < n; i++) {
        f = i;
        if (Search(a[i]) != 1) {
            Pagefault(a[i]);
            display();
            count++;
        }
    }
    printf("\nThe number of page faults are %d\n", count);
    return 0;
}