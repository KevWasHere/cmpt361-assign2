#ifndef SERVER_H
#define SERVER_H


//Add comments here

/*Prototypes*/
int new_socket();
void clean_chld();
int accept_loop(int sock_fd);
//void *get_in_addr(struct sockaddr *current_addr);
int accept_fork(int sock_fd, int new_fd);
void recv_loop(int sock_fd);
#endif