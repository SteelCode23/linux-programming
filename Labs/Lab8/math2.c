#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int result;
int main(int argc, char *argv[]){
printf("main_add pid: %d\n", getpid());
int a = 0;
char b;
int c = 0;
a = atoi(argv[2]);
printf("%d", a);
b = argv[1][0];
c = atoi(argv[3]);
printf("%d", c);
printf("%d", b);
switch(b){
case '+':
result = a + c;
break;
case '-':
result = a - c;
break;
case '*':
result = a * c;
break;
case '/':
result = a / c;
break;
default:
printf("Unsupported operation. Please try again.");
return 1;}
printf("\n%d %c %d = %d\n",a,b,c,result);
return 0;
}
