/*
	- author: mardyu<michealyxd@hotmail.com
	- create date: 11/25/2015
	主要功能: 获得 linux 环境下的 page size 大小, 适用于 mmap 内存申请
 */

#include <stdio.h>
#include <unistd.h>

long get_page_size()
{
	return sysconf(_SC_PAGE_SIZE);
}

int main(void)
{
	printf("%ld\n", get_page_size());
	return 0;
}
