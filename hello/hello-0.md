### linux下简单的kernel module创建
内核模块（Kernel Module）是 Linux 内核的扩展组件，允许在不重新编译或重启整个内核的情况下，动态添加或移除功能。它本质上是可加载到内核中运行的代码块，通常用于驱动硬件、实现文件系统、扩展内核功能等。
#### 内核的模块特点
* 动态加载
    可在系统运行时候加载卸载无需重启
* 直接运行在内核态
* 常用于设备驱动，文件系统，网络功能
#### 环境配置
安装内核头文件：
`sudo apt install linux-headers-$(uname -r)`
$(uname -r)表示内核版本
安装的内核头文件一般在：/lib/modules/$(uname -r)/build文件夹中
#### 基本模板
```c
#include <linux/module.h>  // 必须包含的内核模块头文件
#include <linux/init.h>    // 包含 __init 和 __exit 宏

int my_module_init(void){  //加载模块 
	/* code */
	return 0; // 表示成功
}

void my_modlue_exit(void){  //卸载模块
	/* code */
}
// 注册加载/卸载
module_init(my_module_init);
module_exit(my_module_exit);

// 声明模块许可证（必须，否则会有警告）
MODULE_LICENSE("GPL");
// 可选声明模块描述和作者
MODULE_DESCRIPTION("A simple Linux kernel module");
MODULE_AUTHOR("Your Name");
```

#### makefile编写
```makefile
obj-m := my_module.o  # 目标模块名称（对应 .c 文件名）

all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
obj-m:指明模块对象文件，必须与c文件名一致
-C切换到内核构建目录（确保已安装对应内核头文件）
M=$(PWD) 指定模块源代码路径为当前目录。
* 编译:make
* 清除:make clean
#### 加载和卸载
编译成功会在当前目录生成.ko文件，
`sudo insmod my_module.ko`加载模块
`sudo rmmod my_module`卸载模块
`lsmod | grep my_module` 查看已加载模块
#### 调试
一般在模块中会用printk方便调试：
`dmesg | tail -n 20`  # 查看最近 20 条内核日志
`dmesg -C`            # 清空日志缓存（方便调试）

