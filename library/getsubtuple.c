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

int
makeipaddr (struct sockaddr *addr, int addrlen, char *buf)
{
  return getnameinfo (addr, addrlen, buf, sizeof (buf), NULL, 0,
		      NI_NUMERICHOST);
}

jobject wrap_int(JNIEnv *env, int res){
jclass integerClass = (*env)->FindClass(env, "java/lang/Integer");
jmethodID integerConstructor = (*env)->GetMethodID(env, integerClass, "<init>", "(I)V");
jobject wrappedInt = (*env)->NewObject(env, integerClass, integerConstructor, (jint)(res));
return wrappedInt; 
}

/*
 * Class:     com_mptcp_Mptcp
 * Method:    _native_getSubflowTuple
 * Signature: (II)[Lcom/mptcp/Mptcp/HostTuple;
 */
JNIEXPORT jobjectArray JNICALL Java_com_mptcp_Mptcp__1native_1getSubflowTuple
  (JNIEnv * env, jclass class, jint sockfd, jint subid)
{
  unsigned int optlen;
  char buf1[512];
  char buf2[512];
  struct mptcp_sub_tuple *sub_tuple;

  optlen = sizeof (struct mptcp_sub_tuple) + 2 * sizeof (struct sockaddr_in);

  sub_tuple = malloc (optlen);

  sub_tuple->id = subid;
  int res = getsockopt (sockfd, IPPROTO_TCP, MPTCP_GET_SUB_TUPLE,
			sub_tuple,
			&optlen);

  if (res < 0)
    {
      return res;
    }

  struct sockaddr_in *sin = (struct sockaddr_in *) &sub_tuple->addrs[0];


  makeipaddr ((struct sockaddr *) sin, sizeof (struct sockaddr_in), buf2);


  jobjectArray result;
  // TODO : trouver unen manière facile et optimale de retourner le résultat 
  // (qui fonctionne) 
  result = (*env)->NewObjectArray (env, 4, (*env)->FindClass(env, "java/lang/Object"), NULL);
  if (result == NULL)
    {
      return NULL;		/* out of memory error thrown */
    }

  makeipaddr ((struct sockaddr *) sin, sizeof (struct sockaddr_in), buf1);

    printf("++ %s ++\n", buf1); 
  (*env)->SetObjectArrayElement (env, result, 0, (*env)->NewStringUTF (env, buf1));
  (*env)->SetObjectArrayElement (env, result, 1, wrap_int(env, ntohs (sin->sin_port)));
  // port: ntohs(sin->sin_port)
  // host: buf1


  sin++;


  (*env)->SetObjectArrayElement (env, result, 2, (*env)->NewStringUTF (env, buf2));
  (*env)->SetObjectArrayElement (env, result, 3, wrap_int(env, ntohs (sin->sin_port)));
  return result;

}
