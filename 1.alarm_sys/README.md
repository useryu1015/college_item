## 红外警报系统（毕设）
> 视频介绍：[红外警报系统](https://www.bilibili.com/video/BV1cT4y1T7gx/?spm_id_from=333.337.search-card.all.click&vd_source=5292a23e9a80c849a2c727ed746aadb7)
> 
> CSDN博文：[矩阵按键控制](https://blog.csdn.net/ling0604/article/details/109643518)

* 项目描述：以STM32为主控平台，DIY智能防盗警报系统；集合声光警报、人机交互、警报时间记录与查询、管理员身份认证等功能。
* 程序介绍：基于前后台中断响应框架，自定义多个定时器中断配合完成如下功能：	           
1．交互界面：OLED交互界面（多级菜单显示万年历、警报记录、时间设置、用户认证等）	         
2．交互控制：4*4矩阵按键输入	        
3．信号检测：一对人体红外监测模块	       
4．光报警：三色灯（中断控制闪烁&使能）	    
5．声报警：语音合成模块（串口报文收发）	     
6．万年历：带UI可单独设置时分秒（以定时器作时钟源自主开发）	     
7．RFID：射频识别模块，做门禁&管理员身份认证	        

<img src="/document/毕业设计/IMG_20201206_170808.jpg" alt="Image 1" style="width:40%">
<img src="/document/毕业设计/IMG_20201206_170735.jpg" alt="Image 2" style="width:40%">
