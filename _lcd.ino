/*
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you  can usually tell them by the 16-pin interface.
 The circuit:
 * LCD RS pin to digital pin 13
 * LCD En pin to digital pin 12
 * LCD D4 pin to digital pin 11
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 09
 * LCD D7 pin to digital pin 08
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
//                RS  EN  D4  D5 D6 D7
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
// make some custom characters
byte armsUpDn[8] = {
  0b00000,
  0b00100,
  0b01110,
  0b00100,
  0b00000,
  0b01110,
  0b00000,
  0b00000
};

void Setup_LCD()
{
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // create a new character
  lcd.createChar(1, armsUpDn);  
  // startup LOGO  
  lcd.setCursor(4,0);
  lcd.print("CNCProVN");
  lcd.setCursor(3,1);
  lcd.print("Plasma THC");
  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("www.cncprovn.com");
  lcd.setCursor(5,1);
  lcd.print("v:02.0");
  delay(100);
  lcd.clear();
}

void doLCD()
{
  if (show >= 2)
  {
    show = 0;
    switch (menu)
    {
      case 0:
        doLCDDefault();
        break;
      case 1:
        doLCDMenu();
        break;
      case 11:
        doLCDMenuSetup();
        break;
      case 111:
        doLCDDelayTime();
        break;
      case 112:
        doLCDHysreresis();
        break;
      case 113:
        doLCDStartVoltage();
        break;
      case 114:
        doLCDLoadDefault();
        break;
      case 12:
        doLCDTest();
        break;
      default:
        doLCDDefault();
    }
  }  
}

void doLCDDefault()
{
  if (encoderVal < 0)        encoderVal = 0;
  else if (encoderVal > 250) encoderVal = 250;
  SetV = encoderVal;
  if (SetV != oldValue)
  {
    SaveData(_SetV, SetV);
    oldValue = SetV;
  }
  lcd.setCursor(0,0);
  lcd.print("SetV: ");
  lcd.print(SetV);
  lcd.print("         ");
  lcd.setCursor(0,1);
  lcd.print("ArcV: ");
  lcd.print(ArcV / 10);
  lcd.print("         ");  
}
//Main menu
void doLCDMenu()
{
  if (encoderVal < 0) encoderVal = 2;
  pos = encoderVal % 3;
  switch (pos)
  {
    case 0:
      lcd.setCursor(0,0);
      lcd.print("> Exit          ");
      lcd.setCursor(0,1);
      lcd.print("  Setup         ");
      break;
    case 1:
      lcd.setCursor(0,0);
      lcd.print("> Setup         ");
      lcd.setCursor(0,1);
      lcd.print("  Test          ");
      break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("> Test          ");
      lcd.setCursor(0,1);
      lcd.print("  Exit          ");
      break;
  }
}
// Setup
void doLCDMenuSetup()
{
  if (encoderVal < 0) encoderVal = 4;
  pos = abs(encoderVal % 5);
  switch (pos)
  {
    case 0:
      lcd.setCursor(0,0);
      lcd.print(">> Exit         ");
      lcd.setCursor(0,1);
      lcd.print("   Delay Time   ");
      break;
    case 1:
      lcd.setCursor(0,0);
      lcd.print(">> Delay Time   ");
      lcd.setCursor(0,1);
      lcd.print("   Hysreresis   ");
      break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print(">> Hysreresis   ");
      lcd.setCursor(0,1);
      lcd.print("   Start Voltage");
      break;
    case 3:
      lcd.setCursor(0,0);
      lcd.print(">> Start Voltage");
      lcd.setCursor(0,1);
      lcd.print("   Load Default ");
      break;
    case 4:
      lcd.setCursor(0,0);
      lcd.print(">> Load Default ");
      lcd.setCursor(0,1);
      lcd.print("   Exit         ");
      break;
  }
}
// Test
void doLCDTest()
{
  if (encoderVal < 0) encoderVal = 2;
  pos = abs(encoderVal % 3);
  switch (pos)
  {
    case 0:
      lcd.setCursor(0,0);
      lcd.print("Test > Exit     ");
      lcd.setCursor(0,1);
      lcd.print("       Torch Up ");
      bitWrite(PORTC, 3, 0);
      bitWrite(PORTC, 4, 0);
      bitWrite(PORTC, 5, 0);
      break;
    case 1:
      lcd.setCursor(0,0);
      lcd.print("Test > Torch Up ");
      lcd.setCursor(0,1);
      lcd.print("       Torch Dn ");
      bitWrite(PORTC, 3, 0);
      bitWrite(PORTC, 4, 1);
      bitWrite(PORTC, 5, 1);
      break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("Test > Torch Dn ");
      lcd.setCursor(0,1);
      lcd.print("       Exit     ");
      bitWrite(PORTC, 3, 1);
      bitWrite(PORTC, 4, 0);
      bitWrite(PORTC, 5, 1);
      break;
  }
}
void doLCDDelayTime()
{
  if (encoderVal < 1)        encoderVal = 1;
  else if (encoderVal > 200) encoderVal = 200;
  
  DT = encoderVal;
  if (DT != oldValue)
  {
    SaveData(_DT, DT);
    oldValue = DT;
    LCDtime = 0;
  }
  
  double x = DT / 10.00;
  lcd.setCursor(0,0);
  lcd.print("Set > Delay Time");
  lcd.setCursor(0,1);
  lcd.print("     : ");
  lcd.print(x, 1);
  lcd.print(" s       ");
}
void doLCDHysreresis()
{
  if (encoderVal < 1)        encoderVal = 1;
  else if (encoderVal > 99) encoderVal = 99;

  HyS = encoderVal;
  if (HyS != oldValue)
  {
    SaveData(_HyS, HyS);
    oldValue = HyS;
    LCDtime = 0;
  }
  
  double x = HyS / 10.00;
  lcd.setCursor(0,0);
  lcd.print("Set > Hysreresis");
  lcd.setCursor(0,1);
  lcd.print("     :");
  lcd.write(1);
  lcd.print(x, 1);
  lcd.print(" V       ");
}
void doLCDStartVoltage()
{
  if (encoderVal < 50)        encoderVal = 50;
  else if (encoderVal > 250) encoderVal = 250;

  StV = encoderVal;
  if (StV != oldValue)
  {
    SaveData(_StV, StV);
    oldValue = StV;
    LCDtime = 0;
  }
  
  lcd.setCursor(0,0);
  lcd.print("Set > Start Volt");
  lcd.setCursor(0,1);
  lcd.print("     : ");
  lcd.print(StV);
  lcd.print(" V       ");
}
void doLCDLoadDefault()
{
  Default();

  for (byte i = 0; i < 100; i++)
  {
    lcd.setCursor(0,0);
    lcd.print("     Default    ");
    lcd.setCursor(0,1);
    lcd.print("Load   ");
    lcd.print(i);
    lcd.print(" ");
    lcd.print("%");
    lcd.print("        ");
    delay(10);
  }
  lcd.setCursor(0,1);
  lcd.print("      DONE      ");
  delay(1000);
  menu = 11;
}
