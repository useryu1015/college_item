# [1.alarm_sys](1.alarm_sys)
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

---------------------------
# [2.robot](2.robot)
## 全自动4轴机械臂

* 项目描述：机械臂能在线设置各个点位（如取料点、过渡点、原点、放料点等）自动踩点完成任务。
* 程序介绍：通过PWM控制舵机角度，实现姿态控制；通过间歇使能PWM控制运行速度；通过USMART组件进行姿态调试，并解析在线配置角度。
* 设计思路：基于工业机器人fanuc示教器编程思路，1比1还原软件控制逻辑。
* 方案优化：通过链表动态寄存机械臂过渡点位，支持动态增减运行点位，最后周期遍历使能点位控制机械臂姿态。





---------------------------
# [3.wifi_car](3.wifi_car)
## Wifi小车

---------------------------
# [4.tracking_car](4.tracking_car)
## TI杯电赛-寻迹爬坡小车
![](/document)


---------------------------
# [5.tempctrl_c51](5.tempctrl_c51)
## 毕设-基于51设计温湿度监控与报警系统


---------------------------
# [6.tempctrl_wjh](6.tempctrl_wjh)
## 毕设-PT100数据采集


## 毕设-热电偶数据采集


---------------------------
# [document](document)
**Usage：**
> 修改子目录下README.md后， 执行generate_readme.sh生成主目录下README.md文件
> 
> 脚本输出REDEME.md大纲

**TODO**
> 添加图文到子目录；robot完整源码；

<img src="/document/代打毕设/psc12313.png" alt="Image 2" style="width:80%">
<!-- ![](/document/代打毕设/psc12313.png) -->

---------------------------
