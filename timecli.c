#include "unp.h"

int
main(int argc, char** argv)
 {
	 
	int sockfd,n;
       
       char buff[MAXLINE];
       char i[MAXLINE];
       char recvline[MAXLINE];
  	int pfd;
	pfd=atoi(argv[2]);

	struct sockaddr_in	servaddr;
        struct hostent *servername;
	struct in_addr hostaddr;
	hostaddr.s_addr=inet_addr(argv[1]);
	char* ptr;

        char* check;
	check=argv[1];
	if((check[0]>='0') && (check[0]<='9'))
      {
		servername = gethostbyaddr((char *)&hostaddr,4,AF_INET);
		strcpy(buff,"Server name : ");
		strcat(buff,servername->h_name);
		write(pfd,buff,sizeof(buff));
		ptr=argv[1];  
	}

 	else
		{	
		servername=gethostbyname(argv[1]);
		
		int p=0;
		while (servername->h_addr_list[p] != 0) 
			{
	        	        hostaddr.s_addr = *(u_long *) servername->h_addr_list[p++];
	        	       strcpy(buff,"IP Address : ");
				strcat(buff,inet_ntoa(hostaddr));
				write(pfd,buff,sizeof(buff));
				ptr=inet_ntoa(hostaddr);		      
			}
		}

        pid_t childpid,pid;
        
	if (argc != 3)
		write(pfd,"usage: a.out <IPaddress>",25);



	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		write(pfd,"socket error",12);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(9886);	/* daytime server */
	
	if (inet_pton(AF_INET,ptr, &servaddr.sin_addr) <= 0)
		printf("inet_pton error for %s", ptr);
       
	
    
	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		{
		write(pfd,"cannot connect to server",25);	
       		exit(0);
		}
		
	   while(1)
		{   
   			strcpy(buff,"Timecli is active");
			write(pfd,buff,sizeof(buff));	

		        n = read(sockfd, recvline, MAXLINE); 
			recvline[n] = 0;	/* null terminate */
			if(n==0)
			{
				write(pfd,"Server connection closed",25);
				exit(1);
			}
		         printf("%s\n",recvline);
		         sprintf(i, "%s\r\n",i);
		         if (n < 0)
			write(pfd,"read error",10);
			
	
         
		}
}
