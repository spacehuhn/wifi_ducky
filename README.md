# Wi-Fi Ducky
Upload, save and run keystroke injections remotely with an ESP8266 + ATmega32u4

## Contents
- [Introduction](#introduction)
  - [What it is](#what-it-is)
  - [How it works](#how-it-works)
  - [The benefits of adding Wi-Fi](#the-benefits-of-adding-wi-fi)
- [Disclaimer](#disclaimer)
- [Installation](#installation)
  - [Preparation](#preparation)  
  - [ESP8266](#esp8266)
  - [Arduino ATmega32u4](#arduino-atmega32u4)
  - [Wire everything up](#wire-everything-up)
- [How to use it](#how-to-use-it)
- [Improvements](#improvements)
- [License](#license)
- [Sources and additional links](#sources-and-additional-links)

## Introduction ##

### What it is

It's a Wi-Fi controlled BadUSB device to remotely execute Ducky Scripts. 

Using a USB device which act as a keyboard to inject keystrokes is well kown these days. 
The [USB Rubber Ducky](https://hakshop.com/products/usb-rubber-ducky-deluxe) by [Hak5](https://www.hak5.org/) is THE hacker gadget for this kind of attack. It introduced a simple script language called *Ducky Script*, which this project uses too.

### How it works

I will use an ESP8266 for this project. This tiny Wi-Fi chip has its own file system called [SPIFFS](https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md). It doesn't replace a micro-sd card, but it should be enough for most payloads.  

Although the ESP8266 is awesome, it doesn't have native USB, which means it can't act as a keyboard :(  
([cnlohr](https://github.com/cnlohr) made a cool project on this and added a USB stack himself: https://github.com/cnlohr/espusb. The problem with that is, that it isn't compatible with the current SDK version, also I wanted to use Arduino to make it more user friendly.)  

Here comes the ATmega32u4 into play!  
It can act as keyboard and thanks to [Seytonic](http://youtube.com/seytonic) run Ducky Script ([link](https://github.com/Seytonic/Duckduino-microSD)).  
So what I did is connecting the ATmega to the ESP8266 via serial.

The ESP will open up a Wi-Fi access point and host a webinterface from what you can upload and manage your scripts.  
When you hit run, it will send the script to the ATmega, which then will execute it on the target machine.  

### The benefits of adding Wi-Fi ###

**But why add Wi-Fi** ...you might ask.  
With Wi-Fi you can upload and run your Ducky Script payloads remotely.  
You just need to plug the device in, connect to its Wi-Fi network and you have full control over the target machine.  

It also gives you one big advantage over other BadUSBs, you can test your scripts live! You don't need to copy them onto a micro-sd card or compile them. You can run them live over the webinterface, which makes its super easy for testing and improving your scripts.

It also adds a lot of possibilites for different attacks.   
You could make the target download executables from the Wi-Fi chip, instead of the internet.
Or execute different attacks and send the results back to the Chip. Or open up a reverse shell on the ESP8266s Wi-Fi.  
And so on... there are so much possibilities!

## Disclaimer

Use it only for testing purposes on your own devices!  
I don't take any responsibility for what you do with this project.  

## Installation

### Short version:
Upload the `arduino_wifi_duck` sketch to your ATmega32u4 and upload the `esp8266_wifi_duck` sketch to your ESP8266.  
Then connect the RX (Arduino) to TX (ESP8266) and TX (Arduino) to RX (ESP8266).

---

### Preparation

What you will need:
- **ESP8266 Wi-Fi chip**  
  I recommend using an ESP-12. It's widely used, cheap and has 4MB of flash memory
- **ATmega32u4**  
  I recommend using some kind of Arduino board. The Arduino Micro and Arduino Leonardo use an ATmega32u4 for example. You could also get a Arduino Pro Micro or other cheap Arduino clones which use the ATmega32u4. I will use a CJMCU-Beetle ATmeaga32u4.
- **(a 3.3V regulator)**  
  I put that in brackets because you will only need this if your ATMega32u4 board doesn't provides 3.3V. The ESP8266 only works with 3.3V, so depending on your board you may need a regulator to get 3.3V out of the 5V.
- **Some skill, knowledge and common sense on this topic**  
  That's probably the most important part here. **This project is not noob friendly!** If you are a beginner, please start with other projects and get some knowledge about how Arduino and its code works, how to handle errors and how to work with the ESP8266. **I can't cover every little detail here. Please respect that.** Depending on your hardware choices you may need to add or change a bit of the Arduino code.  

### ESP8266

[coming soon]

### Arduino ATmega32u4

[coming soon]

### Wire everything up

[coming soon]

## Improvements

My wishlist:
- add support for Digispark (ATtiny85) as alternative for the ATmega32u4
- change settings within the webinterface (Wi-Fi SSID, password etc.)
- full support of all Ducky Script commands (REPLAY is missing)
- auto execute scripts
- add mouse
- control over the internet

## License

This project is licensed under the MIT License - see the [license file](LICENSE) file for details

## Sources and additional links

The USB Rubber Ducky: https://hakshop.com/products/usb-rubber-ducky-deluxe

The Malduino (a Rubber Ducky alternative by Seytonic): https://www.indiegogo.com/projects/malduino-badusb-arduino-usb#/

Seytonic: http://youtube.com/seytonic
          https://github.com/seytonic

Arduino Ducky Script interpreter: https://github.com/Seytonic/Duckduino-microSD

Cnlohrs ESP8266 USB Software Driver: https://github.com/cnlohr/espusb
