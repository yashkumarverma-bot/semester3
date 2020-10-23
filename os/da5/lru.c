#include<stdio.h>

#define SIZE 7
int full = 0;
int a[21], n;
int frame[SIZE];
int stk[SIZE];
int repptr;
int count = 0;
int display() {
    int i;
    printf("\nThe elements in the frame are\n");
    for (i = 0; i < full; i++)
        printf("%d\n", stk[i]);
}
int LRstackopt(int p) {
    int temp;
    int i;
    for (i = 0; i < n; i++)
        if (stk[i] == p)
            break;
    temp = stk[i];
    while (i != SIZE - 1) {
        stk[i] = stk[i + 1];
        i++;
    }
    stk[i] = temp;
}
int Pagerep(int ele) {
    int temp;
    repptr = stk[0];
    temp = frame[repptr];
    frame[repptr] = ele;
    LRstackopt(repptr);
    return temp;
}
int Pagefault(int ele) {
    if (full != SIZE) {
        stk[full] = full;
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
                LRstackopt(i);
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
        if (Search(a[i]) != 1) {
            Pagefault(a[i]);
            count++;
        }
        display();
    }
    printf("\nThe number of page faults are %d\n", count);
    return 0;
}