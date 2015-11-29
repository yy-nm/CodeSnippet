
/*
	- author: mardyu<michealyxd@hotmail.com
	- create date: 11/25/2015
	主要功能: 创建 unix domain socket sever 并创建 sock 文件用于监听连接
	调用方式: ./a.out
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define SOCK_PATH "ECHO"
#define SOCK_MAX_CLIENT 10

void handle_client(int client_fd)
{
	char buf[1024];
	int retn = 0;
	for(;;) {
		retn = recv(client_fd, buf, sizeof(buf) - 1, 0);
		if (retn > 0) {
			buf[retn] = '\0';
			fprintf(stdout, "recv: %s\n",buf);
		} else if (0 == retn) {
			fprintf(stdout, "client offline");
			break;
		} else {
			fprintf(stderr, "client error");
			break;
		}
	}

	close(client_fd);
}




int main(void)
{
	int socket_fd, client_fd;
	struct sockaddr_un local_addr, client_addr;
	if ((socket_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket error");
		perror(strerror(errno));
		return -1;
	}

	local_addr.sun_family = AF_UNIX;
	strcpy(local_addr.sun_path, SOCK_PATH);
	unlink(local_addr.sun_path);
	int len = strlen(local_addr.sun_path) 
		+ sizeof(local_addr.sun_family);
	if (-1 == bind(socket_fd, (struct sockaddr *)&local_addr, len)) {
		perror("bind error");
		perror(strerror(errno));
		return -2;
	}
	
	if (-1 == listen(socket_fd, SOCK_MAX_CLIENT)) {
		perror("listen error");
		perror(strerror(errno));
		return -3;
	}

	printf("unix domain socket start");
	for(;;) {
		memset(client_addr.sun_path, 0
				, sizeof(client_addr.sun_path));
		len = sizeof(client_addr);
		if (-1 == (client_fd = accept(socket_fd
					, (struct sockaddr *)&client_addr
					, &len))) {
			perror("accept error");
			perror(strerror(errno));
			exit(-4);
		}
		printf("client info: path: %s\n", client_addr.sun_path);
		if (0 == fork()) {
				handle_client(client_fd);
				exit(0);
		}
	}
	close(socket_fd);

	return 0;
}




