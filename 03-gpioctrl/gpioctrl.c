#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>

static struct gpio_desc *led, *button;
#define IO_LED 21
#define IO_BUTTON 20
#define IO_OFFSET 512

static int __init my_init(void)
{
	int state;
	led = gpio_to_desc(IO_LED + IO_OFFSET);
	if(!led)
	{
		printk("gpioctrl-Error getting pin 21\n");
		return -ENODEV;
	}
	state = gpiod_direction_output(led, 0);
        if(state)
        {
                printk("gpioctrl-Error setting pin 20 out.\n ");
                return state;
        }
		
	button = gpio_to_desc(IO_BUTTON + IO_OFFSET);
	if(!button)
	{
			printk("gpioctrl-Error getting pin 20\n");
			return -ENODEV;
	}
	state = gpiod_direction_input(button);
	if(state)
	{
		printk("gpioctrl-Error setting pin 20 input.\n ");
		return state;
	}
	// 设置LED高电平
	gpiod_set_value(led, 1);
	printk("gpioctrl-Button is %s pressed.\n",gpiod_get_value(button)? "":"no");
	return 0;
}

static void __exit my_exit(void)
{
	gpiod_set_value(led, 0);
}
module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("liguoren");
MODULE_DESCRIPTION("advanced hello kernel");
