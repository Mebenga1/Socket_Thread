#ifndef SOCKET_THREAD_H

#define SOCKET_THREAD_H


//inclision des bibliothèques neccessaire

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <asm-generic/socket.h>
#include <time.h>

void  *receive_request(void * args);


#endif
