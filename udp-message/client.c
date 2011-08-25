/*
Prepared By: Hassan Seth
Dated: 25-8-2011
Web: http://hassanseth.wordpress.com
*/

#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in sa;
	int bytes_sent, buffer_length;
	char buffer[1024];

	//Initialize buffer message
	strcpy (buffer, "Hello World");

	//Create Socket
	sock=socket(PF_INET, SOCK_DGRAM, 0);
	if (sock ==-1)
	{
		printf("Error Creating Socket");
		exit(EXIT_FAILURE);
	}

	//Initialize sockaddr_in struct
	memset(&sa, 0, sizeof sa);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("127.0.0.1");
	sa.sin_port = htons(6000);

	//Send message on communication channel
	bytes_sent = sendto(sock, &buffer, sizeof (buffer), 0,(struct sockaddr*)&sa, sizeof sa);
	if (bytes_sent < 0)
		printf("Error sending packet: %s\n", strerror(errno));

	close(sock);
	return 0;
}