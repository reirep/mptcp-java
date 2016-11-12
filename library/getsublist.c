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



#define INIT_SUBNUM 4	// initial max number of subflows
#define SUBNUM_FACT 2 	// growth per step
#define MAX_SUBNUM 128 	// maximum acceptable number of subflows (for kernel memory)
/*
jint trowsMemErr(JNIEnv *env, char * message){
	jclass OutMemErr = (*env)->findClass(env, "java/lang/OutOfMemoryError");
	if (OutMemErr == NULL) {
        	return throwNoClassDefError(env, "java/lang/OutOfMemoryError");
    	}
	return (*env)->ThrowNew( env, OutMemErr, message);
}
*/
/*
 * Class:     com_mptcp_Mptcp
 * Method:    _native_getSubflowList
 * Signature:
 */
JNIEXPORT jobjectArray JNICALL Java_com_mptcp_Mptcp__1native_1getSubflowList
  (JNIEnv *env, jclass class, jint sockfd){
    
        int i;
		unsigned int optlen;
		struct mptcp_sub_ids *ids = malloc(1);
		if(ids == NULL){
			
			//there is not enought memeory, throw an error
			return NULL;
		}


		int maxSub = INIT_SUBNUM; 
		int res = 0; 

		while(maxSub < MAX_SUBNUM){
			// tries to match at most maxSub subflows

			optlen =
				sizeof(struct mptcp_sub_ids) +
				maxSub * sizeof(struct mptcp_sub_status);
			ids = realloc(ids, optlen);
			if(ids == NULL){
				return NULL;//TODO: check if it's the correct return and throw an exception
			}

			int res =
				getsockopt(sockfd, IPPROTO_TCP, MPTCP_GET_SUB_IDS, ids,
					   &optlen);

			if(res >= 0){
				// enough memory and good result
				break;
			}
			else if(errno != EINVAL){
				// enough memory and bad result
				free(ids);
				//create an exception here
				return NULL;
			}
			// else: not enough memory: loop

			maxSub *= SUBNUM_FACT;
		}

		if(res < 0){//this isn't correct !
			free(ids);
			return NULL;
		}


        jintArray result;
        result = (*env)->NewIntArray(env, 2*ids->sub_count);
        if (result == NULL) {
		free(ids);
            return NULL; /* out of memory error thrown */
        }
        // fill a temp structure to use to populate the java int array
        jint fill[2*ids->sub_count];
        for (i = 0; i < ids->sub_count; i++) {
            fill[2*i] = ids->sub_status[i].id;
            fill[2*i+1] = ids->sub_status[i].low_prio;
        }
        // move from the temp structure to the java structure
        (*env)->SetIntArrayRegion(env, result, 0, 2*ids->sub_count, fill);
	free(ids);
        return result;
  }

