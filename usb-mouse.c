#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
 
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id)
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
 
static struct usb_driver mouse_driver =
{
    .name = "mouse_driver",
    .id_table = mouse_table,
    .probe = pen_probe,
    .disconnect = mouse_disconnect,
};
 
static int __init pen_init(void)
{
    return usb_register(&mouse_driver);
}
 
static void __exit pen_exit(void)
{
    usb_deregister(&mouse_driver);
}
 
module_init(pen_init);
module_exit(pen_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Malpp");
MODULE_DESCRIPTION("USB Pen Registration Driver");