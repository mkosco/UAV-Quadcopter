#include <SPI.h>
#include <RF24.h>
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
   * RF24_1MBPS:   1 megabit per second (default)
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
  
  radio.openWritingPipe(address); // set the address
  radio.stopListening(); // set as transmitter
  /* You can choose if acknowlegdements shall be requested (true = default) or not (false) */
  radio.setAutoAck(true);
 
  /* with this you are able to choose if an acknowledgement is requested for 
   * INDIVIDUAL messages.
   */
  radio.enableDynamicAck(); 
  /* setRetries(byte delay, byte count) sets the number of retries until the message is
   * successfully sent. 
   * Delay time = 250 µs + delay * 250 µs. Default delay = 5 => 1500 µs. Max delay = 15.
   * Count: number of retries. Default = Max = 15. 
   */
  radio.setRetries(5,15);
  /* The default payload size is 32. You can set a fixed payload size which must be the
   * same on both the transmitter (TX) and receiver (RX)side. Alternatively, you can use 
   * dynamic payloads, which need to be enabled on RX and TX. 
   */
  //radio.setPayloadSize(11);
  radio.enableDynamicPayloads();
}
void loop() {
  const char text[] = "Hi Receiver";
  Serial.println(sizeof(text));  
  if(radio.write(&text, sizeof(text)-1, 0)){ // 0: acknowledgement request, 1: no ack request
    Serial.println("Message successfully sent");
  }
  delay(2000);
}