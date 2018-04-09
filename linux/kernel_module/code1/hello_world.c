/*************************************************************************
	> File Name: hello_world.c
	> Author: Wan Xiangjun
	> Mail: 
	> Created Time: 2018年03月14日 星期三 22时40分03秒
 ************************************************************************/

#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL")

static int hello_init(void)
{
    printk(KERN_ALERT "Hello, world\n");
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
