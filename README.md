# Arduino_Plasma_THC
THC (torch height controller) for Plasma CNC controller with Arduino UNO base 

### Hardware
  - Arduino UNO
  - 1602 text LCD
    * LCD RS pin to digital pin 13
    * LCD En pin to digital pin 12
    * LCD D4 pin to digital pin 11
    * LCD D5 pin to digital pin 10
    * LCD D6 pin to digital pin 09
    * LCD D7 pin to digital pin 08
    * LCD R/W pin to ground
  - Rotary button
    * encoderPinA     2 //PORTD 2 - INT0
    * encoderPinB     3 //PORTD 3 - INT1
    * buttonPin       4 //PORTD 4
  - I/O
    * outputOkPin     A5 //PORTC 5
    * outputUpPin     A4 //PORTC 4
    * outputDnPin     A3 //PORTC 3
    * arcVoltPin      A0 //PORTC 0
![Arduino THC](https://github.com/PhamDuyAnh/Arduino_Plasma_THC/blob/master/Arduino-THC.jpg)

![Arduino THC prototype](https://github.com/PhamDuyAnh/Arduino_Plasma_THC/blob/master/Arduino-THC-2.jpg)

![Arduino THC Voltage Devider](https://github.com/PhamDuyAnh/Arduino_Plasma_THC/blob/master/Arduino-THC-VD.jpg)

### Library
  - Used library
    * <LiquidCrystal.h>

### Parameter
  - DT  - Delay time - Delay time of output closed despite no supply voltage, when the system detects the main (cutting) arc, 0.1~19.9s.
  - HyS - Hysreresis - The hysteresis voltage - a rangge in which the voltage is measured, in which ther are signals controlling Up/Down, (+-1V ~ +-15V)
  - StU - Started Voltage - Value of the off load voltage detection in the plasma cutter - uesd to detect the main (cutting) arc: 50~300V.
  - dTime
  - divRato


### Source
<https://github.com/PhamDuyAnh/Arduino_Plasma_THC>.

### License GNU v3.0

### Author
  Phạm Duy Anh (CKD)
  http://cncprovn.com

### Donation
  Paypal: phamduyanh@gmail.com
  BTC: 168908e8-1d6f-4133-89b9-19a7914ad344
