#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static void do_rw(const char* fileName);

int main(int argc, char* argv[])
{
	if(argc != 2){
		fprintf(stderr, "need to filename\n");
		return -1;
	}

	do_rw(argv[1]);

	return 0;
}

static void do_rw(const char* fileName)
{
	int fd;
	ssize_t size;
	char buf[1024];

	if((fd = open(fileName, O_RDWR|O_APPEND)) == -1) { 
		fprintf(stderr, "open error\n");
		return;
	}

	//標準入力のデータをファイルに出力する
	while((size=read(STDIN_FILENO,buf,sizeof(buf))) >0){
		if(write(fd, buf, size)!=size) {
			fprintf(stderr, "write error\n");
			return;
		}
	}

	if(size < 0) {
		fprintf(stderr, "read error\n");
	}

	return;
}
