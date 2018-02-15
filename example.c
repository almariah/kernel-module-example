#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/kthread.h>

static struct task_struct *thread_st;

static int some_work(void *unused ) {
  int i;
  for (i=0; i<10; i++) {
    printk(KERN_INFO "Module is working\n");
    ssleep(2);
  }
  return 0;
}


static int __init example_init(void) {

  printk(KERN_INFO "Module is loaded\n");

  thread_st = kthread_run(some_work, NULL, "some_work_thread");

  if (thread_st) {
    printk(KERN_INFO "Kernel thread created\n");
  } else {
    printk(KERN_ERR "Kernel thread failed\n");
  }

  return 0;
}

static void __exit example_exit(void) {
  kthread_stop(thread_st);
  printk(KERN_INFO "Module unloading...\n");
}

module_init(example_init);
module_exit(example_exit);

MODULE_LICENSE("Apache");
MODULE_AUTHOR("Addullah Almariah");
MODULE_DESCRIPTION("Kernel Module Example");
