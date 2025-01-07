#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(void)
{
	pid_t pid;
	int fd;
	int status;
	off_t offset;
	char buf[1024];
	ssize_t n;

	fd = open("output", O_RDWR|O_TRUNC|O_APPEND); //forkする前にオープンする
	if((pid=fork()) < 0)
		fprintf(stderr, "fork error\n");
	else if(pid==0){
		fd = open("output", O_RDWR);//同じファイルをオープンする
		write(fd,"aaaaaaaa",8);
		exit(0);
	}else{
		wait(&status); //子プロセスを待つ
		write(fd,"bbbbbbbbbb",10);
	}

	exit(0);
}
