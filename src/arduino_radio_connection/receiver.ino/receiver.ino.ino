#include <SPI.h>
#include "RF24.h"
RF24 radio(7, 8); // (CE, CSN)
const byte address[6] = "1RF24"; // address / identifier
void setup() {
  Serial.begin(115200);
  if(!radio.begin()){
    Serial.println("nRF24L01 module not connected!");
    while(1){}
  }
  else 
    Serial.println("nRF24L01 module connected!");
  /* Set the data rate:
   * RF24_250KBPS: 250 kbit per second
   * RF24_1MBPS:   1 megabit per second
   * RF24_2MBPS:   2 megabit per second
   */
  radio.setDataRate(RF24_2MBPS);
  /* Set the power amplifier level rate:
   * RF24_PA_MIN:   -18 dBm
   * RF24_PA_LOW:   -12 dBm
   * RF24_PA_HIGH:   -6 dBm
   * RF24_PA_MAX:     0 dBm (default)
   */
  radio.setPALevel(RF24_PA_LOW); // sufficient for tests side by side 
   
   /* Set the channel x with x = 0...125 => 2400 MHz + x MHz 
   * Default: 76 => Frequency = 2476 MHz
   * use getChannel to query the channel
   */
  radio.setChannel(0);
  
  radio.openReadingPipe(0,address); // set the address
  radio.startListening(); // set as receiver
  /* The default payload size is 32. You can set a fixed payload size which 
   * must be the same on both the transmitter (TX) and receiver (RX)side. 
   * Alternatively, you can use dynamic payloads, which need to be enabled 
   * on RX and TX. 
   */
  //radio.setPayloadSize(11);
  radio.enableDynamicPayloads();
}
void loop() {
  if(radio.available()){
    byte len = radio.getDynamicPayloadSize();
    Serial.println(len); //just for information
    char text[len+1] = {0}; 
    radio.read(&text, len);
    Serial.println(text);
  }
}