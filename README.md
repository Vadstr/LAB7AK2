# AK-lab7
## Результат виконання

### insmod для n=6

![1](1.png)

### Пошук адреси помилки

![2](2.png)

## Лістинг:

### Makefile

```makefile
ccflags-y := -I$(PWD)/inc
ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := hello11.o hello22.o
ccflags-y += -g -DDEBUG
else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build
default:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp hello11.ko hello11.ko.unstripped
	cp hello22.ko hello22.ko.unstripped
	$(CROSS_COMPILE)strip -g hello11.ko
	$(CROSS_COMPILE)strip -g hello22.ko
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
%.s %.i: %.c
	$(MAKE) -C $(KDIR) M=$$PWD $@
endif
```
### hello1.h

```c
// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause

#include <linux/ktime.h>

struct my_list_head {
	struct my_list_head *next;
	ktime_t time;
	ktime_t post_time;
};

int print_hello(uint iterations);
```

### hello1.c

```cpp
// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <hello1.h>
#include <linux/slab.h>
#define DEBUG

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("AK-2 lab_7 advanced task: hello1\n");
MODULE_AUTHOR("Illia Starodubtcev IV-82\n");

static struct my_list_head *head;

void clear_my_list(void)
{
	struct my_list_head *temp_first;
	struct my_list_head *temp_second;

	temp_first = head;

	while (temp_first != NULL) {
		temp_second = temp_first->next;
		kfree(temp_first);
		temp_first = temp_second;
	}
}

int print_hello(uint n)
{
	int i;
	struct my_list_head *temp_head1;
	struct my_list_head *temp_head2;

	BUG_ON(n > 10);

	head = kmalloc(sizeof(struct my_list_head *), GFP_KERNEL);

	temp_head1 = head;

	if (n == 0) {
		pr_warn("WARNING! n = 0\n");
		return 0;
	} else if (n >= 5) {
		pr_warn("WARNING! 5 <= n <= 10\n");
	}

	for (i = 0; i < n; i++) {
		temp_head1->next = kmalloc(sizeof(struct my_list_head *)
		, GFP_KERNEL);
		if (n == 6)
			temp_head1 = NULL;

		temp_head1->time = ktime_get();
		pr_info("Hello, world\n");
		temp_head1->post_time = ktime_get();
		temp_head2 = temp_head1;
		temp_head1 = temp_head1->next;
	}
	kfree(temp_head2->next);
	temp_head2->next = NULL;

	return 0;
}
EXPORT_SYMBOL(print_hello);


static int __init hello1_init(void)
{
	pr_info("hello1 init");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct my_list_head *temp_first = head;
	struct my_list_head *temp_second = temp_first;

	pr_debug("Print list start");
	while (temp_first != NULL) {
		pr_debug("Time spent %lld",
		temp_first->post_time - temp_first->time);

		temp_second = temp_first;
		temp_first = temp_second->next;
		kfree(temp_second);
	}
	pr_debug("Print list end");
	pr_info("hello1 exit");
}

module_init(hello1_init);
module_exit(hello1_exit);

```

### hello2.c

```cpp
// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
#include <linux/init.h>
#include <linux/module.h>
#include <hello1.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("AK-2 lab_7 advanced task: hello1\n");
MODULE_AUTHOR("Illia Starodubtcev IV-82\n");

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
```

### hello11.ko.unstripped

```assembly
hello11.ko.unstripped:     file format elf32-littlearm


Disassembly of section .text:

00000000 <print_hello>:
{
	int i;
	struct my_list_head *temp_head1;
	struct my_list_head *temp_head2;

	BUG_ON(n > 10);
   0:	e350000a 	cmp	r0, #10
{
   4:	e92d47f0 	push	{r4, r5, r6, r7, r8, r9, sl, lr}
	BUG_ON(n > 10);
   8:	8a00002f 	bhi	cc <print_hello+0xcc>
			unsigned int index = kmalloc_index(size);

			if (!index)
				return ZERO_SIZE_PTR;

			return kmem_cache_alloc_trace(kmalloc_caches[index],
   c:	e3005000 	movw	r5, #0
  10:	e3405000 	movt	r5, #0
  14:	e1a04000 	mov	r4, r0
  18:	e3a010c0 	mov	r1, #192	; 0xc0
  1c:	e3a02004 	mov	r2, #4
  20:	e5950018 	ldr	r0, [r5, #24]
  24:	e3401060 	movt	r1, #96	; 0x60
  28:	ebfffffe 	bl	0 <kmem_cache_alloc_trace>

	head = kmalloc(sizeof(struct my_list_head *), GFP_KERNEL);
  2c:	e3003000 	movw	r3, #0

	temp_head1 = head;

	if (n == 0) {
  30:	e3540000 	cmp	r4, #0
	head = kmalloc(sizeof(struct my_list_head *), GFP_KERNEL);
  34:	e3403000 	movt	r3, #0
  38:	e1a06000 	mov	r6, r0
  3c:	e5830000 	str	r0, [r3]
	if (n == 0) {
  40:	0a000022 	beq	d0 <print_hello+0xd0>
		pr_warn("WARNING! n = 0\n");
		return 0;
	} else if (n >= 5) {
  44:	e3540004 	cmp	r4, #4
  48:	9a000002 	bls	58 <print_hello+0x58>
		pr_warn("WARNING! 5 <= n <= 10\n");
  4c:	e3000000 	movw	r0, #0
  50:	e3400000 	movt	r0, #0
  54:	ebfffffe 	bl	0 <printk>
  58:	e3a080c0 	mov	r8, #192	; 0xc0
		, GFP_KERNEL);
		if (n == 6)
			temp_head1 = NULL;

		temp_head1->time = ktime_get();
		pr_info("Hello, world\n");
  5c:	e3007000 	movw	r7, #0
  60:	e3408060 	movt	r8, #96	; 0x60
  64:	e3407000 	movt	r7, #0
{
  68:	e3a0a000 	mov	sl, #0
  6c:	e3a02004 	mov	r2, #4
  70:	e1a01008 	mov	r1, r8
  74:	e5950018 	ldr	r0, [r5, #24]
	for (i = 0; i < n; i++) {
  78:	e28aa001 	add	sl, sl, #1
  7c:	ebfffffe 	bl	0 <kmem_cache_alloc_trace>
		if (n == 6)
  80:	e3540006 	cmp	r4, #6
  84:	11a09006 	movne	r9, r6
  88:	03a09000 	moveq	r9, #0
		temp_head1->next = kmalloc(sizeof(struct my_list_head *)
  8c:	e5860000 	str	r0, [r6]
		temp_head1->time = ktime_get();
  90:	ebfffffe 	bl	0 <ktime_get>
  94:	e1c900f8 	strd	r0, [r9, #8]
		pr_info("Hello, world\n");
  98:	e1a00007 	mov	r0, r7
  9c:	ebfffffe 	bl	0 <printk>
		temp_head1->post_time = ktime_get();
  a0:	ebfffffe 	bl	0 <ktime_get>
	for (i = 0; i < n; i++) {
  a4:	e15a0004 	cmp	sl, r4
		temp_head2 = temp_head1;
		temp_head1 = temp_head1->next;
  a8:	e5996000 	ldr	r6, [r9]
		temp_head1->post_time = ktime_get();
  ac:	e1c901f0 	strd	r0, [r9, #16]
	for (i = 0; i < n; i++) {
  b0:	1affffed 	bne	6c <print_hello+0x6c>
	}
	kfree(temp_head2->next);
  b4:	e1a00006 	mov	r0, r6
  b8:	ebfffffe 	bl	0 <kfree>
	temp_head2->next = NULL;
  bc:	e3a03000 	mov	r3, #0
  c0:	e5893000 	str	r3, [r9]

	return 0;
}
  c4:	e3a00000 	mov	r0, #0
  c8:	e8bd87f0 	pop	{r4, r5, r6, r7, r8, r9, sl, pc}
	BUG_ON(n > 10);
  cc:	e7f001f2 	.word	0xe7f001f2
		pr_warn("WARNING! n = 0\n");
  d0:	e3000000 	movw	r0, #0
  d4:	e3400000 	movt	r0, #0
  d8:	ebfffffe 	bl	0 <printk>
		return 0;
  dc:	eafffff8 	b	c4 <print_hello+0xc4>

000000e0 <clear_my_list>:
	temp_first = head;
  e0:	e3003000 	movw	r3, #0
  e4:	e3403000 	movt	r3, #0
  e8:	e5930000 	ldr	r0, [r3]
	while (temp_first != NULL) {
  ec:	e3500000 	cmp	r0, #0
  f0:	012fff1e 	bxeq	lr
{
  f4:	e92d4010 	push	{r4, lr}
		temp_second = temp_first->next;
  f8:	e5904000 	ldr	r4, [r0]
		kfree(temp_first);
  fc:	ebfffffe 	bl	0 <kfree>
	while (temp_first != NULL) {
 100:	e2540000 	subs	r0, r4, #0
 104:	1afffffb 	bne	f8 <clear_my_list+0x18>
 108:	e8bd8010 	pop	{r4, pc}

Disassembly of section .init.text:

00000000 <init_module>:
EXPORT_SYMBOL(print_hello);


static int __init hello1_init(void)
{
   0:	e92d4010 	push	{r4, lr}
	pr_info("hello1 init");
   4:	e3000000 	movw	r0, #0
   8:	e3400000 	movt	r0, #0
   c:	ebfffffe 	bl	0 <printk>
	return 0;
}
  10:	e3a00000 	mov	r0, #0
  14:	e8bd8010 	pop	{r4, pc}

Disassembly of section .exit.text:

00000000 <cleanup_module>:

static void __exit hello1_exit(void)
{
	struct my_list_head *temp_first = head;
   0:	e3003000 	movw	r3, #0
   4:	e3403000 	movt	r3, #0
{
   8:	e92d4070 	push	{r4, r5, r6, lr}
	struct my_list_head *temp_second = temp_first;

	pr_debug("Print list start");
   c:	e3000000 	movw	r0, #0
  10:	e3400000 	movt	r0, #0
	struct my_list_head *temp_first = head;
  14:	e5934000 	ldr	r4, [r3]
	pr_debug("Print list start");
  18:	ebfffffe 	bl	0 <printk>
	while (temp_first != NULL) {
		pr_debug("Time spent %lld",
  1c:	e3005000 	movw	r5, #0
  20:	e3405000 	movt	r5, #0
	while (temp_first != NULL) {
  24:	e3540000 	cmp	r4, #0
  28:	0a00000b 	beq	5c <cleanup_module+0x5c>
		pr_debug("Time spent %lld",
  2c:	e5941010 	ldr	r1, [r4, #16]
  30:	e1a00005 	mov	r0, r5
  34:	e5942008 	ldr	r2, [r4, #8]
  38:	e594c014 	ldr	ip, [r4, #20]
  3c:	e594300c 	ldr	r3, [r4, #12]
  40:	e0512002 	subs	r2, r1, r2
  44:	e0cc3003 	sbc	r3, ip, r3
  48:	ebfffffe 	bl	0 <printk>
		temp_first->post_time - temp_first->time);

		temp_second = temp_first;
		temp_first = temp_second->next;
		kfree(temp_second);
  4c:	e1a00004 	mov	r0, r4
		temp_first = temp_second->next;
  50:	e5944000 	ldr	r4, [r4]
		kfree(temp_second);
  54:	ebfffffe 	bl	0 <kfree>
  58:	eafffff1 	b	24 <cleanup_module+0x24>
	}
	pr_debug("Print list end");
  5c:	e3000000 	movw	r0, #0
  60:	e3400000 	movt	r0, #0
  64:	ebfffffe 	bl	0 <printk>
	pr_info("hello1 exit");
  68:	e3000000 	movw	r0, #0
  6c:	e3400000 	movt	r0, #0
}
  70:	e8bd4070 	pop	{r4, r5, r6, lr}
	pr_info("hello1 exit");
  74:	eafffffe 	b	0 <printk>

```

## Висновок

В данній лабораторній роботі я модифікував код з 6 лабораторної роботи який тепер використовує  BUG_ON() замість друку повідомлення та повернення -EINVAL для неприпустимого значення параметра

