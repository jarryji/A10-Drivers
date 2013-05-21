#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x7d276e4a, "module_layout" },
	{ 0xb0285735, "platform_driver_unregister" },
	{ 0x22adcd06, "platform_driver_probe" },
	{ 0xe450b1f9, "platform_device_register_resndata" },
	{ 0xbdf94507, "gpio_read_one_pin_value" },
	{ 0x20fd0cbb, "gpio_write_one_pin_value" },
	{ 0x5fa32a89, "gpio_set_one_pin_io_status" },
	{ 0x4b729722, "kmalloc_caches" },
	{ 0x383e8a27, "gpio_request_ex" },
	{ 0x84c41780, "script_parser_fetch" },
	{ 0x9a9ce393, "kmem_cache_alloc" },
	{ 0x27e1a049, "printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x2df11e47, "platform_device_unregister" },
	{ 0x344a50ed, "gpio_release" },
	{ 0x37a0cba, "kfree" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "C7CCDE57C2BBC861E356D7A");
