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

/*
 * Class:     com_mptcp_Mptcp
 * Method:    _native_closeSubflow
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_com_mptcp_Mptcp__1native_1closeSubflow
  (JNIEnv *env, jclass class, jint sockfd, jint subId, jint how){

        unsigned int optlen;
        struct mptcp_close_sub_id *sub_id;
        int error;
        optlen = sizeof(struct mptcp_close_sub_id);

        sub_id->id=subId;
        //sub_id->how= how;
        error= getsockopt(sockfd, IPPROTO_TCP, MPTCP_CLOSE_SUB_ID,sub_id,&optlen);
        return error;

}

/*
 * Class:     com_mptcp_Mptcp
 * Method:    _native_openSubflow
 * Signature: (ILjava/lang/String;ILjava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_com_mptcp_Mptcp__1native_1openSubflow  (JNIEnv *env, jclass class, jint sockfd, jstring source_host, jint source_port, jstring dest_host, jint dest_port, jint priority){
        unsigned int optlen;
        struct mptcp_sub_tuple *sub_tuple;
        struct sockaddr_in *addr;
        int error;
        const char *nativeSource = (*env)->GetStringUTFChars(env, source_host, 0);
        const char *nativeDest = (*env)->GetStringUTFChars(env, dest_host, 0);

        optlen = sizeof(struct mptcp_sub_tuple) +
            2 * sizeof(struct sockaddr_in);
        sub_tuple = malloc(optlen);

        sub_tuple->id = 0;
        //sub_tuple->prio = priority;

        addr = (struct sockaddr_in*) &sub_tuple->addrs[0];

        addr->sin_family = AF_INET;
        addr->sin_port = htons(source_port);
        inet_pton(AF_INET, nativeSource, &addr->sin_addr);

        addr++;

        addr->sin_family = AF_INET;
        addr->sin_port = htons(dest_port);
        inet_pton(AF_INET, nativeDest, &addr->sin_addr);

        error =  getsockopt(sockfd, IPPROTO_TCP, MPTCP_OPEN_SUB_TUPLE, sub_tuple, &optlen);

	if (error){
		return NULL;
}
	int i;
   	 optlen;
   	struct mptcp_sub_ids *ids;

   	optlen = 42;
	ids = malloc(optlen);

   	getsockopt(sockfd, IPPROTO_TCP, MPTCP_GET_SUB_IDS, ids, &optlen);
        return ids->sub_status[0].id;//the last flow added is on first place in sub_status
}

