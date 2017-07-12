#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Keyboard.h>

RF24 radio(7,8);

const uint64_t adress = 0xF0F0F0F0E1LL;
int citiri;
bool apasat=false;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, adress);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Keyboard.begin();

}

void loop() {
  if(radio.available())
  {
    unsigned char text = "";
    radio.read(&text, sizeof(text));
    if(text==16)citiri=0,Serial.println("16 ");
    else
    {
    if(citiri==0)
    {
      if(((int)text)==8) {if(apasat==false){Keyboard.write(KEY_PAGE_DOWN);apasat=true;}}
      else if(((int)text)==4) {if(apasat==false){Keyboard.write(KEY_PAGE_UP);apasat=true;}}
      else if(((int)text)==0) apasat=false;
    }
    Serial.print((int)text);
    Serial.print(" ");
    citiri++;
  }
  
  if(citiri==4)
  {
    Serial.println();
    citiri=0;
  }
  }
}
