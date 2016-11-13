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
#include <string.h>


#define SUB_NUM 32 	// maximum acceptable number of subflows (for kernel memory)
#define SIZE_STRUCT 6 //the current size of the mptcp_sub_ids

#define MEM_ERR_MESSAGE "Impossible d'allouer la mém�oire nécéssaire !"

//a small function to throw an error that signal that there is no enought memeory
jint trowsMemErr(JNIEnv *env, char * message){
	jclass OutMemErr = (*env)->FindClass(env, "java/lang/OutOfMemoryError");
	if (OutMemErr == NULL) {
        	return throwNoClassDefError(env, "java/lang/OutOfMemoryError");
    	}
	return (*env)->ThrowNew( env, OutMemErr, message);
}

/*
 * Class:     com_mptcp_Mptcp
 * Method:    _native_getSubflowList
 * Signature:
 */
JNIEXPORT jobjectArray JNICALL Java_com_mptcp_Mptcp__1native_1getSubflowList
  (JNIEnv *env, jclass class, jint sockfd){

	unsigned int optlen;
	struct mptcp_sub_ids *ids = malloc(SUB_NUM* sizeof(struct mptcp_sub_ids));

	if(ids == NULL){
		trowsMemErr(env, strerror(errno));
		return NULL;
	}

	optlen = sizeof(struct mptcp_sub_ids) + SUB_NUM * sizeof(struct mptcp_sub_status);

	int res = getsockopt(sockfd, IPPROTO_TCP, MPTCP_GET_SUB_IDS, ids, &optlen);

	if(res != 0){ // enough memory and bad result
		char * error = strerror(errno);
		free(ids);
		trowsMemErr(env, error);
		return NULL;
	}

	//analysing the results

	//crating the returned array here
	//TODO : remove those F###ing hack
	jintArray tableau = (*env)->NewIntArray(env, 2+SIZE_STRUCT*ids->sub_count);

        if (tableau == NULL) {
		free(ids);
		trowsMemErr(env, "Java environnement out of memomry !\n");
        	return NULL; /* out of memory error thrown */
        }

        // fill a temp structure to use to populate the java int array
	jint number[2] = {ids->sub_count,SIZE_STRUCT};
	(*env)->SetIntArrayRegion(env, tableau, 0,2, number);
	unsigned int i;
        for (i = 0; i < ids->sub_count; i++) {
        	jint fill[6] = {
        		ids->sub_status[i].id,
        		ids->sub_status[i].slave_sk,
        		ids->sub_status[i].fully_established,
        		ids->sub_status[i].attached,
        		ids->sub_status[i].low_prio,
        		ids->sub_status[i].pre_established
        	};
        	(*env)->SetIntArrayRegion(env, tableau, i*6+2, 6, fill);
	}

	free(ids);
        return tableau;
  }

