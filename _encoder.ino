//Encoder Interrupt time require <2us
boolean A, B, lastA, lastB;
boolean ButtonOk, ButtonStat, lastButtonStat;

void Setup_Encoder()
{
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(buttonPin,   INPUT);
  attachInterrupt(0, doEncoder, CHANGE);
}


//attachInterrupt(0, doEncoder, CHANGE);
//2x Quadrature Encoder
/*
void doEncoder()
{
  A = bitRead(PIND, 2);
  B = bitRead(PIND, 3);

  if ((A != lastA) & (B != lastB))
  {
    if (A ^ B) Vset ++;
    else       Vset --;
  }
  lastA = A;
  lastB = B;
}
*/

//attachInterrupt(0, doEncoder, CHANGE);
//1x Quadrature Encoder
void doEncoder()
{
  A = bitRead(PIND, 2);
  B = bitRead(PIND, 3);

  if ((A != lastA) & (B != lastB))
  {
    if (A)
      if (A = B) encoderVal ++;
      else       encoderVal --;
    LCDtime = 0;
  }
  lastA = A;
  lastB = B;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// Button
void checkButton()
{
  ButtonStat = bitRead(PIND, 4);
  if (ButtonStat != lastButtonStat)
  {
    if (!ButtonStat) ButtonOk = true;
    lastButtonStat = ButtonStat;
  }
}

void checkMenu()
{
  if (ButtonOk)
  {
    Serial.print(menu);
    Serial.println("   Button");
    
    ButtonOk = false;
    LCDtime = 0;
    
    if (menu == 0) menu = 1;
    else if (menu == 1)
    {
      if (pos == 0)      menu = 0;
      else if (pos == 1) menu = 11;
      else if (pos == 2) menu = 12;
    }
    else if (menu == 11)
    {
      if (pos == 0) menu = 1;
      else if (pos == 1) menu = 111;
      else if (pos == 2) menu = 112;
      else if (pos == 3) menu = 113;
      else if (pos == 4) menu = 114;
    }
    else if (menu == 111) menu = 11;
    else if (menu == 112) menu = 11;
    else if (menu == 113) menu = 11;
    else if (menu == 12)
    {
      menu = 1;
    }
    if (menu == 0)        encoderVal = SetV;
    else if (menu == 111) encoderVal = DT;
    else if (menu == 112) encoderVal = HyS;
    else if (menu == 113) encoderVal = StV;
    else                  encoderVal = 0;
  }
}
