### 树莓派串口收发
树莓派3B+引脚8和引脚10是UART发送和接收引脚，将8与10短接；
#### 设备文件/编号
驱动文件和设备的关联并非是通过设备文件来建立的，而是通过主次设备号的建立实现的
在/dev中有各种设备文件，使用`ls -la`查看设备文件编号,有：
`crw-rw----  1 root     dialout   4,  64 Apr 24 20:11 ttyS0`
主设备号为4，次设备号为64
4代表驱动
64代表设备
通过`cat /proc/devices`显示：
```
Character devices:
  1 mem
  4 /dev/vc/0
  4 tty
  4 ttyS
  5 /dev/tty
  5 /dev/console
  5 /dev/ptmx
  5 ttyprintk
```
其中4代表tty和ttyS驱动
#### 手动创建设备文件node
`sudo mknod myserial c 4 64`建立一个myserial设备文件，设备类型字符设备，对应主设备号4，次设备号64；
这个主设备号和次设备号其实对应着树莓派的spi外设，我们的myserial相当于对于同一个门的第二个门牌号；对myserial的操作等同于对外设操作
然后`sudo screen myserial 9600`已9600波特率打开串口终端，连接到设备 ttyS0（通常是物理串口）进行通信；
之后就会显示串口接受的数据，同时可以向界面输入要传输的数据(但不会显示)，如果安装前文所说的短接，那么输入的数据会回环显示出来。