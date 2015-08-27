/**
 * @file    node_handler.c
 * @Author  Casper
 * @date    August 2015
 * @brief   Add and remove nodes over UDP
 *
 * Holds methods so nodes can join and leave via UDP broadcast.
 * Send, collect and analyze UDP datagrams.
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "node_handler.h"

#define buf_size 512

int ret;
int sending_socket, listening_socket;
struct sockaddr_in sending_addr, listening_addr;


/** Broadcast message */
int send_broadcast(char* msg)
{
  /* Build and send message */
  ret = sendto(sending_socket, msg, strlen(msg)+1, 0,
                (struct sockaddr*)&sending_addr, sizeof(sending_addr));
  if (ret < 0) {
    log_err("Could not send datagram");
    close(sending_socket);
    return -1;
  }

  return 0;
}


/** Setup socket for UDP broadcast */
int sending_socket_setup(const char *ip, const unsigned int port)
{
  /* Create socket */
  sending_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (!sending_socket)
    log_err("Could not create socket for broadcast");

  /* Enable broadcast */
  int broadcast_enable = 1;
  int ret = setsockopt(sending_socket, SOL_SOCKET, SO_BROADCAST,
                        &broadcast_enable, sizeof(broadcast_enable));
  if (ret < 0) {
    log_err("Could not set socket to broadcast");
    close(sending_socket);
    return -1;
  }

  /* Zero out struct */
  memset(&sending_addr, 0, sizeof(sending_addr));

  /* Set IPv4 */
  sending_addr.sin_family = AF_INET;
  /* Convert address to binary IPv4 */
  inet_pton(AF_INET, ip, &sending_addr.sin_addr);
  /* Convert port to binary port */
  sending_addr.sin_port = htons(port);

  return 0;
}


/** Setup listening socket */
int listening_socket_setup(const unsigned int port)
{
  /* receive buffer */
  char recv_buf[buf_size];
  /* recvfrom sets source ip */
  struct sockaddr_in client_addr;
  unsigned int client_length;

  /* Create socket */
  listening_socket = socket(PF_INET, SOCK_DGRAM, 0);
  if (!listening_socket)
    log_err("Could not create listening socket");

  /* Zero out struct */
  memset(&listening_addr, 0, sizeof(listening_addr));

  /* Set port, listen on all interfaces */
  listening_addr.sin_family = AF_INET;
  listening_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  listening_addr.sin_port = htons(port);

  ret = bind(listening_socket, (struct sockaddr*)&listening_addr,
              sizeof(struct sockaddr));
  if (ret < 0) {
    log_err("Can't bind to listening address");
    close(listening_socket);
    return -1;
  }

  while(1) {
    printf("Waiting for incomming data on listening socket...\n");

    client_length = sizeof(client_addr);

    ret = recvfrom(listening_socket, recv_buf, sizeof(recv_buf), 0,
                          (struct sockaddr*)&client_addr, &client_length);
    if (ret < 0)
      log_err("recvfrom call failed");

    printf("+ received %d bytes from IP %s: %s", ret,
        inet_ntoa(client_addr.sin_addr), recv_buf);
  }

  return 0;
}


/** Close server socket */
int sending_socket_teardown()
{
  close(sending_socket);

  return 0;
}


/** Close client socket */
int listening_socket_teardown()
{
  close(listening_socket);

  return 0;
}

