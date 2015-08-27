#include <stdio.h>
#include <stdlib.h>
#include "node_handler.h"

const unsigned int port = 2000;

int main()
{
  printf("SERVER: Listening for UDP datagrams on port %d\n", port);

  listening_socket_setup(port);

  return 0;
}
