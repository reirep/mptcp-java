//int closeSubflow(Socket sock, int subId, int how)

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

JNIEXPORT jint JNICALL Java_com_mptcp_Mptcp__1native_1closeSubflow
  (JNIEnv *env, jclass class, jint sock, jint subId, jint how){

	unsigned int optlen;
        struct mptcp_close_sub_id *sub_id;
        int error;
	optlen = sizeof(struct mptcp_close_sub_id);
	
	sub_id->id=subId;
	sub_id->how= how;
	error= getsockopt(sockfd, IPPROTO_TCP, MPTCP_CLOSE_SUBFLOW,sub_id,&optlen);
	return error;

}
