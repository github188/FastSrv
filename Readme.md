pure_server & dragon
---------------------------------

###============ 程序说明
####brief:
c++服务端框架 ps_framework ，和基于此框架的游戏后台 dragon <br />
支持 windows/Linux <br />
目前在紧张的开发阶段，已经能看到完工的曙光了。

####特性：
Ⅰ. 支持多客户端；
Ⅱ. 使用优秀的设计模式，跨平台集中在数个类之间；
Ⅲ. 大量的通知和回调设计；
Ⅳ. 支持灵活的自定义协议和session；

####程序版本：
1.4 dev version | update on 2014-09-03 23:33:46

####author & mail:
zengpw | zengpw1226@gmail.com;zengpw@foxmail.com;

<br />

###============ 编译说明
####Windows：
Ⅰ. 用 visual studio 2010 打开 win.sln
Ⅱ. 顺序编译 ps_framework 、 ps_net 、 dragon
Ⅲ. 然后你可以直接按 F5 调试运行 dragon（需要在dragon的工程设置项 - DEBUG 这一项里面，设置 work dir为 $project\..\lib）

####Linux：
//TODO

<br />

###============ 其他
####进度的规划：
Ⅰ.采用的是季度规划，即以3个月为一个开发周期；

####依赖的第三方软件：
Ⅰ. 使用系统调用 epoll，所以要求linux内核版本高于2.6.19
Ⅱ. Linux下使用gnu make，Windows下使用 vs2010 或以上版本

