/*
	- author: mardyu<michealyxd@hotmail.com
	- create date: 11/25/2015
	主要功能: 实现一个简易版本的 tee 功能
	调用方式: cat {fle-name} | ./a.out {other-file}
 */
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stddef.h>

int main(int argc, void **args)
{
	char *file_name = NULL;
	int fd = 0;
	if (argc > 1)
		file_name = (char *) args[1];
	if (file_name && strlen(file_name)) {
		fd = open(file_name
				, O_CREAT | O_WRONLY | O_APPEND
				, S_IRUSR | S_IWUSR);
		if (fd < 0)
			perror(strerror(errno));
	}
	
	int buff_sz = sysconf(_SC_PAGE_SIZE);
	char *buff = mmap(NULL, buff_sz, PROT_READ | PROT_WRITE
			, MAP_PRIVATE | MAP_ANONYMOUS
			, -1, 0);
	if (NULL == buff) {
		perror(strerror(errno));
	}
	ssize_t read_sz = 0;
	while((read_sz = read(STDIN_FILENO, buff, buff_sz)) > 0) {
		if (fd > 0)
			write(fd, buff, read_sz);
		write(STDOUT_FILENO, buff, read_sz);
	}

	if (fd > 0) {
		close(fd);
		fd = -1;
	}

	return 0;
}



