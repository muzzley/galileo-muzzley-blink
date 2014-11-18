var muzzley = require("muzzley-client");
var mraa = require('mraa');
var config = require("./config");

var gpio = new mraa.Gpio(config.pin); //LED hooked up to digital pin 13 (or built in pin on Galileo Gen1 & Gen2)
gpio.dir(mraa.DIR_OUT); //set the gpio direction to output
var gpioStatus = gpio.write(0); //Boolean to hold the state of Led
console.log(config.pin, "was set to", gpioStatus);

muzzley.connectApp(config.muzzley, function(err, activity){

  if(err){
    console.log("[error]", "createActivity ", err);
    return;
  }

  console.log("[info]", "Connected. activityId:", activity.activityId);

  activity.on('participantJoin', function(participant) {
    console.log("[info]", participant.name + " joins");

    participant.changeWidget('switch', function(err) {
      if (err) return console.log("[error]", "changeWidget", err );

      participant.on('action', function(action) {
        if(!action) return;

        gpio.write(action.v);
        console.log("Led switched to value", action.v);
      });
    });

    participant.on('quit', function() {
      console.log('[info]', participant.name + " quits");
    });
  });

});
