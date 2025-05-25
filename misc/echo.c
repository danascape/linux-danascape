// SPDX-License-Identifier: GPL-2.0
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/init.h>

/*
 * A simple echo module
 */

static char *string = "Default";

module_param(string, charp, 0000);
MODULE_PARM_DESC(string, "A character string");

static int __init echo_init(void)
{
	pr_info("echo: Initialise...\n");
	pr_info("The provided string: %s\n", string);
	return 0;
}

static void __exit echo_exit(void)
{
	pr_info("echo: Exit...\n");
}

module_init(echo_init);
module_exit(echo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saalim Quadri <danascape@gmail.com>");
MODULE_DESCRIPTION("Simple echo Module");
