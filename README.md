# WiFi-Vehicle(WIFI智能控制小车)  
华清远见课程设计  
----
基于STM32的WIFI智能小车无线控制  
本仓库只提供简单的服务端和客户端,不提供小车控制电机代码  
#### 目录介绍:  
./Sever 简单的TCP服务端，用于与串口通信,并且接受TCP客户端的控制信息  
>main.c 主程序  
>>serial.c 简单的串口通信库  
>>serial.c 头文件,声明  
>>tools.c 用于省略创建服务端与客户端过程  
>>tools.h 头文件,声明  
>>test.c 测试,直接用于智能小车串口通信

>./Client 使用QT写的Client控制界面
>>暂无介绍

#### 编译环境:  
* Client:  
  * Windows11  
  * QT 5.12.12 MinGW 32-bit

* Server:  
  * ubuntu-18.04-64bit  
  * OpenWrt-SDK-ar71xx-for-linux-i686-gcc-4.8-linaro_uClibc-0.9.33.2

#### 具体流程:  
Client:  
&emsp;连接Wifi,通过TCP客户端向智能小车发送指令  

Server:  
&emsp;编译TCP服务端,并上传到小车系统进行搭建  

#### 个人观感:
&emsp;没有什么难度,开发板是OpenWrt系统.

#### 界面:
![客户端](https://github.com/chengnb/WiFi-Vehicle/blob/main/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-07-07%20164129.png)
