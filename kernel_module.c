#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h> 
#include <linux/uaccess.h>
#include <linux/sched.h> 
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/sched/signal.h>
#include <asm/uaccess.h>

#define BUFFER_SIZE 1000
#define DEVICE_NAME "process_list"
MODULE_LICENSE("Dual BSD/GPL");

int my_close(struct inode *pinode, struct file *pfile);
int my_close(struct inode *pinode, struct file *pfile);
ssize_t my_read(struct file *pfile, char *buffer, size_t length, loff_t *offset);
char *getState(long);
struct task_struct *curr_proc;
int numberofOpens;
char buffer[256];

char *getState(long state)
{

        switch (state)
        {
                case TASK_RUNNING:
                        return "TASK_RUNNING";
                case TASK_INTERRUPTIBLE:
                        return "TASK_INTERRUPTIBLE";
                case TASK_UNINTERRUPTIBLE:
                        return "TASK_UNINTERRUPTIBLE";
                case __TASK_STOPPED:
                        return "__TASK_STOPPED";
                case __TASK_TRACED:
                        return "__TASK_TRACED";
                case TASK_IDLE:
                        return "TASK_UNINTERRUPTIBLE | TASK_NOLOAD";
                case TASK_KILLABLE:
                        return "TASK_WAKEKILL | TASK_UNINTERRUPTIBLE";
                case TASK_STOPPED:
                        return "TASK_WAKEKILL | __TASK_STOPPED";
                case TASK_TRACED:
                        return "TASK_WAKEKILL | __TASK_TRACED";
                default:
                {

                        return "Unknown";
                }
        }
}
// The prototype functions for the character driver 
int my_open(struct inode *pinode, struct file *pfile)
{

        printk(KERN_ALERT "Inside the %s function \n", __FUNCTION__);
        return 0;
}
int my_close(struct inode *pinode, struct file *pfile)
{
        printk(KERN_ALERT "Inside the %s function \n", __FUNCTION__);
        return 0;
}
ssize_t my_read(struct file *pfile, char *buffer, size_t length, loff_t *offset)
{
        int status;
        struct task_struct *task;
        char process[BUFFER_SIZE];
        memset(process, 0, sizeof(char) * BUFFER_SIZE);
        printk(KERN_INFO "Process List-> Reading the Prcoess Information...\n");

        for_each_process(task) //iterating through list of perocesses
        {
                if (curr_proc == task)
                {
                        char *state = getState(task->state);
                        memset(process, 0, sizeof(char) * BUFFER_SIZE);
                        printk(process, "PID=%d PPID=%d CPU=%d STATE=%s", task->pid, task->parent->pid,task_cpu(task), state);  
                        sprintf(process, "PID=%d PPID=%d CPU=%d STATE=%s", task->pid, task->parent->pid,task_cpu(task), state); 
                        printk(KERN_INFO "Process:--> %s", process);
                        status = copy_to_user(buffer, process, strlen(process)); //copying block of data to user space
                        if (status != 0)
                        {
                                printk(KERN_ALERT "error copying data to the user");
                                return -EFAULT; 
                        }
                        curr_proc = next_task(task);
                        break;
                }
        }
        return strlen(process);
}
ssize_t my_write(struct file *pfile, const char *buffer, size_t length, loff_t *offset)
{
        printk(KERN_ALERT "Inside the %s function \n", __FUNCTION__);
        return length;
}

struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write = my_write,

};


int __init my_module_init(void)
{
        printk(KERN_ALERT "Inside the %s function \n", __FUNCTION__);

        /*Register */
        register_chrdev(500, "DEVICE_NAME_SHRIJEET", &my_fops);
        return 0;
}

void __exit my_module_exit(void)
{

        printk(KERN_ALERT "Inside the %s function \n", __FUNCTION__);

        /*Register */
        unregister_chrdev(500, "DEVICE_NAME_SHRIJEET");

        printk(KERN_ALERT "Device sucessfully removed\n");
}

module_init(my_module_init);
module_exit(my_module_exit);