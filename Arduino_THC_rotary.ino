/*
 Project:  THC for Plasma CNC controller
 Platform: Arduino UNO R3
 Created:  April 2015
 Version:  02.00
 By:       Pham Duy Anh - phamduyanh@gmail.com
 
 Require:
  -> input
  <- output
  
  -> serial Tx
  -> serial Rx
  -> reset
  
  -> rotary encoder      digital - interrupt
  -> rotary encoder      digital - interrupt
  -> totary button       digital

  -> plasma Torch on     digital
  -> plasma Arc Ok       analog or digital)
  -> plasma arc voltage  analog 0-5V

  <- Arc Ok              optocoupler
  <- torch Up            optocoupler
  <- torch Down          optocuopler

  <- LCD
  <- LCD
  <- LCD
  <- LCD
  <- LCD
  <- LCD
*/

#define encoderPinA     2                 //PORTD 2 - INT0
#define encoderPinB     3                 //PORTD 3 - INT1
#define buttonPin       4                 //PORTD 4
#define outputOkPin     A5                //PORTC 5
#define outputUpPin     A4                //PORTC 4
#define outputDnPin     A3                //PORTC 3
#define inputNA         A2
#define arcVoltPin      A0                //PORTC 0

#define defaultLCDtime  500               // s * 100
/*
 Parameter
 * DT  - Delay time - Delay time of output closed despite no supply voltage, when the system detects the main (cutting) arc, 0.1~19.9s.
 * HyS - Hysreresis - The hysteresis voltage - a rangge in which the voltage is measured, in which ther are signals controlling Up/Down, (+-1V ~ +-15V)
 * StU - Started Voltage - Value of the off load voltage detection in the plasma cutter - uesd to detect the main (cutting) arc: 50~300V.
 * dTime
 * divRato
*/
#define _SetV 0
#define _DT   1
#define _HyS  2
#define _StV  3
int SetV, DT, HyS, StV;
//int divRato = 43 ;
int divRato = 51 ;
int ArcV;
int oldValue;

// Array of Param
//              SetV, DT, HYS, StV, divRato,
// Param Address   0,  1,   2,   3,       4,
int Param[5] = {SetV, DT, HyS, StV, divRato};
byte ParamItem = 5;

// Enable to do THC
boolean Do;
// Encoder, menu, pos
int encoderVal;
byte menu = 0;
byte pos  = 0;
byte show = 0;
unsigned int LCDtime = 0;

void setup()
{
  Setup_Encoder();
  Setup_LCD();
  Setup_THC();
  Setup_Timer2();
  //Read parameter from EEPROM
  ReadData();
  //Set value for all parameter
  SetV = Param[_SetV];
  DT   = Param[_DT];
  HyS  = Param[_HyS];
  StV  = Param[_StV];
  //Preset value for encoder
  encoderVal = SetV;
  Serial.begin(9600);
}

void loop()
{
  //Read voltage value from ADC
  ArcV = double(analogRead(arcVoltPin)) * double(100.00 / divRato);
  
  checkButton();
  checkMenu();
  doTHC();
  doLCD();

  //RS232();
}




  
