#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.>

int simple_init(void) {
	printk(KERN_INFO "Loading Module\nPachon");
	return 0;
}
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\nPachon")
}
module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("El pachon negro con agua");
MODULE_AUTHOR("Cristopher Barrios");