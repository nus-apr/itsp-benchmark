/*numPass=1, numTotal=6
Verdict:WRONG_ANSWER, Visibility:1, Input:"2", ExpOutput:"4", Output:"6"
Verdict:WRONG_ANSWER, Visibility:1, Input:"4", ExpOutput:"20", Output:"40"
Verdict:WRONG_ANSWER, Visibility:1, Input:"10", ExpOutput:"220", Output:"550"
Verdict:WRONG_ANSWER, Visibility:1, Input:"3", ExpOutput:"10", Output:"18"
Verdict:ACCEPTED, Visibility:0, Input:"1", ExpOutput:"1", Output:"1"
Verdict:WRONG_ANSWER, Visibility:0, Input:"20", ExpOutput:"1540", Output:"4200"
*/
#include<stdio.h>

int main(){
   int i,j,N,sum;/*N represents input number*/
   sum=0;
   scanf("%d",&N);
   for(i=1;i<=N;i++){
      for(j=1;j<=N;j++){
        sum=sum+j;}
   }
    printf("%d",sum);
   return 0;
}