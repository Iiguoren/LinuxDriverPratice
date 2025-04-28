### 创建字符驱动
上一节中说明了如何使用`mknod`命令创建一个访问内核驱动的接口，通过创建`ttyS`的节点myserial 关联了书梅派的收发串口，这一节介绍如何实现一个简单的字符驱动
#### 分配设备号
实现一个字符驱动首先需要分配一个主设备号，在linux中通过一个函数:`register_chrdev`实现，具体为：
`int register_chrdev(int num, char* procname, file_operations *fop);`
需要输入主设备号，驱动名，和文件操作结构体地址
如果num为0就会自动分配一个主设备号，如果不为0，就在所对应设备号下分配子设备号
返回所对应的设备号或小于0的报错

将注册函数写在模块初始化中，在模块关闭函数中写入unregister_chrdev(int, char*)
#### fop结构体
fop结构体定义着如何处理设备如：read,write,open,close等
因此，在定义fop时候将自定义的重载函数地址传给fop如：
```c
ssize_t myread(/*这里参考fop结构体中read参数);
file_operations fops = {
    .read = myread
}
这样对字符设备的read操作就定义好了
#### 结果
载入模块:
hello_cdev-major niber is 236.
为驱动注册了设备号
`mknod hello0 c 236 0`
`cat ./hello0`
显示:hello_cdev-read is called.
