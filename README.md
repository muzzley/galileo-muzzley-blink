# muzzley blink demo

This repository demonstrates how [muzzley](https://www.muzzley.com) can be used on an Intel Galileo Gen1, Gen2 and Edison using C++ and Node.js. Once integrated, you'll be able to remotely control your board from anywhere.

## Dependencies

In order to be able to run these examples, you must create a muzzley application token.

* Go to muzzley website and [Sign Up](https://muzzley.com/register).
* Once Signed Up and logged in, go to the [Apps](https://www.muzzley.com/apps) section.
* Create a new app and provide its name.
* Back in the apps listing page, click on the app you've just created to open it's details.
* On the right you'll see the `App Token`. Copy it as you'll have to paste it into the examples.

These demos use the native muzzley [switch widget](https://www.muzzley.com/documentation/widgets/switch.html) to effortlessly provide a switching interface in your mobile device. You can create your own HTML-based control interfaces by creating a muzzley [Webview widget](https://www.muzzley.com/documentation/widgets/webview.html).


## The demos are available in the following development environments:

* [C++](https://github.com/muzzley/galileo-muzzley-blink/tree/master/cpp)
* [Node.Js](https://github.com/muzzley/galileo-muzzley-blink/tree/master/nodejs)
