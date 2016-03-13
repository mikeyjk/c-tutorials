#include <sys/types.h>

int socket_descriptor;

// http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
struct addrinfo {

  /**
   * This field specifies additional options, described below.
   * Multiple flags are specified by bitwise OR-ing them together.
   */
  int ai_flags; // AI_PASSIVE, AI_CANONNAME, etc.

  /**
   * This field specifies the desired address family for the
   * returned addresses.  Valid values for this field include
   * AF_INET and AF_INET6.  The value AF_UNSPEC indicates that
   * getaddrinfo() should return socket addresses for any
   * address family (either IPv4 or IPv6, for example) that
   * can be used with node and service.
   */
  int ai_family; // IPv4, IPv6, ... etc.

  /**
   * This field specifies the preferred socket type, for
   * example SOCK_STREAM or SOCK_DGRAM.  Specifying 0 in this
   * field indicates that socket addresses of any type can be
   * returned by getaddrinfo().
   */
  int ai_socktype; // SOCK_STREAM, SOCK_DGRAM.

  /**
   * This field specifies the protocol for the returned socket
   * addresses.  Specifying 0 in this field indicates that
   * socket addresses with any protocol can be returned by
   * getaddrinfo().
   */
  int ai_protocol; // Use 0 for "any".

  /**
   * A pointer to the socket address is placed in the ai_addr field, and
   * the length of the socket address, in bytes, is placed in the
   * ai_addrlen field.
   */
  struct sockaddr *ai_addr; // Populated with socket information.
  size_t ai_addrlen; // Size of ai_addr in bytes.

  /**
   * If hints.ai_flags includes the AI_CANONNAME flag, then the
   * ai_canonname field of the first of the addrinfo structures in the
   * returned list is set to point to the official name of the host.
   */
  char *ai_canonname; // Full canonical hostname.

  struct addrinfo *ai_next; // Linked list, next node.
};

// Populated with socket information.
struct sockaddr {
  unsigned short sa_family; // Address family, AF_xxx.

  /**
   * sa_data contains a destination address and port number for the socket.
   * This is rather unwieldy since you don't want to tediously pack the address
   * in the sa_data by hand.
  */
  char sa_data[14]; // 14 bytes of protocol address.
};

// IPv4, see struct in6_addr for IPv6.
struct in_addr {
  uint32_t s_addr; // 32-bit int (4 bytes).
}

// IPv4, see struct sockaddr_in6 for IPv6.
struct sockaddr_in {

  /**
   * Corresponds to sa_family in struct sockaddr.
   */
  short int sin_family; // Address family, AF_INET.

  /**
   * Expected to be in Network Byte Order (big endian).
   */
  unsigned short int sin_port; // Port number.

  struct in_addr sin_addr; // Internet address.

  /**
   * sin_zero is to pad the structure to the length of a struct sockaddr
   * should be set to all zeros with the function memset().
   */
  unsigned char sin_zero[8]; // Same size as struct sockaddr.
};

// (IPv6 only--see struct sockaddr_in and struct in_addr for IPv4)

struct sockaddr_in6 {
  u_int16_t       sin6_family;   // address family, AF_INET6
  u_int16_t       sin6_port;     // port number, Network Byte Order
  u_int32_t       sin6_flowinfo; // IPv6 flow information
  struct in6_addr sin6_addr;     // IPv6 address
  u_int32_t       sin6_scope_id; // Scope ID
};

struct in6_addr {
  unsigned char   s6_addr[16];   // IPv6 address
};

/**
 * For some calls, sometimes you don't know in advance if it's going to fill
 * out your struct sockaddr with an IPv4 or IPv6 address. So you pass in
 * this parallel structure, very similar to struct sockaddr except larger,
 * and then cast it to the type you need
 */
struct sockaddr_storage {
  sa_family_t ss_family; // Address family.

  // All this is padding, implementation specific, ignore it:
  char __ss_pad1[_SS_PAD1SIZE];
  int64_t __ss_align;
  char __ss_pad2[_SS_PAD2SIZE];
};

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int getaddrinfo(
  const char *node, // E.g. "www.example.com" or IP.
  const char *service, // E.g. "http" or port number.
  const struct addrinfo *hints,
  struct addrinfo **res
);
