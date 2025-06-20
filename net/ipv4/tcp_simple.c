// SPDX-License-Identifier: GPL-2.0

#include<linux/module.h>
#include<linux/init.h>

static int __init hello_init(void)
{
	pr_info("Hello World\n");
	return 0;
}

static void  __exit hello_exit(void)
{
	pr_info("GoodBye World\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saalim Quadri <danascape@gmail.com>");
MODULE_DESCRIPTION("Simple Hello World Module");
