#include <linux/module.h>
#include <linux/init.h>

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

ssize_t my_read(struct file *f,char __user *u, size_t l,  loff_t *o){
	printk("hello_cdev-read is called.\n");
	return 0;
}

static int major;
static struct file_operations fops = {
		.read = my_read,
		.release = my_open,
		.open = my_open,
};

static int __init my_init(void)
{
	major = register_chrdev(major, "hello_cdev", &fops);
	if(major < 0){
		printk("hello_cdev-Error register cdev.\n");
		return major;
	}
	printk("hello_cdev-major number is %d.\n",major);
	return 0;	
}

static void __exit my_exit(void)
{
	unregister_chrdev(major, "hello_cdev"); 
}
module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("liguoren");
MODULE_DESCRIPTION("a simple cdev driver");
