/*numPass=2, numTotal=7
Verdict:WRONG_ANSWER, Visibility:1, Input:"4
1 2 3 4
5
2 3 4 5 6", ExpOutput:"1 2 3 4 5 6 
", Output:"2 3 4 "
Verdict:WRONG_ANSWER, Visibility:1, Input:"3
3 2 4
5
9 2 1 4 6", ExpOutput:"1 2 3 4 6 9 
", Output:"2 4 "
Verdict:WRONG_ANSWER, Visibility:1, Input:"5
1 2 3 5 6
6
-6 -4 -2 -1 2 4
", ExpOutput:"-6 -4 -2 -1 1 2 3 4 5 6 
", Output:"2 "
Verdict:ACCEPTED, Visibility:0, Input:"1
1
1
1
", ExpOutput:"1 
", Output:"1 "
Verdict:WRONG_ANSWER, Visibility:0, Input:"1
1
4
3 5 6 7
", ExpOutput:"1 3 5 6 7 
", Output:""
Verdict:ACCEPTED, Visibility:0, Input:"3
9 2 1
3
1 2 9
", ExpOutput:"1 2 9 
", Output:"1 2 9 "
Verdict:WRONG_ANSWER, Visibility:0, Input:"7
28 49 23 29 02 69 34
8
23 49 12 93 34 21 43 54", ExpOutput:"2 12 21 23 28 29 34 43 49 54 69 93 
", Output:"23 34 49 "
*/
#include <stdio.h>
#include <stdlib.h>

void sort(int [],int);
void swap(int *,int *);

int main() {
    int i,j;
    struct sets{
        int n,*ptr;};
    struct sets set[2];
    scanf("%d\n",&set[0].n);
    set[0].ptr=(int *)malloc(set[0].n*sizeof(int));
    for(i=0;i<set[0].n;i++)
       scanf("%d ",&set[0].ptr[i]);
    scanf("\n%d\n",&set[1].n);
    set[1].ptr=(int *)malloc(set[1].n*sizeof(int));
    for(i=0;i<set[1].n;i++)
       scanf("%d ",&set[1].ptr[i]);
    for(i=0;i<2;i++)
       sort(set[i].ptr,set[i].n);
    for(i=0;i<set[0].n;i++)
       for(j=0;j<set[1].n;j++)
          if(set[0].ptr[i]==set[1].ptr[j])
            printf("%d ",set[0].ptr[i]);
    return 0;}
    
void sort(int a[],int n){
    int i,j;
    for(i=0;i<n;i++)
       for(j=i;j<n;j++)
          if(a[i]>a[j])
            swap(&a[i],&a[j]);}

void swap(int *a,int *b){
    int t;
    t=*b;
    *b=*a;
    *a=t;}