#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <linux/stat.h>
#include <sys/stat.h>
int main(int argc, char *argv[]){
	printf("exec_math_bs pid:%d\n", getpid());
    pid_t pid = fork();
	int	a = atoi(argv[2]);
    char b = argv[1][0];
    int c = atoi(argv[3]);
	char *program = "#include <stdio.h>\n"
			"#include <stdlib.h>\n"
			"#include <unistd.h>\n"
			"int result;\n"
			"int main(int argc, char *argv[]){\n"
			"printf(\"main_add pid: %d\\n\", getpid());\n"
			"int a = 0;\n"
		 	"char b;\n"
            "int c = 0;\n"
			"a = atoi(argv[2]);\n"
            "b = argv[1][0];\n"
            "c = atoi(argv[3]);\n"
            "switch(b){\n"
            "case '+':\n"
            "result = a + c;\n"
            "break;\n"
            "case '-':\n"
            "result = a - c;\n"
            "break;\n"
            "case '*':\n"
            "result = a * c;\n"
            "break;\n"
            "case '/':\n"
            "result = a / c;\n"
            "break;\n"                        
            "default:\n"
            "printf(\"Unsupported operation. Please try again.\");\n"
            "return 1;}\n"
            "printf(\"%d %c %d = %d\\n\",a,b,c,result);\n"
            "return 0;\n"                        
			"}\n";
    if(pid==-1){
        perror("Fork Failed");
        exit(1);
    }
    else if(pid==0){
        int fd1 = creat("./math.c", S_IRUSR | S_IWUSR);
        printf("fd for math.c file:%d\n", fd1);
        write(fd1, program, strlen(program));
        char *argv2[] = { "cc", "./math.c", "-o", "math", NULL };
        char *envp[] = { "PATH=/usr/bin:/bin", "LD_LIBRARY_PATH=/usr/lib:/lib", NULL };
        close(fd1);
        int fd2 = open("/usr/bin/cc", O_RDONLY); 
        if (fexecve(fd2, argv2, envp) == -1) {
            perror("Error executing fexecve for compiler");
            close(fd2);
            exit(1);
        }
        close(fd2);
    }
    else{

        char *envp[] = { "PATH=/usr/bin:/bin", "LD_LIBRARY_PATH=/usr/lib:/lib", NULL };
        int fd3 = open("./math", O_RDONLY);
        if (fexecve(fd3, argv, envp) == -1) {
            perror("Error executing fexecve");
            close(fd3);  // Close the file descriptor if fexecve fails
            exit(1);
        }
        close(fd3);
    }
}
