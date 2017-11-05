/*-------------------------------------------------------------------------
  # Student's Name: Kevin Ho
  # CMPT 361 Assignment #2
  # server.c
  # Functions that create a server for server-client connection in UDP
*-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <sys/select.h>
#include <sys/time.h>

#define BUF_SIZE 320

//Creates new server for client-server connection
int new_socket(){
	//getaddrinfo
	char *port = "4420";
	struct addrinfo hints, *server_info, *current;
	int sock_fd;
	int val = 1;

	//select
	//fd_set read_fds, write_fds;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	int err = getaddrinfo(NULL, port, &hints, &server_info);

	if (err != 0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
		exit(1);
	}

	for (current = server_info; current != NULL; current = current->ai_next){	
	
		//Socket
		sock_fd = socket(current->ai_family, current->ai_socktype, 
				current->ai_protocol);
		if (sock_fd == -1){
			perror("Server: socket");
			continue;
		}
		err = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));
		if (err == -1){
			perror("Server: setsockopt");
			exit(1);
		}

		//Bind
		err = bind(sock_fd, current->ai_addr, current->ai_addrlen); 
		if (err == -1){
			close(sock_fd);
			perror("Server: bind");
			continue;
		} 

		//Working Server
		break;
	}
	printf("Server: Waiting for Connections...\n");

	if (current == NULL){
		fprintf(stderr, "Could not create server\n");
		exit(1);
	}

	freeaddrinfo(server_info);  //Done with Struct

	return sock_fd;
}

void recv_loop(int sock_fd){
	//getnameinfo
	int err;
	struct sockaddr_storage client_addr;
  socklen_t client_addr_len;
	ssize_t nread;;

	//Header
	//State layout, 8 - 1 byte, 16 - 2 byte, 32 - 4 byte
	uint8_t recv_buf[BUF_SIZE];
	uint8_t send_buf[BUF_SIZE];
	uint8_t opcode;
	//uint32_t arg;
	uint16_t seq_num = 1;
	uint32_t min_bet = 1;
	//uint8_t active_player = 0;
	uint32_t bank = 100;
	//uint8_t dealer_cards[21];
	//uint8_t player_array[7][41];	//41 each per player. Index 33 on main buf


	printf("sizeof(recv_buf): %lu\n", sizeof(recv_buf));

	memset(recv_buf, 0, BUF_SIZE);
	memset(send_buf, 0, BUF_SIZE);

	memcpy(send_buf + 7, &min_bet, 4);
	memcpy(send_buf + 5, &seq_num, 2);
	memcpy(send_buf + 45, &bank, 4);

	printf("recv_buf: %s\n", recv_buf);

	while(1){

		client_addr_len = sizeof(client_addr);
		//Checking bytes received
		nread = recvfrom(sock_fd, &recv_buf, BUF_SIZE, 0,
					(struct sockaddr *) &client_addr, &client_addr_len);

		//Client request
		if (recv_buf[0] == 1){
			printf("Request line!\n");
			//Copy opcode
			opcode = (uint8_t) 0;
			memcpy(send_buf, &opcode, 1);
			//Copy Username
			memcpy(send_buf + 33, recv_buf + 1, 12);
			printf("State: %s\n", send_buf);
			//Initial play for game here.
			//Send state of game
		}
		//Currently in game

		//Continue if failed request to get next request
		if (nread == -1){
			perror("Server: recvfrom");
			continue;
		}

		//Used to show bytes received.
		//Reference: https://linux.die.net/man/3/getaddrinfo
		char host[NI_MAXHOST], service[NI_MAXSERV];

		err = getnameinfo((struct sockaddr *) &client_addr, client_addr_len,
					host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);

		if (err == 0){
			printf("Received %zd bytes from %s:%s\n", nread, host, service);
		} else {
			fprintf(stderr, "getnameinfo: %s\n", gai_strerror(err));
		}

		err = sendto(sock_fd, &send_buf, BUF_SIZE, 0,
				(struct sockaddr *) &client_addr, client_addr_len);

		if (err == -1){
			perror("Server: sendto");
		}

		/*
		//Bet Test
		opcode = (uint8_t) 2;
		memcpy(send_buf, &opcode, 1);

		seq_num = seq_num + 1;
		memcpy(send_buf + 5, &seq_num, 2);

		err = sendto(sock_fd, &send_buf, BUF_SIZE, 0, (struct sockaddr *) &client_addr, 
				client_addr_len);
		*/
	}
	return;
}

//Unused select code. Not working
/*
	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	FD_SET(sock_fd, &read_fds);
	*/

	//Test. Change later. Move to seperate function 
	//getaddrinfo manpage http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
	//nc -u localhost 4420
	//echo "msg" > /dev/udp/localhost/4420
	
		/*
		if (sendto(sock_fd, buf, nread, 0, (struct sockaddr *) &client_addr, 
					client_addr_len) != nread){
			perror("Server: sendto");
		}*/


		//Select stuff

		/*
		struct timeval timeout = {
			.tv_sec = 0,
			.tv_usec = 1000e3,
		};
		int err = select(sock_fd + 1, &read_fds, &write_fds, NULL, &timeout);
		
		if (err == -1){
			close(sock_fd);
			perror("Server: select");
			exit(1);
		} 
		*/

		//printf("Before FD_ISSET\n");
		//printf("%d\n", FD_ISSET(sock_fd, &read_fds));

		/*
		if (FD_ISSET(0, &read_fds)){
			printf("Server: Waiting for Connections...\n");
		
			client_addr_len = sizeof(struct sockaddr_storage);
			//Changed nread to err. Change back if errors
			nread = recvfrom(sock_fd, buf, BUF_SIZE, 0, (struct sockaddr *) &client_addr,
						&client_addr_len);

			//printf("Recvfrom: %sn", buf);


			//Continue if failed request to get next request
			if (nread == -1){
				perror("Server: recvfrom");
				continue;
			}

			//FD_CLR(sock_fd, &read_fds);
		}
		*/

		//Still need to do write_fds and save read_fds to buff

		/*
		char* buf = (char*)malloc(320);		
		char* copybuf = (char*)malloc(320);
		
		if (buf == NULL){
			fprintf(stderr, "Malloc Failed\n");
		exit(1);
		}
		*/

		/*
		if (copybuf == NULL){
			fprintf(stderr, "Malloc Failed\n");
		exit(1);
		}
	*/

	/*
		if (strlen(buf) != 0){
			memcpy(copybuf, buf, strlen(buf));
	
			int i = strlen(buf) + 3 + strlen(inet_ntoa(cli_addr.sin_addr)) + ntohs(cli_addr.sin_port);
		*/

		/*
		//FD_ZERO(&write_fds);
		FD_SET(sock_fd, &write_fds);
		if(FD_ISSET(sock_fd, &write_fds)){
			err = sendto(sock_fd, buf, nread, 0, (struct sockaddr *) &client_addr, 
						client_addr_len);
			if(err == -1) {
				perror("Server: sendto");
				close(sock_fd);
				exit(1);
			}
			FD_CLR(sock_fd, &write_fds);
		}
	}*/

	//close(sock_fd);