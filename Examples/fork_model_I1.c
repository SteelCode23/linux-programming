#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
int main(int argc, char *argv[]){
	int a = 0;
	int b = 0;
	a = atoi(argv[1]);
	b = atoi(argv[2]);

	printf("I am a lonely process, pid=%d\n", getpid());	
	int child_pid = fork();
	if(child_pid == -1){
		perror("impossible to have a child!\n");
		exit(1);
	}
	if(child_pid >= 0){//(child_pid != -1)
		if(child_pid > 0)
			printf("I am the parent, pid=%d\n", getpid());
		else{//(child_pid == 0)
			printf("I am the child, pid=%d\n", getpid());
			//Assign child's tasks here
			printf("child: %d - %d = %d\n", a, b, a - b);
			exit(0);
		}
	}
	//Assign parent tasks here
	printf("parent: %d + %d = %d\n", a, b, a + b);
	int child_exit = 0;
	wait(&child_exit);
	printf("%d\n", child_exit);
	exit(0);
}
