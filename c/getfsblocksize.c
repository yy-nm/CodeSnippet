
/*
	- author: mardyu<michealyxd@hotmail.com
	- create date: 11/25/2015
	主要功能: 获得文件系统的 block size, 跟具体的文件系统相关
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	const char const *path = "/";
	struct stat filestat;
	
	memset(&filestat, 0, sizeof(struct stat));
	if(stat(path, &filestat) >= 0)
	{
		printf("blksize: %ld, allocated 512B num: %ld, dev: %ld"
		, filestat.st_blksize, filestat.st_blocks, filestat.st_dev);

	}
	else
	{
		printf("get stat of file error!error reason: %s", strerror(errno));
	}
	
	return 0;
}
