# Wi-Fi Ducky
Upload, save and run keystroke injections remotely with an ESP8266 + ATmega32u4 or ATtiny85

## Contents
- [Introduction](#introduction)
  - [What it is](#what-it-is)
  - [How it works](#how-it-works)
  - [The benefits of Wi-Fi](#the-benefits-of-wi-fi)
- [Disclaimer](#disclaimer)
- [Installation](#installation)
  - [Preparation](#preparation)  
  - [ESP8266](#esp8266)
  - [Arduino ATmega32u4](#arduino-atmega32u4)
  - [Digispark ATtiny85](#digispark-aTtiny85)
  - [Wire everything up](#wire-everything-up)
- [How to use it](#how-to-use-it)
- [FAQ](#faq)
- [License](#license)
- [Sources and additional links](#sources-and-additional-links)

## Introduction ##

### What it is

It's a Wi-Fi controlled BadUSB device to remotely execute Ducky Scripts. 

Using a USB device which act as a keyboard to inject keystrokes is well kown these days. 
The [USB Rubber Ducky](https://hakshop.com/products/usb-rubber-ducky-deluxe) by [Hak5](https://www.hak5.org/) is THE hacker gadget for this kind of attack. It introduced a simple script language called *Ducky Script*, which we will be using for this project too.  

### How it works

I will use an ESP8266 for this project. This tiny Wi-Fi chip has its own file system called [SPIFFS](https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md). It doesn't replace a micro-sd card, but should be enough for most of your payloads.  

Although the ESP8266 is awesome, it doesn't have native USB :(  
(@cnlohr made a cool project on this and added a USB stack himself: https://github.com/cnlohr/espusb. The problem with that is that it isn't compatible with the current SDK version, also I wanted to use Arduino to make it more user friendly.)  

Here comes the ATmega32u4 into play!  
It can act as keyboard and thanks to @seytonic run Ducky Script [link](https://github.com/Seytonic/Duckduino-microSD).  
So what I did is connecting the ATmega to the ESP8266 via serial.

The ESP will open up a Wi-Fi access point and host a webinterface from what you can upload and manage and your scripts.  
When you hit run, it will send the script to the ATmega which then will execute it on the target machine.  

### The benefits of Wi-Fi ###

** But why add Wi-Fi ** ...you might ask.  
With Wi-Fi you can upload and run your Ducky Script payloads remotely, which can be super usefull for pentesting!  
You just need to plug the device in, connect to its Wi-Fi network and you have full control over the target machine.  

It also adds a lot of possibilites for different attacks.   
You could make the target download executables from the Wi-Fi chip instead from the internet.
Or execute different attacks and send the results back to the Chip. Or open up a reverse shell on the ESP8266s Wi-Fi.  
And so on... there are so much possibilities!

## Disclaimer

Use it only for testing purposes on your own devices!

## Installation

coming soon.. I guess?

## FAQ

## License

This project is licensed under the MIT License - see the [license file](LICENSE) file for details

## Sources and additional links
