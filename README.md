# FastSrv
Update
<blockquote>
2015-12-25：修复98%Warning级别告警@gcc version 4.4.7 <br/>
2015-12-25：测试通过@CentOS 6.6 <br/>
</blockquote>

Feature
<blockquote>
支持 TLV 协议 <br/>
支持报文缓存（基于 redis） <br/>
支持负载均衡（基于 Google Protocol Buffers） <br/>
</blockquote>

Introduction
<blockquote>
common: 提供 日志、数据库、网络、配置、线程、 redis 、 python 的底层支持 <br/>
protocol: 提供 tlv协议、 google protobuf协议的支持 <br/>
session: 提供 心跳协议、网络事件循环、 redis 事件循环的支持 <br/>
</blockquote>
<blockquote>
balance: 用于平衡 task 进程的负载 <br/>
task: 用于接收报文，回复报文 <br/>
upload: 用于处理耗时过多的报文 <br/>
sending: 提供ICE接口，方便异构语言下发指令 <br/>
</blockquote>

Compile
<blockquote>
common: make cmi<br/>
protocol: make cm<br/>
session: make cm<br/>
</blockquote>
<blockquote>
balance: make cm<br/>
task: make cm<br/>
upload: make cm<br/>
sending: make cm<br/>
</blockquote>

Depend on
<blockquote>
网络底层依赖 libevent 2.0.22-stable <br/>
数据持久化依赖 redis 2.8.22 <br/>
心跳协议依赖 Google Protocol Buffers 2.6.1 release <br/>
日志文件系统依赖 log4cplus 2.8.22 rc4 <br/>
http 接口依赖 python 3.3.3<br/>
</blockquote>
