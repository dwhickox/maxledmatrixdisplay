/*copyright David Hickox
   set the clock with ab hours cd min and ef seconds in the format "a,b,c,d,e,f" in the serial console
   Requirements to run, adafruit gfx and Max72xxPanel by markruys https://github.com/markruys/arduino-Max72xxPanel


   variables for you to mess with:
   pinCS, set this to what digital pin you want to connect CS (on the matrix input) to
   numHorizDisp, set how many 8*8 max matricies you have horizontaly
   numVertDisp, set how many 8*8 max matricies you have verticaly
   ampm, change this from 0 to 1 if you want 12 hour time instead of 24
   txtsz, this is the text size, mess with this if you have more pannels or are just curious
   rot, (0-3) rotates your display oreintation depending on how you have it set up, the default and most common is 1
   interval, i guess if you wanted to use this as a metrinome or something you could change the lenght of the second with this
   marquee, if you wish to have the text scroll like a movie theater marquee, set this to 1 if not set it to 0 (an added benifit of this is that it will display the seconds as well
   interval1, change how fast the marquee scrolls, the larger the number the slower (millis delay)
*/


#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>


int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numHorizDisp = 4;//adjust this to your setup
int numVertDisp = 1;
int ampm = 0; // if you want it to run 24 hour set to 0 if you want 12 hour set to 1
int txtsz = 1;
int rot = 1;
int marquee = 1;//1 marquee enabled, 0 disabled
int h;
int h1;
int m;
int m1;
int s;
int s1;
int curs = 0;
int interval = 1000;
int interval1 = 80;
int debug;
int i;
String msg;
String sermsg;
unsigned long prevMil = 0;
unsigned long prevMil1 = 0;

Max72xxPanel matrix = Max72xxPanel(pinCS, numHorizDisp, numVertDisp);

void setup() {
  Serial.begin(57600);
  matrix.setIntensity(3); // Set brightness between 0 and 15

  matrix.setRotation(0, rot); //you may have to change this section depending on your LED matrix setup
  matrix.setRotation(1, rot);
  matrix.setRotation(2, rot);
  matrix.setRotation(3, rot);
  matrix.setTextSize(txtsz);
  matrix.setTextWrap(false);
  matrix.setTextColor(HIGH);
  Serial.println("made it through setup");
}

void loop() {
  unsigned long curMil = millis();
  unsigned long curMil1 = millis();
  if ((unsigned long)(curMil - prevMil) >= interval) {
    if ((unsigned long)(curMil - prevMil) > interval) {
      debug = debug + ((curMil - prevMil) - interval);
      i++;
      if (i == 10) {
        Serial.println(debug);
        i = 0;
      }
    }
    if (Serial.available() > 5) // set the clock with ab hours cd min and ef seconds in the format "a,b,c,d,e,f" in the serial console
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
    msg = "";
    msg.concat(h);
    msg.concat(h1);
    msg.concat(":");
    msg.concat(m);
    msg.concat(m1);
    sermsg = msg;
    sermsg.concat(":");
    sermsg.concat(s);
    sermsg.concat(s1);
    Serial.println(sermsg);
    if (marquee == 1) {
      msg.concat(":");
      msg.concat(s);
      msg.concat(s1);
    }
    s1++;
  if (s1 >= 10) {
      s1 = 0;
      s++;
      Serial.println("seconds reset");
    }
    if (s >= 6) {
      s = 0;
      m1++;
      Serial.println("10 seconds reset");
    }
    if (m1 >= 10) {
      m1 = 0;
      m++;
      Serial.println("minutes reset");
    }
    if (m >= 6) {
      m = 0;
      h1++;
      Serial.println("10 minutes reset");
    }
    if ((ampm == 0 and h1 >= 10 and h < 2) or (ampm == 1 and h1 >= 10 and h < 1)) {
      h1 = 0;
      h++;
      Serial.println("hours reset");
    }
    if (ampm == 0) {
      if (h >= 2 and h1 >= 4) {
        h = 0;
        h1 = 0;
        Serial.println("24 hour turn over reset");
      }
    }
    else {
      if (h >= 1 and h1 >= 4) {
        h = 0;
        h1 = 0;
        Serial.println("12 hour turn over reset");
      }
    }
    prevMil = curMil;
  }

  if (marquee == 1) {
    if ((unsigned long)(curMil1 - prevMil1) >= interval1) {
      curs --;
      if (curs == -msg.length() * 6) {
        curs = 34;
      }
      prevMil1 = curMil1;
    }
  }
  matrix.fillScreen(LOW);//Empty the screen
  matrix.setCursor(curs, 0); //Move the cursor to the end of the screen
  matrix.print(msg);
  matrix.write();
}
