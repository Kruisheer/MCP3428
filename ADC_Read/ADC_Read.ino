#include<Wire.h>

//If using all 8 chanels the second MCP chip is referrenced with the following
//#define Addr1 0x6E

unsigned Addr = 0x68;  // MCP3428 I2C address is 0x68 aka (104)
unsigned Addr_p1 = 0x10;
unsigned Addr_p2 = 0x30;
unsigned Addr_p3 = 0x50;
unsigned Addr_p4 = 0x70;

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  //Wire.beginTransmission(Addr);
  //Wire.write(0x62); //initialize?
}

void loop()
{
  quiryADCport(Addr, Addr_p1);
  quiryADCport(Addr, Addr_p2);
  quiryADCport(Addr, Addr_p3);
  quiryADCport(Addr, Addr_p4);
}


void quiryADCport(int Addr, int Port)
{
  unsigned int data[2];
  Wire.beginTransmission(Addr);
  // Select configuration command
  // Continuous conversion mode, Channel-1, 12-bit resolution
  //Channel 1 = 0x10, Channel 2 = 0x30, Channel 3 = 0x50, Channel 4 = 0x70
  Wire.write(Port);
  Wire.endTransmission();
  delay(100);
  
  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  Wire.requestFrom(Addr, 2);
    if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  // Convert the data to 12-bits
  int raw_adc = (data[0] & 0x0F) * 256 + data[1];
  if (raw_adc > 2047)
  {
    raw_adc -= 4096;
  }
  
  // Output data to serial monitor
  Serial.print("$BRS,");
  Serial.print("Addr: ,");
  Serial.print(Addr);
  Serial.print(" Port: ,");
  Serial.print(Port);
  Serial.print(" , 12bit Value: ,");
  //Serial.write(raw_adc);
  Serial.println(raw_adc);
  delay(100); 
}
