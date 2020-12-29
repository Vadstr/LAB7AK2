// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause

#include <linux/ktime.h>

struct my_list_head {
	struct my_list_head *next;
	ktime_t time;
	ktime_t post_time;
};

int print_hello(uint iterations);
