// thermometer & hygromether with DHT sensor on TM1637 LED display by niq_ro from http://arduinotehniq.com/
// ver.2.0 - changed library from TM1637.h to TM1637Display.h
// ver.2.1 - changed library from DHT.h to DHTesp.h

#include <TM1637Display.h>  // library from https://github.com/avishorp/TM1637

#include "DHTesp.h" // Click here to get the library: http://librarymanager/All#DHTesp
DHTesp dht;

#define DHTPIN D7 // GPIO13 = D7    // what pin we're connected the DHT output
/*
#include <DHT.h> 
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22 
DHT dht(DHTPIN, DHTTYPE); 
*/

#define CLK D6 // GPIO12 = D6                       // Define the connections pins:
#define DIO D5 // GPIO14 = D5
// Definitions using https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/ 
 
//TM1637 tm1637(CLK,DIO);
TM1637Display display(CLK, DIO);

uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
uint8_t codare[] = {
  0b00111111,    // 0
  0b00000110,    // 1
  0b01011011,    // 2
  0b01001111,    // 3
  0b01100110,    // 4
  0b01101101,    // 5
  0b01111101,    // 6
  0b00000111,    // 7
  0b01111111,    // 8
  0b01101111,    // 9
  };
 
void setup(){
  
display.setBrightness(0x01);  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  
 delay(1500);//Delay to let system boot
// dht.begin();   // used in DHT.h library

 // Autodetect is not working reliable, don't use the following line
  // dht.setup(17);
  // use this instead: 
  dht.setup(DHTPIN, DHTesp::DHT22); // Connect DHT sensor to GPIO 17

 
}//end "setup()"
 
 
void loop(){   //Start of Program 
/*
   int humidity = dht.readHumidity();
   int temp = dht.readTemperature();  
*/
  int humidity = dht.getHumidity();
  int temp = dht.getTemperature();


//   int temp = 23;
//   int humidity = 48;
 
 int digitoneT = temp / 10;
 int digittwoT = temp % 10;
 
 int digitoneH = humidity / 10;
 int digittwoH = humidity % 10;
  
data[0] = codare[digitoneT];
data[1] = codare[digittwoT];
data[2] = 0x63; // degree symbol
data[3] = 0x39; // C
display.setSegments(data);   
    
delay (3000);
display.clear();

data[0] = codare[digitoneH];
data[1] = codare[digittwoH];
data[2] = 0x63; // degree symbol
data[3] = 0x5C; // o
display.setSegments(data); 

delay(3000);
display.clear();
}// end loop() 
