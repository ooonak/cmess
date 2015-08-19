/**
 * @file    node_handler.h
 * @Author  Casper
 * @date    August 2015
 */

#include "dbg.h"

/** Broadcast message */
int send_broadcast(char* msg);

/** Setup socket for UDP broadcast */
int sending_socket_setup(const char *ip, const unsigned int port);

/** Setup listening socket */
int listening_socket_setup(const unsigned int port);

/** Close server socket */
int sending_socket_teardown();

/** Close client socket */
int listening_socket_teardown();

