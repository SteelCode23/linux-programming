#include <fcntl.h>
#include <unistd.h>

void main(){
	int fd_in = open("/dev/pts/0", O_RDONLY);
	int fd_out = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666 );
	
	if(fd_in == -1){
		write(2,"Error in opening device!\n",25);
		return;
	}
	if(fd_out == -1){
		write(2,"Error in opening log file!\n",27);

		return;
	}

	char buf[20];
	ssize_t bytes_read;
	
	while ((bytes_read = read(fd_in, buf, sizeof(buf))) > 0) {


		if(buf[0]=='E' && buf[1]=='N' && buf[2] =='D'){
			int result = close(fd_in);
			if(result == -1){
				write(2,"Error in closing the device!\n",29);
			}			
			if (close(fd_out) == -1) {
				write(2, "Error closing log file\n",23);
			}			
			return;
		}
		if(write(fd_out, buf, bytes_read) != bytes_read){
			write(2, "Error writing to log",18);
		}
    	}

	int result = close(fd_in);
	if(result == -1){
		write(2, "Error closing the device!\n",26);
	}
}
