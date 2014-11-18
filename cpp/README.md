# muzzley C++ blink demo

This demo allows you to light on/off an onboard LED connected to the IO13.

## Dependencies

* [Lib mraa](https://github.com/intel-iot-devkit/mraa)
  This library is provided by Intel, it offers you some tools to manipulate your board pins.
* [Lib muzzley](https://github.com/muzzley/muzzley-client-cpp)
  This library allows you to easily exchange messages between your mobile devices and your board, while being able to easily set up an interaction interface.

## Installing

First you must install Intel's mraa library:

    echo "src mraa-upm http://iotdk.intel.com/repos/1.1/intelgalactic" > /etc/opkg/mraa-upm.conf
    opkg update
    opkg install libmraa0

Once the muzzley C++ lib is part of the Intel Dev Kit repository, run the following command:

    opkg install muzzley-cpp-client

Then you can compile the example with the following command:

    g++ -std=c++0x -I/usr/include/muzzley muzzley_blink.cpp -o myapp -lmuzzley -lmraa -lpthread

To run the demo, type:

    ./myapp
