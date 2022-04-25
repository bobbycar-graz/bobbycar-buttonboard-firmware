#include <ezButton.h>

#include <Arduino.h>
#include <eXoCAN.h>

#define BTN1 PB4
#define BTN2 PB3
#define BTN3 PA15
#define BTN4 PB12
#define BTN5 PB11
#define BTN6 PB10

#define MDBT1 PB7
#define MDBT2 PA8
#define MDBT3 PB13
#define MDBT4 PB0

#define MDLED4 PB6
#define MDLED3 PB15
#define MDLED2 PB14
#define MDLED1 PB1


int txMsgID = 0x100;
int rxMsgID = 0x180;
uint8_t txData[1]{0x00};
uint8_t txDataLen = 1;
uint32_t txDly = 5000; // mSec


int id, fltIdx;
uint8_t rxbytes[8];
eXoCAN can;


ezButton ModeButton1(MDBT1);
ezButton ModeButton2(MDBT2);
ezButton ModeButton3(MDBT3);
ezButton ModeButton4(MDBT4);

ezButton Button1(BTN1);
ezButton Button2(BTN2);
ezButton Button3(BTN3);
ezButton Button4(BTN4);
ezButton Button5(BTN5);
ezButton Button6(BTN6);


void setup()
{
  can.begin(STD_ID_LEN, BR250K, PORTA_11_12_WIRE_PULLUP); // 11b IDs, 250k bit rate, no transceiver chip, portA pins 11,12
  can.filterMask16Init(0, 0, 0x7ff, 0, 0);                // filter bank 0, filter 0: don't pass any, flt 1: pass all msgs

  pinMode(MDLED1, OUTPUT);
  pinMode(MDLED2, OUTPUT);
  pinMode(MDLED3, OUTPUT);
  pinMode(MDLED4, OUTPUT);

  ModeButton1.setDebounceTime(50); // set debounce time to 50 milliseconds
  ModeButton2.setDebounceTime(50); // set debounce time to 50 milliseconds
  ModeButton3.setDebounceTime(50); // set debounce time to 50 milliseconds
  ModeButton4.setDebounceTime(50); // set debounce time to 50 milliseconds


  Button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  Button2.setDebounceTime(50); // set debounce time to 50 milliseconds
  Button3.setDebounceTime(50); // set debounce time to 50 milliseconds
  Button4.setDebounceTime(50); // set debounce time to 50 milliseconds
  Button5.setDebounceTime(50); // set debounce time to 50 milliseconds
  Button6.setDebounceTime(50); // set debounce time to 50 milliseconds
}


void signal_can(uint8_t button_number, bool on_off)
{

  txData[0] = button_number;
  txMsgID = 0x100|on_off;
    
  can.transmit(txMsgID, txData, txDataLen);
  
}

uint32_t last = 0;
void loop()
{

  ModeButton1.loop(); // MUST call the loop() function first
  ModeButton2.loop(); // MUST call the loop() function first
  ModeButton3.loop(); // MUST call the loop() function first
  ModeButton4.loop(); // MUST call the loop() function first
  
  Button1.loop(); // MUST call the loop() function first
  Button2.loop(); // MUST call the loop() function first
  Button3.loop(); // MUST call the loop() function first
  Button4.loop(); // MUST call the loop() function first
  Button5.loop(); // MUST call the loop() function first
  Button6.loop(); // MUST call the loop() function first


  if(Button1.isPressed())
    signal_can(1,1);
    
  if(Button1.isReleased())
    signal_can(1,0);

  if(Button2.isPressed())
    signal_can(2,1);
    
  if(Button2.isReleased())
    signal_can(2,0);

  if(Button3.isPressed())
    signal_can(3,1);
    
  if(Button3.isReleased())
    signal_can(3,0);

  if(Button4.isPressed())
    signal_can(4,1);
    
  if(Button4.isReleased())
    signal_can(4,0);

  if(Button5.isPressed())
    signal_can(5,1);
    
  if(Button5.isReleased())
    signal_can(5,0);

  if(Button6.isPressed())
    signal_can(6,1);
    
  if(Button6.isReleased())
    signal_can(6,0);
  

  if(ModeButton1.isPressed())
    signal_can(10,1);
   
  if(ModeButton1.isReleased())
    signal_can(10,0);

  if(ModeButton2.isPressed())
    signal_can(11,1);
   
  if(ModeButton2.isReleased())
    signal_can(11,0);

  if(ModeButton3.isPressed())
    signal_can(12,1);
   
  if(ModeButton3.isReleased())
    signal_can(12,0);

  if(ModeButton4.isPressed())
    signal_can(13,1);
   
  if(ModeButton4.isReleased())
    signal_can(13,0);



  if (can.receive(id, fltIdx, rxbytes) > -1) // poll for rx
  {
    if (id == rxMsgID)
    {
      digitalWrite(MDLED1, rxbytes[0] & 0x01);
      digitalWrite(MDLED2, rxbytes[0] & 0x02);
      digitalWrite(MDLED3, rxbytes[0] & 0x04);
      digitalWrite(MDLED4, rxbytes[0] & 0x08);
    }
  }

}
