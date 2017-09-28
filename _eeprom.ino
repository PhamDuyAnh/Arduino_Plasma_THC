#include <EEPROM.h>
void Default()
{
  SetV = 100;
  DT   = 5;
  HyS  = 10;
  StV  = 100;
  EEPROM.write(_SetV, SetV);
  EEPROM.write(_DT  ,   DT);
  EEPROM.write(_HyS ,  HyS);
  EEPROM.write(_StV ,  StV);
}

void ReadData()
{
  //              SetV, HYS, DT, HU, sTs, dTime,
  // Param Address   0,   1,  2,  3,   4,     5,
  for (int j = 0; j < ParamItem; j++)
  {
    Param[j] = EEPROM.read(j);
  }
}

void SaveData(int add, int value)
{
  EEPROM.write(add, value);
}
