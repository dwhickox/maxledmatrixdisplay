#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>


int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 4;//adjust this to your setup
int numberOfVerticalDisplays = 1;
String letter = "test";
int curs = 0;
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
  if (Serial.available() > 0)
  {
      Serial.println("serial was deamed avialable for letter");
      letter = Serial.readString();
      Serial.println(letter);
  }
  
  matrix.fillScreen(LOW);//Empty the screen
  matrix.setCursor(curs,0);//Move the cursor to the end of the screen
  curs ++;
  if (curs == 31) {
    curs = -letter.length()*5;
  }
    
  matrix.print(letter);
  matrix.write();
  delay(30);
  
}
