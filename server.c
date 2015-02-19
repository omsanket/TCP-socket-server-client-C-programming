#include	"unp.h"
#include	<time.h>
#include   <pthread.h>

void* daytime (void *a);


int
main(int argc, char **argv)
{
	int			listenfd, connfd,sockfd,n,*iptr;
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE];
	time_t				ticks;
        char				recvline[MAXLINE + 1];

	if((listenfd=socket(AF_INET, SOCK_STREAM, 0))==-1)
        printf("socket not created");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(9887);	/* daytime server */
        
	if(bind(listenfd, (SA *) &servaddr, sizeof(servaddr))==-1)
        printf("cannot bind");

	if(listen(listenfd, LISTENQ)==-1)
        printf("cannot listen");

	for ( ; ; ) 
        {
		if(connfd = accept(listenfd, (SA *) NULL, NULL)==-1)
                printf("cannot accept");   

        while ( (n = read(sockfd, recvline, MAXLINE)) > 0) 
        {
		recvline[n] = 0;	/* null terminate */
        printf("recieved%s",recvline);
        if(recvline=="1")
        { iptr=malloc(sizeof(int));
         
         *iptr=connfd;
                
        pthread_t t0;
        if(pthread_create(&t0,NULL,daytime,&iptr)==-1)
           printf("can't create thread");
       
        void* result;
        if(pthread_join(t0,&result)==-1)
        printf("can't join thread");
        }
        
        else if(recvline=="2")
        printf("option 2");
        
        else if(recvline=="3")
        if(close(connfd)==-1)
        printf("cannot close");
       
        else
        printf("invalid input");
        }
        exit (0);
        
        }
        if(close(connfd)==-1)
        printf("cannot close");
 
        }
void* daytime (void *a)
        {int connfd;
        char				buff[MAXLINE];
        connfd=*((int*) a);
        free (a);
        time_t ticks;
        ticks=time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
         if(write(connfd, buff, strlen(buff))==-1)
         printf("cannot write");
        
		if(close(connfd)==-1)
                printf("cannot close");
	}
