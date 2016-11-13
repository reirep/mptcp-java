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

	jclass intArray = (*env)->FindClass(env, "[I");
        jobjectArray ext = (*env)->NewObjectArray(env, ids->sub_count, intArray, NULL);
	if(ext == NULL){
		free(ids);
		trowsMemErr(env, MEM_ERR_MESSAGE);
		return NULL;
	}
        int j;
        for(j =0; j < ids->sub_count; j++){
                jint fill[6] = {
                        ids->sub_status[j].id,
                        ids->sub_status[j].slave_sk,
                        ids->sub_status[j].fully_established,
                        ids->sub_status[j].attached,
                        ids->sub_status[j].low_prio,
                        ids->sub_status[j].pre_established
                };
                jintArray inner = (*env)->NewIntArray(env, SIZE_STRUCT);
		if(inner == NULL){
			free(ids);
			trowsMemErr(env, MEM_ERR_MESSAGE);
			return NULL;
		}
                (*env)->SetIntArrayRegion(env, inner, 0, 6, fill);
                (*env)->SetObjectArrayElement(env, ext, j, inner);
        }
        return ext;
  }

