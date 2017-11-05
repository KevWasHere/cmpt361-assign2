/*-------------------------------------------------------------------------
  # Student's Name: Kevin Ho
  # CMPT 361 Assignment #2
  # server.h
  # server.c header
*-----------------------------------------------------------------------*/

#ifndef SERVER_H
#define SERVER_H

/*Prototypes*/

//Creates a new socket for a UDP server
int new_socket();

//Recvfrom and sendto loop.
//Parameters: sock_fd - socket created from new_socket()
void recv_loop(int sock_fd);
#endif