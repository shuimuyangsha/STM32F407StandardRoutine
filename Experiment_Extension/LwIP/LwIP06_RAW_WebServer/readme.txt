
本实验所需器材：STM32F407开发板块，网线一根。

本实验将实现如下功能：上电以后初始化相应的外设，如果开启了DHCP的话就获取IP地址等信息，在本实验中开发板为WebServer服务器，当开发板LCD进入主界面以后我们就可以在浏览器中输入开发板的IP地址来访问WsbServer服务器，可以在浏览器中控制开发板的相应外设，如LED、蜂鸣器。也可以通过浏览器来查看AD值和STM32F407内部温度传感器值。

注意：本实验未使用UCOS操作系统，访问开发板的电脑一定要和开发板在同一个网络中，否则无法访问！如果没有插网线并且开启了DHCP的话就会等待很久！


               	正点原子@ALIENTEK
               	2014-11-3
		广州市星翼电子科技有限公司
                联系电话（传真）：020-38271790
	       	购买：http://shop62103354.taobao.com
                      http://shop62057469.taobao.com
               	技术支持论坛：www.openedv.com