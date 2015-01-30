# muzzley Node.Js blink demo

This demo allows you to light on/off an onboard LED connected to the IO13.

## Dependencies

* [Node.Js v0.10](http://nodejs.org/download/)
  This demo runs with version 0.10 or later.

## Installing

First you must clone this repository using the command

    git clone https://github.com/muzzley/galileo-muzzley-blink.git

Then install Intel's mraa library:

    echo "src mraa-upm http://iotdk.intel.com/repos/1.1/intelgalactic" > /etc/opkg/mraa-upm.conf
    opkg update
    opkg install libmraa0

Once the Intel MRAA lib is part of the Intel Dev Kit repository, run the following command inside the project's `nodejs` folder:

    npm install

## Running the demo

Enter the folder `nodejs` and type the following command

    node index.js

The `activityId` will be printed to your console. Using the muzzley app in your Android, iOS or WP8 smartphone, press the menu (three vertical dots) button in the top right and choose "Muzzley Key".  Enter the generated `activityId` and your smartphone should become a switch interface. Pressing the switch should turn your board's LED on and off.
