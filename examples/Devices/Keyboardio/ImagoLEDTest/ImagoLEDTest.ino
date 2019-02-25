#include<Wire.h>
#include<avr/pgmspace.h>
#include <Arduino.h>
#define Addr_GND 0x60
#define R 0x25 
#define G 0xC0
#define B 0xFF
uint8_t i,j;

const PROGMEM byte PWM_Gama64[64]=
{
  0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
  0x08,0x09,0x0b,0x0d,0x0f,0x11,0x13,0x16,
  0x1a,0x1c,0x1d,0x1f,0x22,0x25,0x28,0x2e,
  0x34,0x38,0x3c,0x40,0x44,0x48,0x4b,0x4f,
  0x55,0x5a,0x5f,0x64,0x69,0x6d,0x72,0x77,
  0x7d,0x80,0x88,0x8d,0x94,0x9a,0xa0,0xa7,
  0xac,0xb0,0xb9,0xbf,0xc6,0xcb,0xcf,0xd6,
  0xe1,0xe9,0xed,0xf1,0xf6,0xfa,0xfe,0xff
};

void setup() {
  digitalWrite(MOSI, HIGH);
  digitalWrite(SS, HIGH);
  Wire.begin();
//  Wire.setClock(400000);//I2C 1MHz
  //TWBR=2;
  Init_3741(R, G, B);
}

void IS31FL3741_Test_mode() {
  Init_3741(0xff, 0x00, 0x00);
IS31FL3741_Test_mode1();
  Init_3741(0x00, 0xff, 0x00);
IS31FL3741_Test_mode1();
  Init_3741(0x00, 0x00, 0xff);
IS31FL3741_Test_mode1();

 
 Init_3741(0x90, 0x90, 0x90);
IS31FL3741_Test_mode1();

}
void loop() {
   IS31FL3741_Test_mode();//breath mode
   delay(5);
}

void IS_IIC_WriteByte(uint8_t Dev_Add,uint8_t Reg_Add,uint8_t Reg_Dat)
{
  Wire.beginTransmission(Dev_Add/2); // transmit to device IS31FL373x
  Wire.write(Reg_Add); // sends regaddress
  Wire.write(Reg_Dat); // sends regaddress
  Wire.endTransmission(); // stop transmitting
}

void Init_3741(uint8_t Rdata, uint8_t Gdata, uint8_t Bdata)
{
  IS_IIC_WriteByte(Addr_GND,0xfe,0xc5);//unlock
  IS_IIC_WriteByte(Addr_GND,0xfD,0x02);//write page 2
  for(i=2;i<0xB4;i+=3)
  {
    IS_IIC_WriteByte(Addr_GND,i,Rdata);//R LED Scaling
  }
  for(i=1;i<0xB4;i+=3)
  {
    IS_IIC_WriteByte(Addr_GND,i,Gdata);//G LED Scaling
  }
  for(i=0;i<0xB4;i+=3)
  {
    IS_IIC_WriteByte(Addr_GND,i,Bdata);//B LED Scaling
  }
  IS_IIC_WriteByte(Addr_GND,0xfe,0xc5);//unlock
  IS_IIC_WriteByte(Addr_GND,0xfD,0x03);//write page 3
  for(i=2;i<0xAB;i+=3)
  {
    IS_IIC_WriteByte(Addr_GND,i,Rdata);//R LED Scaling
  }
  for(i=1;i<0xAB;i+=3)
  {
    IS_IIC_WriteByte(Addr_GND,i,Gdata);//G LED Scaling
  }
  for(i=0;i<0xAB;i+=3)
  {
    IS_IIC_WriteByte(Addr_GND,i,Bdata);//B LED Scaling
  }

  IS_IIC_WriteByte(Addr_GND,0xfe,0xc5);//unlock
  IS_IIC_WriteByte(Addr_GND,0xfD,0x00);//write page 0
  for(i=0;i<0xB4;i++)
  {
    IS_IIC_WriteByte(Addr_GND,i,0x00);//write all PWM set 0x00
  }
  IS_IIC_WriteByte(Addr_GND,0xfe,0xc5);//unlock
  IS_IIC_WriteByte(Addr_GND,0xfD,0x01);//write page 1
  for(i=0;i<0xAB;i++)
  {
    IS_IIC_WriteByte(Addr_GND,i,0x00);//write all PWM set 0x00
  } //init all the PWM data to 0
 
  IS_IIC_WriteByte(Addr_GND,0xfe,0xc5);//unlock
  IS_IIC_WriteByte(Addr_GND,0xfD,0x04);//write page 4
  IS_IIC_WriteByte(Addr_GND,0x01,0x7F);//global current
  IS_IIC_WriteByte(Addr_GND,0x00,0x01);//normal operation 
}

void IS31FL3741_Test_mode1(void)//
{
  IS_IIC_WriteByte(Addr_GND,0xFD,0x00);//write frist frame
  for (j=0;j<64;j++)//all LED ramping up
  { 
    IS_IIC_WriteByte(Addr_GND,0xfe,0xc5);//unlock
    IS_IIC_WriteByte(Addr_GND,0xfD,0x00);//write page 0
    for(i=0;i<0xB4;i++)
    {
      IS_IIC_WriteByte(Addr_GND,i,pgm_read_byte_near(&PWM_Gama64[j]));//set all PWM
    }
    IS_IIC_WriteByte(Addr_GND,0xfe,0xc5);//unlock
    IS_IIC_WriteByte(Addr_GND,0xfD,0x01);//write page 1
    for(i=0;i<0xAB;i++)
    {
      IS_IIC_WriteByte(Addr_GND,i,pgm_read_byte_near(&PWM_Gama64[j]));//set all PWM
    }
    delay(0);//10ms
  }
  delay(0); //keep on 1s
  
  for (j=63;j>0;j--)//all LED ramping down
  {
    IS_IIC_WriteByte(Addr_GND,0xfe,0xc5);//unlock
    IS_IIC_WriteByte(Addr_GND,0xfD,0x00);//write page 0
    for(i=0;i<0xB4;i++)
    {
      IS_IIC_WriteByte(Addr_GND,i,pgm_read_byte_near(&PWM_Gama64[j-1]));//set all PWM
    }
    IS_IIC_WriteByte(Addr_GND,0xfe,0xc5);//unlock
    IS_IIC_WriteByte(Addr_GND,0xfD,0x01);//write page 1
    for(i=0;i<0xAB;i++)
    {
      IS_IIC_WriteByte(Addr_GND,i,pgm_read_byte_near(&PWM_Gama64[j-1]));//set all PWM
    }
    delay(0);//10ms
  } 
  delay(0); //keep off 0.5s
}
  
