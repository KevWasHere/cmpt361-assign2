/*-------------------------------------------------------------------------
  # Student's Name: Kevin Ho
  # CMPT 361 Assignment #2
  # server.c
  # Functions that create a server for server-client connection
*-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <arpa/inet.h>
#include <sys/wait.h>

#include <sys/select.h>
#include <sys/time.h>

#define BACKLOG 20 //20 Pending connections allowed 
#define BUF_SIZE 320
#define REQUEST_SIZE 13

/*Reference
Used for SIGCLD Handler
http://www.microhowto.info/howto/reap_zombie_processes_using_a_sigchld_handler.html
*/

/*
http://www.microhowto.info/howto/listen_for_and_receive_udp_datagrams_in_c.html
*/

//Signal handler for SIGCHLD. Code sampled from microhow.info and CMPT360
void sigchld_handler(int signal){ 	
	//Chance of waitpid() overwriting errno. Save and restore later
  int saved_errno = errno;
  while((waitpid(-1, NULL, WNOHANG)) > 0){}
  errno = saved_errno;
}

//Cleans dead processes. Code sampled from microhowto.info and CMPT360
void clean_chld(){
  struct sigaction sa;
	sa.sa_handler = &sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
	if (sigaction(SIGCHLD, &sa, 0) == -1) {
		perror("Sigaction");
		exit(1);
	}
}

//Sockaddr for IPv4 or IPv6:
void *get_in_addr(struct sockaddr *current_addr){
	if (current_addr->sa_family == PF_INET){
		return &(((struct sockaddr_in*)current_addr)->sin_addr);
	} else if (current_addr->sa_family == PF_INET6){
		return &(((struct sockaddr_in6*)current_addr)->sin6_addr);
	} else {
		fprintf(stderr, "Unexpected address family for client\n");
		exit(EXIT_FAILURE);
	}	
}

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

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_V4MAPPED | AI_ADDRCONFIG;
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
	
	
	/*
	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	FD_SET(sock_fd, &read_fds);
	*/
	
	//Test. Change later. Move to seperate function 
	//getaddrinfo manpage http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
	//Select https://github.com/nvurgaft/UDP-server-with-select-/blob/master/server.c
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
			//toUpper(copybuf);
			err = sendto(sock_fd, buf, nread, 0, (struct sockaddr *) &client_addr, 
						client_addr_len);
			if(err == -1) {
				perror("Server: sendto");
				close(sock_fd);
				exit(1);
			}
			printf("Server is ready to write\n");
			//printf("Send to client: %s", copybuf);
			//printf("==========================\n");
			printf("\n");
			//memset(&copybuf, 0, sizeof(copybuf));
			FD_CLR(sock_fd, &write_fds);
		}
	}*/
	
	//close(sock_fd);

	return sock_fd;
}

//
void recv_loop(int sock_fd){
	//getnameinfo
	int err;
	struct sockaddr_storage client_addr;
  socklen_t client_addr_len;
	ssize_t nread;
	//char buf[BUF_SIZE];
	
	//REMEMBER TO FREE LATER!!!
	uint32_t *buf = malloc(BUF_SIZE * sizeof(uint32_t));
	
	if (buf == NULL){
		fprintf(stderr, "Malloc Failed\n");
		exit(1);
	}
	
	memset(&buf, 0, BUF_SIZE);
	
	memset(&buf, 1, 1); 
	//memset(&buf+3, 2, 1);

	printf("buf: %zu\n", buf);
	
	while(1){
		
		client_addr_len = sizeof(struct sockaddr_storage);
		//Changed nread to err. Change back if errors. Can prob change later. Just checking bytes
		nread = recvfrom(sock_fd, &buf, BUF_SIZE, 0, (struct sockaddr *) &client_addr,
					&client_addr_len);
		printf("buf: %zu\n", buf);
		
		if (nread == REQUEST_SIZE){
			printf("Request line!\n");
			
			//Something wrong here
			if (&buf[0] == (uint32_t *) 1){
				printf("Request line!\n");
			}
			//Initial play for game here. 
			//Send state of game
		}
		//Currently in game
	
		//Continue if failed request to get next request
		if (nread == -1){
			perror("Server: recvfrom");
			continue;
		}
		
		char host[NI_MAXHOST], service[NI_MAXSERV];

		err = getnameinfo((struct sockaddr *) &client_addr, client_addr_len,
					host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);
					
		if (err == 0){
			printf("Received %zd bytes from %s:%s\n", nread, host, service);
		} else {
			fprintf(stderr, "getnameinfo: %s\n", gai_strerror(err));
		}
		
		err = sendto(sock_fd, &buf, nread, 0, (struct sockaddr *) &client_addr, 
				client_addr_len);

		if (err == -1){
			perror("Server: sendto");
		} 
	}
	return;
}

//Fork for accept connection
int accept_fork(int sock_fd, int new_fd){
	int pid = fork();
	char *statusLine = malloc(1000 * sizeof(char));

	if (statusLine == NULL){
		fprintf(stderr, "Malloc Failed\n");
		exit(1);
	}
	
	if (pid < 0){
		//Fork failed. student server allowed for 20 processes
		fprintf(stderr, "Fork failed");
		exit(1);
	} else if (pid == 0) {
		//Currently child
		close(sock_fd); //Close becuase not listening for new connections
		
		statusLine = "Connected!\n";
		send(new_fd, statusLine, strlen(statusLine), 0);
	
		//free(buffRead);
		close(new_fd);
		
		exit(0);
	} else {
		//Currently Parrent
		close(new_fd); //Close client because not interating
	}
	
	free(statusLine);
		
	return 0;
}

//Accept loop for server
int accept_loop(int sock_fd){
	int new_fd;
	char buff_size[INET6_ADDRSTRLEN];
	
	//Accept loop for connections
  while(1){
    struct sockaddr_storage client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    
    new_fd = accept(sock_fd, (struct sockaddr *)&client_addr,
		    &client_addr_size);
    if (new_fd == -1){
      perror("Server: accept:");
			continue;	//Don't want to close connection from one bad accept
    }
		
		inet_ntop(client_addr.ss_family, 
				get_in_addr((struct sockaddr *)&client_addr),
				buff_size, sizeof buff_size);

		printf("Accepted Connection...\n");
		
		accept_fork(sock_fd, new_fd);
		
		printf("Closed Connection...\n");
  }
	return 0;
}