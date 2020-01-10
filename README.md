### log4cplus_demo
---

两种使用log4cplus库的demo，用于 [log4cplus](https://github.com/log4cplus/log4cplus) 库的快速入门和使用，并提供了配置文件的参考.

相关博文请参考 []() 。

### 使用配置文件
---

由 logConfigTest.cpp 及 log4cplus.config  组成，配置文件控制着日志的生成。

推荐该使用模式。

### 直接在程序中配置
---

也可以在程序中配置log4cplus。但不如配置文件方式简洁易维护。

### 编译
---

两者都通过 scons 编译。点击可查看 [Scons](https://blog.csdn.net/guotianqing/article/details/92003258) 的编写和使用。

直接运行 scons 即可完成两者编译，需要 c11 的支持。
