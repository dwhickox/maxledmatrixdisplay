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
    Serial.println("seconds reset");
  }
  if (s >= 6){
    s = 0; 
    m1++;
    Serial.println("10 seconds reset");
  }
  if (m1 >= 10){
    m1 = 0;
    m++;
    Serial.println("minutes reset");
  }
  if (m >= 6){
    m = 0;
    h1++;
    Serial.println("10 minutes reset");
  }
  if ((ampm == 0 and h1 >= 10 and h < 2) or (ampm ==1 and h1 >= 10 and h < 1)){
    h1 = 0;
    h++;
    Serial.println("hours reset");
  }
  if (ampm == 0){
    if (h >= 2 and h1 >= 4){
      h = 0;
      h1 = 0;
    Serial.println("24 hour turn over reset");
    }
  }
  else{
    if (h >= 1 and h1 >= 4){
      h = 0;
      h1 = 0;
    Serial.println("12 hour turn over reset");
    }
  }
}
