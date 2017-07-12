#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Keyboard.h>
#include <Mouse.h>

RF24 radio(7,8);

const uint64_t adress = 0xF0F0F0F0E1LL;
int citiri,xval,yval,zval,xref=127,yref,zref;
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
    { if(((int)text)==1) {xref=xval;yref=yval;zref=zval;}
      else if(((int)text)==8) {if(apasat==false){Mouse.press();apasat=true;}}
      else if(((int)text)==4) {if(apasat==false){Mouse.click(MOUSE_RIGHT);apasat=true;}}
      else if(((int)text)==0) Mouse.release(),apasat=false;
    }
    else if(citiri==1)
    {
      xval=text;
    }
    else if(citiri==2)
    {
      yval=text;
    }
    else if(citiri==3)
    {
      zval=text;
      Mouse.move((xval-xref)/10,-(zval-127)/10,0);
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
