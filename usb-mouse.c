#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
 
static int mouse_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    printk(KERN_INFO "Pen drive (%04X:%04X) plugged\n", id->idVendor, id->idProduct);
    return 0;
}
 
static void mouse_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "Pen drive removed\n");
}
 
static struct usb_device_id mouse_table[] =
{
    { USB_DEVICE(0x045e, 0x0084) },
    {} /* Terminating entry */
};
MODULE_DEVICE_TABLE (usb, mouse_table);
 
static ssize_t skel_read( struct file *file, char *buffer, size_t count,
	loff_t *ppos )
{
	printk( KERN_INFO "Pen drive (%04X) plugged\n", buffer );
	return 0;
}

static const struct file_operations mouse_fops = {
	.read = skel_read
};

static struct usb_driver mouse_driver =
{
    .name = "mouse_driver",
    .id_table = mouse_table,
    .probe = mouse_probe,
    .disconnect = mouse_disconnect,
};
 
static int __init mouse_init(void)
{
    return usb_register(&mouse_driver);
}
 
static void __exit mouse_exit(void)
{
    usb_deregister(&mouse_driver);
}
 
module_init(mouse_init);
module_exit(mouse_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Malpp");
MODULE_DESCRIPTION("USB Pen Registration Driver");