# muzzley Node.Js blink demo

This demo allows you to light on/off an onboard LED connected to the IO13.

## Dependencies

* [Node.Js v0.10](http://nodejs.org/download/)
  This demo runs with version 0.10 or later.

## Installing

First you must install Intel's mraa library:

    opkg install libmraa

Once the muzzley JS lib is part of the Intel Dev Kit repository, run the following command:

   opkg install muzzley-client

To run the demo, type:

   node index.js