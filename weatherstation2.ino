// thermometer & hygromether with DHT sensor on TM1637 LED display by niq_ro from http://arduinotehniq.com/
// changed library from TM1637.h to TM1637Display.h

#include <TM1637Display.h>  // library from https://github.com/avishorp/TM1637

#include <DHT.h> 
#define DHTPIN D7     // what pin we're connected the DHT output
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22 
DHT dht(DHTPIN, DHTTYPE); 
 
#define CLK 12 // GPIO12 = D6                       // Define the connections pins:
#define DIO 14 // GPIO14 = D5
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
 dht.begin();   
 
}//end "setup()"
 
 
void loop(){   //Start of Program 

   int humidity = dht.readHumidity();
   int temp = dht.readTemperature();  

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
