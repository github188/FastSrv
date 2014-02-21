pure_server<br />
程序说明：用C++实现的 server 库，目的是10万并发^_^，运行在 linux 平台，会自带一个示例程序<br />
程序版本：2014年2月21日 17:50:49

author：zengpw<br />
mail：zengpw@foxmail.com; vincent.tseng.cn@gmail.com<br />

已经实现的功能：<br />
Ⅰ.基于TCP IPV4协议的socket通信；
Ⅱ.
Ⅲ.采用select的服务端；
Ⅳ.采用stl list的任务队列；
Ⅴ.固定大小的线程池；

未来功能展望：<br />
Ⅰ.采用epoll的服务端；
Ⅱ.动态线程池；
Ⅲ.对XML支持（即是支持对XML序列化及反序列化）；

进度的规划：<br />
Ⅰ.采用的是季度规划，即以3个月为一个开发周期；

依赖的第三方软件：<br />
Ⅰ. 编译采用 cmake <br />
Ⅱ. 由于采用了epoll这个系统调用，所以要求linux内核版本高于2.6.19 <br />

