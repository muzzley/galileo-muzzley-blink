/*
Copyright (c) 2014, Muzzley

Permission to use, copy, modify, and/or distribute this software for
any purpose with or without fee is hereby granted, provided that the
above copyright notice and this permission notice appear in all
copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.
*/

//
// You can compile this application with the following command:
// g++ -std=c++0x -I/usr/include/muzzley Examples/galileo_app.cpp -o myapp -lmuzzley -lpthread
//
// And run it like this:
// ./myapp
//
// Once running, you can pair your smartphone to this app using
// the mobile muzzley application and the "Activity Id" that is
// written to the screen.
//

#define DEBUG 0

#define APP_TOKEN "3ddde2aa9832a038" // Get yours at muzzley.com
#define STATIC_ACTIVITY_ID ""        // Optional.
#define DEFAULT_IOPIN 13

#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <muzzley.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <mraa.h>

using namespace std;
using namespace __gnu_cxx;

static int iopin;
mraa_result_t r = MRAA_SUCCESS;
mraa_gpio_context gpio;


void sig_handler(int signo) {
  if (signo == SIGINT) {
      printf("closing IO%d nicely\n", iopin);
  }
  exit(signo);
}

int main(int argc, char* argv[]) {

  iopin = DEFAULT_IOPIN;

  mraa_init();
  cout << "MRAA Version: " << mraa_get_version() << endl << "Starting Blinking on IO" << iopin << endl << flush;
  gpio = mraa_gpio_init(iopin);
  if (gpio == NULL) {
    cout << "Are you sure that pin" << iopin << " you requested is valid on your platform?" << endl << flush;
    exit(1);
  }
  cout << "Initialised pin" << iopin << endl << flush;

  // set direction to OUT
  r = mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
  if (r != MRAA_SUCCESS) {
    mraa_result_print(r);
  }

  signal(SIGINT, sig_handler);

  // Create the Muzzley client
  muzzley::Client _client;

  // Register listener to be invoked when activity is sucessfully created.
  //
  // Don't bother to store the returned activityId, the Client class already does that,
  // access it through the 'getActivityId' method.
  //
  // Return 'false' if you want to stop other listeners from being invoked.
  _client.on(muzzley::ActivityCreated, [] (muzzley::Message& _data, muzzley::Client& _client) -> bool {
    cout << "Activity created with id " << (string) _data["d"]["activity"]["activityId"] << endl << flush;
    cout << "You can now pair your smartphone, using the muzzley app, to the activity id " << (string) _data["d"]["activity"]["activityId"] << endl << flush;
    return true;
  });

  _client.on(muzzley::ParticipantJoined, [] (muzzley::Message& _data, muzzley::Client& _client) -> bool {
    long participant_id = _data["d"]["participant"]["id"];
    string name = _data["d"]["participant"]["name"];

    cout << "Participant " << name << "(" << participant_id << ")" << " joined." << endl << flush;
    string participant_string;
    muzzley::tostr(participant_string, _data);

    // Change widget to a custom WebView widget
    muzzley::JSONObj _widget_opts;
    _widget_opts << "widget" << "switch";
    _client.changeWidget(participant_id, _widget_opts, [] (muzzley::Message& _data, muzzley::Client& _client) -> bool {

    });
    return true;
  });

  _client.on(muzzley::WidgetAction, [] (muzzley::Message& _data, muzzley::Client& _client) -> bool {
    string widget_data;
    muzzley::tostr(widget_data, _data["d"]);
    bool light_on = (bool) _data["d"]["v"];
    if (light_on) {
      cout << "Led is ON" << endl;
      r = mraa_gpio_write(gpio, 1);
    } else {
      cout << "Led is OFF" << endl;
      r = mraa_gpio_write(gpio, 0);
    }
    return true;
  });

  // Connects the application to the Muzzley server.
  //
  // It will start the application loop synchronously,
  // i.e. the program will not execute anything below this line.
  _client.connectApp(APP_TOKEN, STATIC_ACTIVITY_ID);

  return 0;
}
