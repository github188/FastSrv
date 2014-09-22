pure_server & dragon
---------------------------------

###============ 程序说明
####Brief:
c++服务端框架 ps_framework ，和基于此框架的游戏后台 dragon <br />
支持 windows/Linux ，平台差异代码很小，大约只占 5% 左右，集中在2、3个类中，目前主要是 windows 版本开发。<br />
目前在紧张的开发阶段，已经能看到完工的曙光了。

####特性：
Ⅰ. 支持多客户端； <br />
Ⅱ. 使用优秀的设计模式，跨平台集中在数个类之间； <br />
Ⅲ. 大量的通知和回调设计； <br />
Ⅳ. 支持灵活的自定义协议和session；

####程序版本：
1.4 dev version , update on 2014-9-9 17:14:06

####Author & Contact:
zengpw <br />
zengpw1226@gmail.com;zengpw@foxmail.com; <br />
如果你想加入开发，请先阅读代码开发风格指南，它的位置在 <br />
<br />
　 　 _doc/pure_server_code_style_guide.txt
<br />

###============ 编译说明
####Windows：
Ⅰ. 用 visual studio 2010 打开 win.sln <br />
Ⅱ. 顺序编译 ps_framework 、 ps_net 、 dragon <br />
Ⅲ. 然后你可以直接按 F5 调试运行 dragon（需要在dragon的工程设置项 - DEBUG 这一项里面，设置 work dir为 $project\..\lib） <br />
　 　 或者
　 你也可以把 bulid 目录里面的 dragon.exe 拷贝到 lib 目录下运行（因为 dragon.exe 运行时要加载自己写的 lib）
　 　 或者
　 把 dragon\bulid 设置为系统环境变量path

####Linux：
//TODO

<br />

