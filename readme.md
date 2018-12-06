## 简介
server文件夹是windows下的服务端，与client、ClientForLinux 文件夹对应（client 是 windows下的客户端，ClientForLinux为Linux下的客户端）

## 功能
从服务端发送一张图片到客户端

## 依赖
opencv

## 优势
每次发送前，服务端首先发送一个标志位，客户端接受前首先接受标志位，若标志位不对，则客户端进行重连。
每次发送的时候，首先确定数据的长度与BUFSIZE的大小，将数据划分为若干个BUFSIZE的大小，可以保证数据发送的完整性

## 说明
因为文件中包含中文注释，所以请用 GB2312 编码打开文件