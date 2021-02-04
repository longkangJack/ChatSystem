#pragma once 
#include <stdio.h>
#include <string.h>
#include <iostream>
//注册请求的数据格式
//
/*1.昵称
 *2.学校
 *3.用户的密码
 */ 
struct RegisterInfo
{
  RegisterInfo()
  {
    memset(nick_name_,'\0',sizeof(nick_name_));
    memset(school_,'\0',sizeof(school_));
    memset(password_,'\0',sizeof(password_));
  }
  char nick_name_[20];
  char school_[20];
  char password_[20];
};





//登录请求的数据格式
/*
 * 1.用户id
 * 2.密码
 * */ 
struct LoginInfo 
{
  LoginInfo()
  {
    memset(password_,'\0',sizeof(password_));
  }
  char password_[20];
};


//服务端给客户端回复应答的数据格式
// 
/*
 * 1.当前状态(注册状态，登录状态)
 * 2.返回用户ID,类似于注册完毕返回的qq号
 */ 
struct RelpyInfo
{
  int resp_status_;
  uint32_t id_;

};

//枚举状态
enum Status
{
  REGISTER_FAILED = 0,
  REGISTRE_SUCCESS,
  LOGIN_FAILED,
  LODIN_SUCCESS   
};
//如何标识当前的请求是注册请求还是登录请求
//1.对于每一种请求，在TCP层面都会发送两个tcp包
//第一个tcp包，发送一个字节，标识请求是 注册 还是 登录
//第二个tcp包，发送具体的 注册 或者 登录数据
enum ResqType
{
  REFISTER_RESQ = 0,
  LOGIN_RESQ
};
