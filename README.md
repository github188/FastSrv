# libvi
This is a c++ server that is used to network.
<blockquote>
支持 TLV 协议 <br/>
支持报文缓存（基于 redis） <br/>
支持负载均衡（基于 Google Protocol Buffers） <br/>
在 CentOS 6.6 系统上测试通过@2015-11-05 <br/>
</blockquote>

Depend on
<blockquote>
网络底层依赖 libevent 2.0.22-stable <br/>
数据持久化依赖 redis 2.8.22 <br/>
心跳协议依赖 Google Protocol Buffers 2.6.1 release <br/>
日志文件系统依赖 log4cplus 2.8.22 rc4 <br/>
http 接口依赖 python 3.3.3<br/>
</blockquote>
