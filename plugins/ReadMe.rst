插件模式
*********
且称之为“插件模式”。

以前游戏设计中使用到的一个插件模式（貌似来自COM的编程理念）

		iUnKnow
		   |
		   |
   -----------------
   |			   |
   |			   |
iPlugin		iPluginManager
   |			   |
   |			   |
--------------	 Master
|			 |
|			 |
LoginPlugin LoadBalancePlugin

结合观察者模式可以很好使得各个插件协同工作。

Plugin初始化时向PluginManager注册自己所关注的消息，PluginManager收到消息后
向订阅者广播消息。

如此看来，观察者模式应该算是插件模式的一种天然实现了。其实插件模式即解耦依赖关系