pure_server<br />
程序说明：用C++实现的 server 库，目的是10万并发^_^，作用是网游后台，运行在 linux 平台<br />
程序版本： 1.3<br />
author：zengpw<br />
mail：zengpw@foxmail.com;    zengpw1226@gmail.com<br />

last update:
2014年5月7日 21:17:55<br />
计划添加内存数据库，预留ps_memory_db文件夹<br />

已经实现的功能：<br />
Ⅰ.基于TCP IPV4协议的socket通信；<br />
Ⅱ.采用select的服务端；<br />
Ⅲ.采用stl list的任务队列；<br />
Ⅳ.固定大小的线程池；<br />
Ⅴ.初步支持与flash(as3)通信；<br />

未来功能展望：<br />
Ⅰ.采用epoll的服务端；<br />
Ⅱ.动态线程池；<br />

进度的规划：<br />
Ⅰ.采用的是季度规划，即以3个月为一个开发周期；<br />

依赖的第三方软件：<br />
Ⅰ. 编译使用 cmake ，版本要求不低于 2.6<br />
Ⅱ. 使用系统调用 epoll，所以要求linux内核版本高于2.6.19 <br />

