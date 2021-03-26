#include <hidboot.h>        // https://github.com/felis/USB_Host_Shield_2.0
#include <usbhub.h>         // https://github.com/felis/USB_Host_Shield_2.0
#include <SPI.h>
//=============================================================================================================
//===================================     ADAM USB Mouse Interface     ========================================
//===================================          By: John Lundy          ========================================
//===================================   https://github.com/JohnLundy   ========================================
//=============================================================================================================
//===========       Borrowed example code from https://github.com/felis/USB_Host_Shield_2.0      ==============
//===========                                       and                                          ==============
//===========               https://www.instructables.com/Atari-8-Bit-Optical-Mouse              ==============
//===========                                                                                    ==============
//=========== ADAM uses two commons for joystick switch control and neither is connected to true ==============
//===========       ground. Both commons are strobed with a 350mS pulse width with a low of      ==============
//===========        -0.7v and a high of 2.8v. This requires the use of optocoupler ICs to       ==============
//===========        isolate the controller signals because low signals from the Arduino         ==============
//===========       cannot be directly connected to the ADAM to simulate controller switch       ==============
//===========     closures. This project uses ILQ and ILD optocoupler ICs to accomplish this.    ==============
//===========                                                                                    ==============
//===========                  This code was tested using the following:                         ==============
//===========          Arduino UNO ADAM Mouse Shield https://github.com/JohnLundy                ==============
//===========          Arduino UNO R3 https://www.amazon.com/gp/product/B016D5KOOC               ==============
//===========     Arduino USB host shield https://www.amazon.com/gp/product/B07J2KKGZ4with       ==============
//===========                                                                                    ==============
//===========      Verify both input 3.3V and 5V pads are bridged on USB host shield next        ==============
//===========           to power header. Verify 5V pad is bridged for VBUS power.                ==============
//===========                                                                                    ==============
//===========                        Initial release v1.00 (3/26/2021)                           ==============
//=============================================================================================================

//==================================[        Arduino Uno Pin Connections     ]=================================
const byte armpin = 2;             // (D2) ARM output pin
const byte firepin = 3;            // (D3) FIRE output pin
const byte uppin = 4;              // (D4) UP output pin
const byte downpin = 5;            // (D5) DOWN output pin
const byte leftpin = 6;            // (D6) LEFT output pin
const byte rightpin = 7;           // (D7) RIGHT output pin
const byte precpin = 8;            // (D8) Precision mode input button pin
const byte ledpin = 12;            // (D12 LED output pin
const int  senspin = A0;           // (A0) Analog input pin for mouse sensitivity adjust (trimmer pot)

//==================================[       Varibles and Configurations       ]================================
const byte Version[3] = {1,0,0};   // Version number v.1.00
int mouse_sensitivity;             // USB mouse sensitivity setting fine tuned by senspin analog 10k ohm trimmer potentiometer on pin A0
                                   // Range is 3 - 17 for best performance with a wide range of games - clockwise turn of trimmer potentiometer the higher the value
                                   // Majority of games like 12 (2 o'clock position of potentiometer)
                                   // The range is 3 at 8 o'clock through 17 at 4 o'clock of the trimmer potentiometer
int  joy_delay;                    // Joystick delay setting is derived from sensitivity value - range is 3-10
byte joy_holddelay;                // Joystick hold delay setting (games that require joystick to be held down) is derived from current joystick delay value - range is 8-15
int  sens_adj;                     // Store analog sensitivity adjustment value
bool arm = false;                  // ARM controller button status  - OFF to start
bool fire = false;                 // FIRE controller buton status  - OFF to start
bool hold = false;                 // Hold delay center mouse button status - OFF to start
bool prec = false;                 // Precision button status - OFF to start
byte up = 0;                       // UP direction
byte down = 0;                     // DOWN direction
byte left = 0;                     // LEFT direction
byte right = 0;                    // RIGHT direction
int  Xmovement = 0;                // USB mouse left and right variable
int  Ymovement = 0;                // USB mouse up and down variable

//==================================[         Mouse Direction Detection       ]================================
class MouseRptParser : public MouseReportParser
{
  protected:
    void OnMouseMove  (MOUSEINFO *mi);
    void OnLeftButtonUp (MOUSEINFO *mi);
    void OnLeftButtonDown (MOUSEINFO *mi);
    void OnRightButtonUp  (MOUSEINFO *mi);
    void OnRightButtonDown  (MOUSEINFO *mi);
    void OnMiddleButtonUp (MOUSEINFO *mi);
    void OnMiddleButtonDown (MOUSEINFO *mi);
};
void MouseRptParser::OnMouseMove(MOUSEINFO *mi)         // USB Mouse movement detect
{
  Xmovement = mi->dX;                                   // Left movement
  if (Xmovement < -mouse_sensitivity)
  {
      left = abs(Xmovement);
      right = 0;
      Serial.println("Left");
  }
  else if ((Xmovement < -mouse_sensitivity/2) && right)
  {
    left = 0;
    right = 0;
  }
  if (Xmovement > mouse_sensitivity)                    // Right Movement
  {
    right = abs(Xmovement);
    left = 0;
    Serial.println("Right");
  }
  else if ((Xmovement > mouse_sensitivity/2) && left)
  {
    right = 0;
    left = 0;
  }
  if (Ymovement < -mouse_sensitivity)                   // Up Movement
  {
    up = abs(Ymovement);
    down = 0;
    Serial.println("Up");
  }
  else if ((Ymovement < -mouse_sensitivity/2) && down)
  {
    up = 0;
    down = 0;
  }
  Ymovement = mi->dY;                                   // Down Movement
  if (Ymovement > mouse_sensitivity)
  {
    down = abs(Ymovement);
    up = 0;
    Serial.println("Down");
  }
  else if ((Ymovement > mouse_sensitivity/2) && up)
  {
    up = 0;
    down = 0;
  }
};

//==================================[           Mouse Button Detection        ]================================
void MouseRptParser::OnLeftButtonUp	(MOUSEINFO *mi)     // Left button unpressed
{
  Serial.println("Left Button Unpressed");
  fire = false;
};
void MouseRptParser::OnLeftButtonDown	(MOUSEINFO *mi)   // Left button pressed
{
  Serial.println("Left Button pressed");
  fire = true;
};
void MouseRptParser::OnRightButtonUp	(MOUSEINFO *mi)   // Right button unpressed
{
  Serial.println("Right Button Unpressed");
  arm = false;
};
void MouseRptParser::OnRightButtonDown	(MOUSEINFO *mi) // Right button pressed
{
  Serial.println("Right Button Pressed");
  arm = true;
};
void MouseRptParser::OnMiddleButtonUp	(MOUSEINFO *mi)   // Middle button unpressed
{
  Serial.println("Middle Button Unpressed");
};
void MouseRptParser::OnMiddleButtonDown	(MOUSEINFO *mi) // Middle button pressed
{
  hold =!hold;
  Serial.print("Middle Button Pressed - hold mode toggled ");
  Serial.println(bool(hold));
};

//==================================[        USB Host and Mouse Driver        ]================================
USB   Usb;
USBHub  Hub(&Usb);
HIDBoot <USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb);        // Start USB mouse protocol

MouseRptParser Prs;

//==================================[                  Setup                  ]================================
void setup()
{
  Serial.begin( 115200 );
  Serial.println("ADAM USB Mouse Interface");
  Serial.println("    By: John Lundy");
  Serial.print(" Booting: Version ");
  Serial.println(String(Version[0]) + "." + String(Version[1]) + String(Version[2]));
  if (Usb.Init() == -1){
    Serial.println("ERROR: OSC did not start.");
    Serial.println("Verify both input 3.3V and 5V pads are bridged");
    Serial.println("on USB host shield next to power header.");
    Serial.println("Verify 5V pad is bridged for VBUS power.");
  }
  delay( 200 );
  HidMouse.SetReportParser(0, &Prs);
  pinMode(armpin, OUTPUT);         // Set optocoupler control pins as outputs
  pinMode(firepin, OUTPUT);
  pinMode(uppin, OUTPUT);
  pinMode(downpin, OUTPUT);
  pinMode(leftpin, OUTPUT);
  pinMode(rightpin, OUTPUT);
  pinMode(ledpin, OUTPUT);         // Precision mode active LED as output
  pinMode(precpin, INPUT_PULLUP);  // Precision button input with internal pull up
  Resetpins();                     // Make sure all simulated joystick switches are open to start
  ReadSens();                      // Read trimmer potentiometer on senspin line for analog value for deriving mouse mouse_sensitivity value
  digitalWrite(ledpin, LOW);       // Turn off LED indicating precision mode not active to start
}

//==================================[           Start Program Loop            ]================================
void loop()
{
  Usb.Task();                      // Start monitoring the USB mouse activity
  Enablepins();                    // Enable individual output pins to turn on optocoupler outputsOptocoupler ICs require a HIGH for CLOSED/ON
  delay(joy_delay);                // Control the speed in which the ADAM will be able to process mouse movements
  if (hold)                        // Center button toggles hold control and will slow the speed even further and
                                   // simulates holding the joystick down instead of regular short directional moves
  {
    delay(joy_holddelay);
  }
  Resetpins();                     // Make sure all simulated joystick switches are open - Optocoupler ICs require a LOW for OPEN/OFF
  ProcessButton();                 // Read precision mode button for activity
  ReadSens();                      // Read trimmer potentiometer on senspin line for analog value for fine tuning mouse mouse_sensitivity value

}
