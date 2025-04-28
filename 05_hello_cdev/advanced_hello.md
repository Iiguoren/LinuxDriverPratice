### 优化hello kernel
```c
#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void)
{
        printk("hello - hello,Kernel!\n");
        return 0;
}

static void __exit my_exit(void)
{
        printk("hello - goodbye,Kernek!\n");
}
module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("liguoren");
MODULE_DESCRIPTION("advanced hello kernel");
```
添加了static，这样模块函数就不会与其他模块的函数冲突：作用于仅限当前模块
添加了__init/__exit:这两个宏的作用是 优化内存管理（将初始化/退出代码放在特定内存区域，执行后释放）。如果省略，代码仍能运行，但会浪费内核内存
添加了元模块显示模块的作者和描述
#### linux功能
`dmesg -w`:显示所有日志并动态显示最新日志
`lsmod`:显示系统中所有模块
`dmesg|tail`：显示最新输出
`modinfo <mod.ko>`:显示模块信息
`insmod <mod.ko>`:加载模块
`rmmod <mod>`:卸载模块
