### 创建字符驱动
上节我们为字符驱动增加了简单的read功能，但其实这个字符驱动并未和任何文件/硬件进行交互，本节我们介绍如何对硬件进行交互，file.c为所要参考的linux源码;
#### file结构体和file_operations结构体
位置：include/linux/fs.h
**file结构体：**
file 结构体是 进程打开文件后在内核中对应的对象，表示一个已打开的文件实例（即文件描述符对应的内核对象）。
**file_operations结构体**：
file_operations 是 文件操作接口集合，由具体的设备驱动或文件系统提供，定义了一组对文件的操作函数，如 read, write, open, release 等。 
**关系：**
当进程通过 open() 打开某个文件时，文件系统会创建一个 file 结构体对象，并将其中的 f_op 指针指向具体实现的 file_operations 结构体。
后续所有对该文件的操作（如 read(), write()）都通过 f_op 中的函数指针调用实际实现。
#### 实现字符驱动的Open和release
