# muzzley Node.Js blink demo

This demo allows you to light on/off an onboard LED connected to the IO13.

## Dependencies

* [Node.Js v0.10](http://nodejs.org/download/)
  This demo runs with version 0.10 or later.

## Installing

First you must clone this repository using the command

    git clone https://github.com/muzzley/galileo-muzzley-blink.git

and enter the folder `nodejs`.

Then install Intel's mraa library:

    echo "src mraa-upm http://iotdk.intel.com/repos/1.1/intelgalactic" > /etc/opkg/mraa-upm.conf
    opkg update
    opkg install libmraa0

Once the muzzley Node.js lib is part of the Intel Dev Kit repository, run the following command:

    opkg install muzzley-client

To run the demo, type:

    node index.js
