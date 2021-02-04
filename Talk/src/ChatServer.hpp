#pragma once 
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#define TCP_PORT 17878

enum error_no
{
  CREATE_SOCK_FAILED = 0,
};
class ChatServer
{
  public:
    ChatServer()
    {
      //构造函数
      //注册登录
      tcp_sock_ = -1;
      tcp_port_ = TCP_PORT; 
    }
    ~ChatServer
    {
      //析构函数
    }
    /*初始化变量（服务）的接口,被调用者调用的接口
     *用户管理模块的变量,消息池的实例化对象
    */
    int InitSvr(unit16_t tcp_port = TCP_PORT)
    {
      //1.创建tcp socket，并且绑定地址信息，监听
      //登录+注册
      tcp_sock_ = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
      if(tcp_sock < 0)
      {
        return -1;
      }
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(tcp_port);
      addr.sin_addr.s_addr = inet_addr("0.0.0.0");
      /*
       * inet_addr;
       * 1.将点分十进制的IP地址转化成unit32_t
       * 2.将unit32_t从主机字节序转换成网络字节序
       *
       * "0.0.0.0"代表侦听当前机器中的任意网卡信息
       */
     int ret =  bind(tcp_sock_,(struct sockaddr*)&addr,sizeof(addr));
     if(ret < 0 )
     {
       return -2;
     }
     //监听
    ret =  listen(tcp_sock_,5);
    if(ret < 0)
    {
      return -3;
    }
     return 0;
    }
    /*
     * 启动线程
     */ 
    int Start()
    {
      /*
       * udp应该有两类线程
       * 1.生产线程,负责接收udp数据，将udo数据放到消息池当中
       * 2.消费线程,负责从消息池中或者消息，发送到在线用户的客户端
       *
       *

       * tcp                             
       * 针对每一个注册登录请求，(tcp连接)，针对每一个tcp连接，都创建一个线程，
       * 专门为该客户端处理注册和登录请求，注册和登陆完毕之后，服务端关闭连接销毁线程. 
       * tcp是否创建线程，取决于accept函数是否调用成功
       */ 
      //udp线程的创建
      struct sockaddr_in peer_addr;
      socklen_t peer_addrlen = sizeof(peer_addr);
       while(1)
       {
         int new_sock =  accept(tcp_sock_,(struct sockaddr*)&peer_addr,&peer_addrlen);
     if(new_sock < 0)
     {
       continue;

     }

      //正常接收到了
      //创建线程，为客户端的注册和登录请求负责
      pthread_t tid;
      int ret = pthread_create(&tid,NULL,LoginRegisterStart,NULL)
      {


      }

    }
       
 }
  private:
   static void* LoginRegisterStart(void* arg)
    {
      /*
       * 1.注册
       * 2.登录
       *
       */  
    }
  private:
    //TCP和UDP套接字
    int tcp_sock_;
    unit16_t tcp_port_;
    int udp_sock_;
};

