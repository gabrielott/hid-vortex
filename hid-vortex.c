// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *  HID driver for Vortex keyboards
 *
 *  Copyright (c) 2023 Gabriel Ottoboni
 *
 *  Some Vortex keyboards support NKRO but it doesn't work on Linux because
 *  of a buggy report descriptor. This driver fixes the incorrect descriptor.
 *  
 *  Supported keyboards:
 *		- Pok3r RGB
 *
 */

#include <linux/device.h>
#include <linux/hid.h>
#include <linux/module.h>

#include "hid-ids.h"

static __u8 *vortex_report_fixup(struct hid_device *hdev, __u8 *rdesc,
                                  unsigned int *rsize)
{
	/* In the report descriptor for interface 2, fix the incorrect
	   description of report ID 0x04 (the report contains a
	   bitmask, not an array of keycodes.) */
	if (*rsize == 0x86 && rdesc[0x83] == 0x81 && rdesc[0x84] == 0x00) {
		hid_info(hdev, "fixing up Vortex report descriptor\n");
		rdesc[0x84] = 0x02;
	}
	return rdesc;
}

static const struct hid_device_id vortex_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOR_ID_HOLTEK_ALT, USB_DEVICE_ID_VORTEX_POKER_3_RGB) },
	{ }
};
MODULE_DEVICE_TABLE(hid, vortex_devices);

static struct hid_driver vortex_driver = {
	.name = "vortex",
	.id_table = vortex_devices,
	.report_fixup = vortex_report_fixup,
};
module_hid_driver(vortex_driver);

MODULE_LICENSE("GPL");
