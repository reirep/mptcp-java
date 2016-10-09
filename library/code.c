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
  (JNIEnv *env, jclass class, jint fd, jint subid, jint how){
    return 42;
  }


/*
 * Class:     com_mptcp_Mptcp
 * Method:    _native_openSubflow
 * Signature: (ILjava/lang/String;ILjava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_com_mptcp_Mptcp__1native_1openSubflow
  (JNIEnv *env, jclass class, jint fd, jstring source_host, jint source_port, jstring dest_host, jint dest_port, jint priority){
    return 42;
  }


