/*
Prepared By: Hassan Seth
Dated: 25-8-2011
Web: http://hassanseth.wordpress.com
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <stdlib.h>
#include <arpa/inet.h>

int main(void)
{
	//Create Socket
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in sa; 
	char buffer[1024];
	int recsize;
	socklen_t fromlen;

	//Initialize Memory
	memset(&sa, 0, sizeof sa);
	memset (& buffer, 0, sizeof buffer);
	sa.sin_family = AF_INET;
	//Enter IP address of host-server
	sa.sin_addr.s_addr=inet_addr("127.0.0.1");
	sa.sin_port = htons(6000);
	//Initialize recvfrom parameter from size of sockaddr_in struct
	fromlen = sizeof sa;

	//Bind Socket file descriptor to network resource - blocking call
	if (-1 == bind(sock,(struct sockaddr *)&sa, sizeof sa))
	{
		perror("error bind failed");
		close(sock);
		exit(EXIT_FAILURE);
	} 

	//Indefinite loop for listener
	for (;;) 
	{
		printf ("recv test....\n");
		recsize = recvfrom(sock, &buffer, sizeof (buffer), 0, (struct sockaddr *)&sa, & fromlen);

		if (recsize < 0)
			fprintf(stderr, "%s\n", strerror(errno));

		printf("recsize: and errorno %d, %d \n ",recsize, errno);
		printf("recieved message : %s\n", buffer);
		sleep(1);
	}
}