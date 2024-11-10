#include <stdio.h>
#include <sys/resource.h>
#include <errno.h>

int main(){
	int nice_value;
	nice_value = getpriority(PRIO_PROCESS, 0);
	if(nice_value=-1 && errno != 0){
		perror("getPriority failed");
	}
	else{
		printf("Current nice value %d", nice_value);
	}

	return 0;
}