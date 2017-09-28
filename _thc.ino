unsigned int delayTime;
unsigned int SetVx10;

void Setup_THC()
{
  pinMode(outputUpPin, OUTPUT);
  pinMode(outputOkPin, OUTPUT);
  pinMode(outputDnPin, OUTPUT);
  pinMode(13, OUTPUT); // CKD test signal.
}

void doTHC()
{
  if (Do)
  {
    Do = false;
    LCDtime ++;
    show ++;
    // CKD test signal.
    bitWrite(PORTB, 5, !bitRead(PORTB, 5));
 
    if (LCDtime > defaultLCDtime)
    {
      menu = 0;
      pos  = 0;
      LCDtime = 0;
      encoderVal = SetV;
    }
    if ((500 < ArcV) & (ArcV < 2500))
    {
      if (ArcV > StV * 10) delayTime ++;
      
      if (delayTime >= DT * 10)
      {
        SetVx10 = SetV * 10;
        delayTime = DT * 10;
        
        bitWrite(PORTC, 5, 1);
        
        if (ArcV >= SetVx10 + HyS)
        {
          bitWrite(PORTC, 4, 0);
          bitWrite(PORTC, 3, 1);
        }
        else if (ArcV <= SetVx10 - HyS)
        {
          bitWrite(PORTC, 4, 1);
          bitWrite(PORTC, 3, 0);
        }
        else
        {
          bitWrite(PORTC, 4, 0);
          bitWrite(PORTC, 3, 0);
        }       
      }
    }
    else if (menu != 12)
    {
      delayTime = 0;
      bitWrite(PORTC, 4, 0);
      bitWrite(PORTC, 5, 0);
      bitWrite(PORTC, 3, 0);
    }
  }
}

void RS232()
{
  Serial.print("SetV:");
  Serial.print(SetVx10);
  Serial.print(" ArcV:");
  Serial.print(ArcV);
  Serial.print(" StV:");
  Serial.print(StV);
  Serial.print(" DTime:");
  Serial.print(delayTime);
  Serial.println("");
}
