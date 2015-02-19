#include	"unp.h"

int
main(int argc, char **argv)
{
	int					connfd,sockfd, n;
	char				recvline[MAXLINE + 1];
        char				buff[MAXLINE];
	struct sockaddr_in	servaddr;
        pid_t pid;
        char i[20];

        for( ; ; )
	{if (argc != 2)
		printf("usage: a.out <IPaddress>");

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(9887);	/* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		printf("inet_pton error for %s\n", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		printf("connect error");
        
        printf("1.Time :\n2.Echo :\n3.Quit :");
        scanf("%s",i);
        if(write(connfd, i, strlen(i))==-1)
         printf("cannot write");
        
        if(i=="1")
        {
        pid=fork();
        if(pid ==-1)
        printf("cannot create child");
        if(pid==0)
        if( execlp("xterm","xterm","-e","./time_cli","127.0.0.1",(char*)0)==-1)
        printf("cannot run");
        }
           
        else if(i=="2")
        {
        pid=fork();
        if(pid ==-1)
        printf("cannot create child");
        if(pid==0)
        if( execlp("xterm","xterm","-e","./time_cli","127.0.0.1",(char*)0)==-1)
        printf("cannot run");
        }
                     
        else if(i=="3")
       { if(close(connfd)==-1)
        printf("cannot close");
        exit(0);
        }

      } 
        exit (0);
}
     
        



