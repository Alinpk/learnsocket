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
    int listenfd=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(listenfd<0)
        exit(-1);
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(5188);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    //也可以servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    //inet_aton("127.0.0.1",&servaddr.sin_addr);
    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
        printf("bind error\n");
        exit(-1);
    }
    if(listen(listenfd,SOMAXCONN)<0)
        exit(-1);//套接字变成被动套接字
    struct sockaddr_in peeraddr;
    int con;
    socklen_t peerlen=sizeof(peeraddr);
    if((con=accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0)
        exit(-1);
    char recvbuf[1024];
    while(1){
        memset(recvbuf,0,sizeof(recvbuf));
        int status= read(con,recvbuf,sizeof(recvbuf));
        std::cout<<recvbuf<<std::endl;
        write(con,recvbuf,strlen(recvbuf));
        if(status==0)break;
    }
    std::cout<<"connect break"<<std::endl;
    close(con);
    close(listenfd);
    return 0;
}
