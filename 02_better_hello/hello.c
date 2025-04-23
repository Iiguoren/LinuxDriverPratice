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
