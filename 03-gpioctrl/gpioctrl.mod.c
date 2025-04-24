#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
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

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xe4477d56, "gpiod_set_value" },
	{ 0xb0d2a97, "gpio_to_desc" },
	{ 0xac88e55b, "gpiod_direction_output" },
	{ 0xcee724e1, "gpiod_direction_input" },
	{ 0xfff2d03d, "gpiod_get_value" },
	{ 0x122c3a7e, "_printk" },
	{ 0x67a35d9, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "F4154BAEB13AEA621F2860B");
