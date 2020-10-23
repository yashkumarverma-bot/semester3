#include<stdio.h>

#define SIZE 7
int full = 0;
int a[21];
int ref[SIZE];
int frame[SIZE];
int repptr = 0;
int count = 0;
int display() {
    int i;
    printf("\nThe elements in the frame are\n");
    for (i = 0; i < full; i++)
        printf("%d\n", frame[i]);
}
int Pagerep(int ele) {
    int temp;
    while (ref[repptr] != 0) {
        ref[repptr++] = 0;
        if (repptr == SIZE)
            repptr = 0;
    }
    temp = frame[repptr];
    frame[repptr] = ele;
    ref[repptr] = 1;
    return temp;
}
int Pagefault(int ele) {
    if (full != SIZE) {
        ref[full] = 1;
        frame[full++] = ele;
    } else
        printf("The page replaced is %d", Pagerep(ele));
}
int Search(int ele) {
    int i, flag;
    flag = 0;
    if (full != 0) {
        for (i = 0; i < full; i++)
            if (ele == frame[i]) {
                flag = 1;
                ref[i] = 1;
                break;
            }
    }
    return flag;
}
int main() {
    int n, i;
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
        if (Search(a[i]) != 1) {
            Pagefault(a[i]);
            display();
            count++;
        }
    }
    printf("\nThe number of page faults are %d\n", count);
    return 0;
}