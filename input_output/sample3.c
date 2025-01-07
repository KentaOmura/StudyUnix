#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	int fd;
	pid_t pid;
	int status;
	char buf[1024];

	if((fd = open("output", O_RDONLY|O_CLOEXEC)) < 0) 
			fprintf(stderr, "open error\n");
	printf("fd flags = %d\n", fcntl(fd, F_GETFD));

	if((pid=fork()) < 0)
		fprintf(stderr, "fork error\n");
	else if(pid == 0){
		printf("child %d\n",getpid());
		sprintf(buf, "ls -al /proc/%d/fd", getpid());
		execl("/bin/sh", "sh", "-c",buf,(char*)0);
		exit(0);
	}else{
		wait(&status);
		printf("parent %d\n", getpid());
		sprintf(buf, "ls -al /proc/%d/fd", getpid());
		system(buf);
	}
	exit(0);
}
