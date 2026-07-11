#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x92997ed8, "_printk" },
	{ 0xf811cb34, "init_net" },
	{ 0x94078e9e, "nf_unregister_net_hook" },
	{ 0x037a0cba, "kfree" },
	{ 0x779e24bf, "init_task" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x950eb34e, "__list_del_entry_valid_or_report" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0x3a84df8f, "kmalloc_caches" },
	{ 0x1692071a, "__kmalloc_cache_noprof" },
	{ 0x3c69d25d, "nf_register_net_hook" },
	{ 0x5500938b, "module_layout" },
};

MODULE_INFO(depends, "");

