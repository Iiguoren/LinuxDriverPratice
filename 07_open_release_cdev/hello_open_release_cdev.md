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
**inode**
inode 表示一个“文件本体”：这是文件在文件系统中的元信息（类型、大小、权限等），唯一对应一个实际文件对象。
#### 实现字符驱动的Open和release
```c
static int my_open (struct inode *inode, struct file *f){
	pr_info("hello_cdev-Major:%d,Minor: %d\n", imajor(inode), iminor(inode));
	pr_info("hello_cdev-file->position: %lld.\n", file->f_pos);
	pr_info("hello_cdev-file->mode: 0x%x,.\n", f->f_mode);
	return 0;
}

static int my_release (struct inode *inode, struct file *f){
	pr_info("hello_cdev-file is closed.\n");
	return 0;
}
```
对照file_operations结构体中的操作函数声明，通过imajor(inode)获得操作文件
注：只有对设备文件imajor才有意义，即：所有文件都有inode但只有设备文件才有设备号；
```c
static struct file_operations fops = {
		.read = my_read,
		.release = my_open,
		.open = my_open,
};
```
将操作函数注册进文件操作函数后，对其使用read,open等会调用我们自定义的函数，即向内核中写入日志
```
[ 5021.312906] hello_cdev-file->mode: 0x1d,.
[ 5021.312922] hello_cdev-file is closed.
[ 5021.312941] hello_cdev-Major:236,Minor: 0
[ 5021.312949] hello_cdev-file->position: 0.
[ 5021.312955] hello_cdev-file->mode: 0x1d,.
[ 5021.312965] hello_cdev-file is closed.
[ 5021.312981] hello_cdev-Major:236,Minor: 0
[ 5021.312990] hello_cdev-file->position: 0.
[ 5021.312995] hello_cdev-file->mode: 0x1d,.
[ 5021.313006] hello_cdev-file is closed.
```