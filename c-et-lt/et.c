#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <string.h>

void lib_connect(int fd, char *addr, int port);

void lib_epoll_create1();

void lib_epoll_add(int op, int fd);

int lib_epoll_wait(struct epoll_event *events, int num);

int main(int argc, char *argv[]) {
    char *str = "GET / HTTP/1.1\n\n";
    int clientFd = socket(PF_INET, SOCK_STREAM, 0);
    lib_connect(clientFd, "localhost", 80);
    int ret = write(clientFd, str, strlen(str));

    lib_epoll_create1();
    lib_epoll_add(EPOLLIN | EPOLLET, clientFd);
    struct epoll_event *events;
    events = calloc(64, sizeof(struct epoll_event));
    int num;
    num = lib_epoll_wait(events, 64);
    printf("%d\n", num);
    num = lib_epoll_wait(events, 64);
    printf("%d\n", num);
}

/*
gcc et.c include.c
 */