#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <sys/types.h>
#include <linux/tcp.h>
#include <linux/socket.h>
#include <linux/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



JNIEXPORT jint JNICALL Java_com_mptcp_Mptcp__1native_1openSubflow
  (JNIEnv *env, jclass class, jint sockfd, jstring source_host, jint source_port, jstring dest_host, jint dest_port, jint priority){
// private native static int _native_openSubflow(int fd, String source_host, int source_port, String dest_host, int dest_port, int priority);

	unsigned int optlen;
	struct mptcp_sub_tuple *sub_tuple;
	struct sockaddr_in *addr;
	int error;

	optlen = sizeof(struct mptcp_sub_tuple) +
            2 * sizeof(struct sockaddr_in);
	sub_tuple = malloc(optlen);

	sub_tuple->id = 0;
  	sub_tuple->prio = priority;

   	addr = (struct sockaddr_in*) &sub_tuple->addrs[0];

   	addr->sin_family = AF_UNSPEC;
   	addr->sin_port = htons(source_port);
   	inet_pton(AF_UNSPEC, source_host, &addr->sin_addr);

   	addr++;

   	addr->sin_family = AF_UNSPEC;
   	addr->sin_port = htons(dest_port);
   	inet_pton(AF_UNSPEC, dest_host, &addr->sin_addr);

   	error =  getsockopt(sockfd, IPPROTO_TCP, MPTCP_OPEN_SUB_TUPLE, sub_tuple, &optlen);

	return error;
}
