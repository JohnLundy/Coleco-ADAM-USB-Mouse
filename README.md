# **Coleco ADAM USB Mouse**
### _Developed on the Arduino UNO Rev.3_
Coleco ADAM and Colecovision USB Mouse code written for the Arduino UNO R3 was developed for use with the [Coleco ADAM USB Mouse UNO Shield](https://github.com/JohnLundy/Coleco-ADAM-USB-Mouse-UNO-Shield) hardware project. This project was inspired by the original ADAM Mouse that is no longer available and wanted to offer a replacement option using modern USB hardware that is easily obtained.

## Features
- Designed using the popular Arduino UNO Rev.3, USB HOST Shield, and the [Coleco ADAM USB Mouse UNO Shield](https://github.com/JohnLundy/Coleco-ADAM-USB-Mouse-UNO-Shield)

- Works with all modern off-the-shelf USB mice as well as wireless mice

- Ability to change mouse sensitivity and delay balance on the fly for better compatibility with a wide range of software titles

## Design Features
The ADAM and Colecovision use two separate commons for joystick switch control and neither is connected to true ground. Both commons are strobed with a 350mS pulse width with a low of -0.7v and a high of 2.8v. This code controls optocoupler ICs that isolate the controller signals that otherwise cannot be directly connected to the ADAM and simulates controller switch closures.

Both systems never had any software titles specifically designed for mouse control. This added an extra layer of complexity to the design to help compensate for the lack of any kind of standard amongst the wide range of software titles. The design choice of using a 10k potentiometer on the analog (A0) line of the Arduino UNO creates a voltage range that can be sensed to manipulate and adjust mouse sensitivity and joystick delay balance on the fly. With extensive testing, this has proven to work very well to compensate for the wide variety of joystick control sensitivities amongst different software titles. A special button to enable/disable a dedicated precision mode was added for ADAM users for paint programs that need precision movements that otherwise wouldn't work for games.

A workaround was also needed for games that required the joystick to be held down during play to work. This is accomplished by pressing the center mouse button to toggle on/off an increased delay to simulate holding the joystick down in any specific direction.

## Hardware Used In This Project
|Part|Source|
| ------ | ------ |
| ADAM Mouse USB Shield | https://github.com/JohnLundy/Coleco-ADAM-USB-Mouse-UNO-Shield |
| UNO Rev.3 Board ATmega328P with USB Cable or Equivalent | Ordered from Amazon |
| USB Host Shield for Arduino UNO MEGA 2560 or Equivalent | Ordered from Amazon |
| Colecovision Controller Y Cable Splitter | retrogameboyz on Ebay|
| USB Mouse | Off-the-shelf USB mouse found anywhere |
| 9V Power Supply (Center Positive 5.5x2.1mm) or USB Cable for power | Easy internet search for UNO power supply  |

## How To Assemble
Follow the instructions found [here](https://github.com/JohnLundy/Coleco-ADAM-USB-Mouse-UNO-Shield) 

## Loading Code
##### Arduino IDE mothod

1 - Install the [Arduino IDE](https://www.arduino.cc/en/software) and configure it for "Board" type "Arduino/Genuino UNO" under the "Tools" dropdown menu

2 - Install the "USB Host Library Rev. 2.0" library by Oleg Mazurov from the IDE "Tool" dropdown menu and select "Manage Libriries..."

3 - Download the latest Coleco ADAM USB Mouse release from this GitHub repository and load it in the Arduino IDE

4 - Connect the UNO to the USB port. Select the correct "Port" COM setting under the "Tool" dropdown menu

5 - Press the “Upload” button in the Arduino IDE to compile and upload

_*Note:* It has been found that some cheap versions of UNO Rev.3's will require changing the "Tools" dropdown to select "Board" and select "Nano" and changing the processor setting to either "ATmega328P" or "ATmega328P (Old Bootloader)" to successfully load code._

##### XLoader method
1 - Install [XLoader](https://www.hobbytronics.co.uk/arduino-xloader) (Windows only) and configure it for "Device" type "Uno(ATmega328)" and a "Baud rate" of "115200"

2 - Download the latest USB_ADAM_Mouse_UNO.hex from this GitHub repository and select "[...]" to load it in XLoader

3 - Connect the UNO to the USB port and select the correct "COM port" in the dropdown

4 - Press the “Upload” button to load code

## How To Connect
It is recommended to use a joystick controller Y cable splitter to allow the use of keypad functionality while using the mouse. Connect the completed Arduino UNO ADAM USB Mouse assembly to the ADAM console joystick connector via DSub 9-pin connector cable. With the HOST Shield USB connector facing the user, connect the USB mouse. Power the Arduino UNO board with either a 9V Power Supply (Center Positive 5.5x2.1mm) or USB Cable power source and the mouse LED should now be illuminated. Lastly, power on the ADAM console or Colecovision to now use the mouse.

## How it works
- The ADAM USB Mouse assembly is designed to have the HOST Shield USB connector facing the user. Note the location of the trimmer resistor (potentiometer), small button switch, and LED. These three features are how the ADAM USB Mouse will be operated as well as the center button of the mouse.

- The position of the potentiometer is how to adjust mouse sensitivity and joystick delay balance on the fly. Adjustments will be stated in "o'clock" positioning for future reference. A counterclockwise turn will increase mouse sensitivity and decrease joystick delay while a clockwise turn will decrease mouse sensitivity and increase joystick delay.

- The small button switch was added to toggle a dedicated precision mode for ADAM users for paint programs that need precision movements that otherwise wouldn't work for games. This will override any positional setting of the potentiometer and will illuminate the LED to indicate mode is active.

- The center mouse button will toggle on/off an increased delay to simulate holding the joystick down in any specific direction for games that require this. It is also useful for creating straight lines in paint programs and scrolling lists.

##### This picture is show in the 12 o'clock position

![12oclockposition](https://github.com/JohnLundy/Coleco-ADAM-USB-Mouse/raw/main/docs/12oclockposition.jpg)

## Example settings
The range is 8 to 4 o'clock positions. Many games and programs like the 2 o'clock position and is usually a good starting point for testing.

| Game/Program | O'Clock Position |
| ------ | ------ |
| ADAM BOMB | 2 |
| ADAM BOMB 2 | 1-2 |
| AE | 2-3 |
| Beamrider | 2 |
| Blockade Runner | 2 |
| Boulder Dash | 8 |
| Buck Rogers | 2-3 |
| Carnival | 2 |
| Centipede | 9 |
| Cosmic Avenver | 2 |
| Galaxian | 2 |
| Gorf | 2 |
| Gyruss | 2 |
| KABOOM! | 8 |
| Mecha 8 | 3 |
| Mecha 9 | 3 |
| Meteoric Shower | 12 |
| Operation Wolf | 2 |
| Space Fury | 8 |
| Spectron | 4 |
| Star Force | 2 |
| Star Trek | 8 |
| Strike It! | Precision |
| Super Cross Force | 8 |
| Threshold | 8 |
| Time Pilot | 8 |
| ADAMCalc | 2 |
| PaintMASTER | 8 and use precision mode when needed |
| PowerPAINT | 8 and use precision mode when needed |

## License
GNU General Public License v3.0

![have_fun](https://github.com/JohnLundy/Coleco-ADAM-USB-Mouse/raw/main/docs/have_fun.jpg)

**Have Fun!**

