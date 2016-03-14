#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h> // fprintf.
#include <string.h> // memset.
#include <stdlib.h> // exit().
#include <netdb.h>

int socket_descriptor;

// http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
/*int getaddrinfo(*/
  /*const char *node, // E.g. "www.example.com" or IP.*/
  /*const char *service, // E.g. "http" or port number.*/
  /*const struct addrinfo *hints,*/
  /*struct addrinfo **res*/
/*);*/

/**
 * Not super useful.
void printAddrinfo() {
  printf("hints.ai_flags: %d\n", hints.ai_flags);
  printf("hints.ai_family: %d\n", hints.ai_family);
  printf("hints.ai_socktype: %d\n", hints.ai_socktype);
  printf("hints.ai_protocol: %d\n", hints.ai_protocol);
  //printf("hints.ai_addrlen: %d", hints.ai_addrlen);
  //printf("hints.ai_addr: %c", hints.ai_addr);
  printf("hints.ai_canonname: %p\n", hints.ai_canonname);
  printf("hints.ai_canonname: %p\n", hints.ai_canonname);
}
*/

int main() {
  int status;
  struct addrinfo hints;
  struct addrinfo *servinfo;  // will point to the results

  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
  hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

  if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  // servinfo now points to a linked list of 1 or more struct addrinfos
  //
  // // ... do everything until you don't need servinfo anymore ....
  //
  // freeaddrinfo(servinfo); // free the linked-list
  return 0;
}
