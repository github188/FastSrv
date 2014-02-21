pure_server<br />
程序说明：用C++实现的 server 库，目的是10万并发^_^，运行在 linux 平台，会自带一个示例程序<br />

author：zengpw<br />
mail：zengpw@foxmail.com; vincent.tseng.cn@gmail.com<br />

已经实现的功能：<br />
Ⅰ.基于TCP IPV4协议的socket通信；
Ⅱ.
Ⅲ.采用select的服务端；
Ⅳ.采用stl list的任务队列；
Ⅴ.固定大小的线程池；

依赖的第三方软件：<br />
Ⅰ. 编译采用 cmake <br />
Ⅱ. 由于采用了epoll这个系统调用，所以要求linux内核版本高于2.6.19 <br />

