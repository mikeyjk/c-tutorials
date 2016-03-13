#include <sys/types.h>

/**
  ai_family
    This field specifies the desired address family for the
    returned addresses.  Valid values for this field include
    AF_INET and AF_INET6.  The value AF_UNSPEC indicates that
    getaddrinfo() should return socket addresses for any
    address family (either IPv4 or IPv6, for example) that
    can be used with node and service.

  ai_socktype
    This field specifies the preferred socket type, for
    example SOCK_STREAM or SOCK_DGRAM.  Specifying 0 in this
    field indicates that socket addresses of any type can be
    returned by getaddrinfo().

  ai_protocol
    This field specifies the protocol for the returned socket
    addresses.  Specifying 0 in this field indicates that
    socket addresses with any protocol can be returned by
    getaddrinfo().

  ai_flags
    This field specifies additional options, described below.
    Multiple flags are specified by bitwise OR-ing them
    together.
*/
struct addrinfo {
  int ai_flags; // AI_PASSIVE, AI_CANONNAME, etc.
  int ai_family; // AF_INET, AF_INET6, AF_UNSPEC
  int ai_socktype; // SOCK_STREAM, SOCK_DGRAM
  int ai_protocol; // use 0 for "any"
  size_t ai_addrlen; // size of ai_addr in bytes
  struct sockaddr *ai_addr; // struct sockaddr_in or _in6
  char *ai_canonname; // full canonical hostname

  struct addrinfo *ai_next; // linked list, next node
};
