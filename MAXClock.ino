#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>


int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 4;//adjust this to your setup
int numberOfVerticalDisplays = 1;
int ampm = 0; // if you want it to run 24 hour set to 0 if you want 12 hour set to 1
int h;
int h1;
int m;
int m1;
int s;
int s1;
int curs = 0;
String msg;
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {
  Serial.begin(57600);
  matrix.setIntensity(4); // Set brightness between 0 and 15

  matrix.setRotation(0, 1);//you may have to change this section depending on your LED matrix setup
  matrix.setRotation(1,1);
  matrix.setRotation(2,1);
  matrix.setRotation(3,1);
  matrix.setTextSize(1);
  matrix.setTextWrap(false); 
  matrix.setTextColor(HIGH);
  Serial.println("made it through setup");
}

void loop() {
  if (Serial.available() > 5)
  {
      Serial.println("serial was deamed avialable");
      h = Serial.parseInt();
      Serial.println(h);
      h1 = Serial.parseInt();
      Serial.println(h1);
      m = Serial.parseInt();
      Serial.println(m);
      m1 = Serial.parseInt();
      Serial.println(m1);
      s = Serial.parseInt();
      Serial.println(s);
      s1 = Serial.parseInt();
      Serial.println(s1);
  }
  
  matrix.fillScreen(LOW);//Empty the screen
  matrix.setCursor(curs,0);//Move the cursor to the end of the screen
  msg = "";
  msg.concat(h);
  msg.concat(h1);
  msg.concat(":");
  msg.concat(m);
  msg.concat(m1);
  matrix.print(msg);
  msg.concat(":");
  msg.concat(s);
  msg.concat(s1);
  Serial.println(msg);
  matrix.write();
  delay(1000);
  s1++;
  if (s1 >= 10){
    s1 = 0;
    s++;
  }
  if (s >= 6){
    s = 0; 
    m1++;
  }
  if (m1 >= 10){
    m1 == 0;
    m++;
  }
  if (m >= 6){
    m = 0;
    h1++;
  }
  if (h1 >= 10){
    h1 = 0;
    h++;
  }
  if (ampm == 0){
    if (h >= 2 and h1 >= 4){
      h = 0;
      h1 = 0;
    }
  }
  else{
    if (h >= 1 and h1 >= 2){
      h = 0;
      h1 = 0;
    }
  }
}
