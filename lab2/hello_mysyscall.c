#include <sys/syscall.h>
#include <unistd.h>

void mywrite(int fd, const void *buf, size_t count){
	syscall(SYS_write, fd, buf, count);
}


int main(){
	char* text = "Hello, World!\n";

	mywrite(1, text, 14);
        return 0;
}

