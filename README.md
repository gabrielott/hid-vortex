# Unnoficial Linux HID driver for Vortex keyboards

Some Vortex keyboards support n-key rollover (NKRO)
but it doesn't work on Linux
because of a buggy report descriptor.
This driver fixes the incorrect descriptor
and allows NKRO to work.

## Supported keyboards

- Pok3r RGB

If you have a Vortex keyboard
with non-working NKRO on Linux please open an issue and
I'll try and add support to it.

## Installation

Clone the repository and `cd` into it.

Then run as root:
```
dkms add .
dkms build hid-vortex/1.0
dkms install hid-vortex/1.0
```

## Thanks

- [hid-semitek](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-semitek.c) (where I copied 99% of the module from)
- [hid-nx-dkms](https://github.com/emilyst/hid-nx-dkms) (where I copied the dkms stuff from)
