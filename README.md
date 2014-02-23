pure_server<br />
程序说明：用C++实现的 server 库，目的是10万并发^_^，运行在 linux 平台，会自带一个示例程序<br />
程序版本：第一版
最后修改：2014年2月24日 00:05:32<br />
程序状态：可用。<br />

author：zengpw<br />
mail：zengpw@foxmail.com; vincent.tseng.cn@gmail.com<br />

已经实现的功能：<br />
Ⅰ.基于TCP IPV4协议的socket通信；<br />
Ⅱ.<br />
Ⅲ.采用select的服务端；<br />
Ⅳ.采用stl list的任务队列；<br />
Ⅴ.固定大小的线程池；<br />

未来功能展望：<br />
Ⅰ.采用epoll的服务端；<br />
Ⅱ.动态线程池；<br />
Ⅲ.对XML支持（即是支持对XML序列化及反序列化）；<br />
Ⅳ.将接口提供到ps_api这一层<br />

进度的规划：<br />
Ⅰ.采用的是季度规划，即以3个月为一个开发周期；<br />

依赖的第三方软件：<br />
Ⅰ. 编译采用 cmake <br />
Ⅱ. 由于采用了epoll这个系统调用，所以要求linux内核版本高于2.6.19 <br />

