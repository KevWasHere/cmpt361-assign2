/*-------------------------------------------------------------------------
  # Student's Name: Kevin Ho
  # CMPT 361 Assignment #1
  # blackjack.c
  # Calls functions to run blackjack
*-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <unistd.h>

#include "server.h"

//Assignment Specs
//https://docs.google.com/document/d/1QUI7H9mJE2IJsdlcvxukfunvwoSVNkJQzKQ_ZBvv3hA/edit

/*Reference
Used for SIGCLD Handler
http://www.microhowto.info/howto/reap_zombie_processes_using_a_sigchld_handler.html

Used to convert jsmn tokens
https://stackoverflow.com/questions/14388692/how-to-parse-a-small-json-file-with-jsmn-on-an-embedded-system
*/

//Options globals. Change later?
char *num_decks = "2";					//Default deck is 2 (Range from 1 - 10 decks)
char *money_amount = "100";			//Default amount is $100
char *timeout_timer ="15";			//Default timeout is 15 sec (Range from 10 - 45)
char *server_port = "4420";						//Default port is 4420
char *min_bet = "1";						//Default bet is $1 (Anything > $1)

//Prints usage message of the program and exits
void usage(char *progname){
	char *base;
	base = basename(progname);
	printf("usage: %s [-d num_decks] [-m money_amount] [-t timeout_timer]"
	"[-p server_port] [-b min_bet] [-h]\n"
	"\tDefault Number of Desks - 2\n\tDefault Amount of Money - $100\n\t"
	"Default Timeout Timer - 15 seconds\n\tDefault Port - 4420\n\t"
	"Default Minimum Bet - $1\n"
	"Command Summary:\n\t-d\t\tNumber of Decks (Range of 1 - 10 Decks)\n\t"
	"-m\t\tAmount of Money\n\t-t\t\tServer Timer (Range of 10 - 45 seconds)\n\t"
	"-p\t\tServer Port\n\t-b\t\tMinimum Bet (Range of > $1)\n\t-h\t\t"
	"This help\n", base);
	exit(1);
}

//Options for running blackjack
void blackjack_options(int argc, char *argv[]){
	int ch;
	while((ch = getopt(argc, argv, "d:m:t:p:b:h")) != -1){
		//printf("Ecountered option: %c\n", (char)ch);
		switch(ch){
			case 'd':
				num_decks = optarg;
				printf("Number of Decks [%s]!\n", num_decks);
				break;
			case 'm':
				money_amount = optarg;
				printf("Amount of Money [%s]!\n", money_amount);
				break;
			case 't':
				timeout_timer = optarg;
				printf("Timer [%s]!\n", timeout_timer);
				break;
			case 'p':
				server_port = optarg;
				printf("Port [%s]!\n", server_port);
				break;
			case 'b':
				min_bet = optarg;
				printf("Minimum Bet [%s]!\n", min_bet);
				break;
			case 'h':
				usage(argv[0]);
				//break;
			default:
				usage(argv[0]);
				//continue;
		}
	}
}

int main(int argc, char *argv[]){
	//Getopt. Prog, options and non-options
	blackjack_options(argc, argv);
	
	//Remove later
	printf("Number of Decks [%s], Amount of Money [%s], Timer [%s], Port [%s], "
	"Minimum Bet [%s]\n", num_decks, money_amount, timeout_timer, server_port, min_bet);
	
	int sock_fd;
	sock_fd = new_socket();
	//clean_chld();
	//accept_loop(sock_fd);
	
  return 0;	
}