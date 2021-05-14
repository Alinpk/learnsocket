//
//  main.cpp
//  socket
//
//  Created by 黄主江 on 2021/5/13.
//  Copyright © 2021年 黄主江. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void){
    int sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sock<0)
        exit(-1);
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(5188);
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    //inet_aton("127.0.0.1",&servaddr.sin_addr);
    if(connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
        exit(-1);
    char sendbuf[1024]={0};
    char recvbuf[1024]={0};
    while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL){
        write(sock,sendbuf,strlen(sendbuf));
        read(sock,recvbuf,sizeof(recvbuf));
        fputs(recvbuf,stdout);
        memset(sendbuf,0,sizeof(sendbuf));
        memset(recvbuf, 0, strlen(recvbuf));
    }
    std::cout<<"connect break"<<std::endl;
    close(sock);
    
    return 0;
}
