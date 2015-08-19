#include <stdio.h>
#include <stdlib.h>
#include "node_handler.h"

#define buf_size 512

const char *ip = "10.0.0.0";
const unsigned int port = 2000;
char *bye_cmd = "~q";

int main()
{
  printf("CLIENT: Sending your message via UDP broadcast\n");

  sending_socket_setup(ip, port);

  char input_buf[buf_size];

  printf("Please enter a message to broadcast or '~q' to quit, less than %d chars:\n", buf_size);

  while(1) {
    printf("> ");
    fgets(input_buf, buf_size-1, stdin);
    if (strstr(input_buf, bye_cmd))
      break;

    /* Don't send empty strings */
    if (strlen(input_buf) > 1) {
      send_broadcast(input_buf);
      printf(" - we sent: %s", input_buf);
    }
  }

  sending_socket_teardown();

  return 0;
}
