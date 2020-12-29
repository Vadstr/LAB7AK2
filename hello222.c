// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
#include <linux/init.h>
#include <linux/module.h>
#include <hello1.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("LAB7AK2 advanced task: hello1\n");
MODULE_AUTHOR("Striletskiy Vadim IV-82\n");

static uint n = 1;
module_param(n, uint, 0444);

static int hello_init(void)
{
	return print_hello(n);
}

static void hello_exit(void)
{
	pr_alert("Kern_alert HELLO_EXIT,\n");
}

module_init(hello_init);
module_exit(hello_exit);
