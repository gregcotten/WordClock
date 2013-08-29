#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Time.h> 

#define PIN 6

enum page {
  CLOCK,
  SET_BRIGHTNESS,
  SET_COLOR,
  SET_CLOCK
};

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(11, 10, PIN,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

elapsedMillis sinceLastTimeCheck;
page currentPage = CLOCK;
int GMT = -7;
  
void setup() {
  Serial.begin(115200);
  
  matrix.begin();
  //matrix.setTextWrap(false);
  matrix.setBrightness(100);

  setSyncProvider(getTeensy3Time);
  //matrix.setTextColor(colors[0]);
}

void loop() {
  doSerialDuties();
  //blank the screen!
  if (sinceLastTimeCheck > 1000 && currentPage == CLOCK){
    sinceLastTimeCheck = 0;
    matrix.fillScreen(0);
    printTimeToMatrix(matrix.Color(255,50,255));
    matrix.show();
    //digitalClockDisplay();
  }
  
}

void printTimeToMatrix(uint16_t color){
  int currentHour = (hour() + GMT)%24;
  int currentMinute = minute();

  if(currentHour > 20 || currentHour < 8){
    matrix.setBrightness(50);
  }
  else{
    matrix.setBrightness(100);
  }

  //IT IS
  for (int i = 0; i <= 1; i++){
    matrix.drawPixel(i, 0, color);
  }
  for (int i = 3; i <= 4; i++){
    matrix.drawPixel(i, 0, color);
  }

  if (currentMinute < 5){
    //O'CLOCK
    for (int i = 5; i <= 10; i++){
      matrix.drawPixel(i, 9, color);
    }
    hourPast(currentHour, color);
  }
  else if (currentMinute < 35){
    //X PAST
    for (int i = 0; i <= 3; i++){
    matrix.drawPixel(i, 4, color);
    }
    hourPast(currentHour, color);
  }
  else if (currentMinute >= 35){
    //X TO
    for (int i = 9; i <= 10; i++){
    matrix.drawPixel(i, 3, color);
    }
    hourTo(currentHour, color);
  }

  //MINUTES
  if ( (currentMinute >= 5 && currentMinute < 10) || (currentMinute >= 55 && currentMinute < 60) ){
    for (int i = 6; i <= 9; i++){
      matrix.drawPixel(i, 2, color);
    }
  }
  else if ( (currentMinute >= 10 && currentMinute < 15) || (currentMinute >= 50 && currentMinute < 55) ){
    for (int i = 5; i <= 7; i++){
      matrix.drawPixel(i, 3, color);
    }
  }
  else if ( (currentMinute >= 15 && currentMinute < 20) || (currentMinute >= 45 && currentMinute < 50) ){
    matrix.drawPixel(0, 1, color);
    for (int i = 2; i <= 8; i++){
      matrix.drawPixel(i, 1, color);
    }
  }
  else if ( (currentMinute >= 20 && currentMinute < 25) || (currentMinute >= 40 && currentMinute < 45) ){
    for (int i = 0; i <= 5; i++){
      matrix.drawPixel(i, 2, color);
    }
  }
  else if ( (currentMinute >= 25 && currentMinute < 30) || (currentMinute >= 35 && currentMinute < 40) ){
    for (int i = 0; i <= 9; i++){
      matrix.drawPixel(i, 2, color);
    }
  }
  else if ( (currentMinute >= 30 && currentMinute < 35)){
    for (int i = 0; i <= 3; i++){
      matrix.drawPixel(i, 3, color);
    }
  }
}

void hourPast(int currentHour, uint16_t color){
  switch (currentHour){
    case 0: case 12: for (int i = 5; i <= 10; i++){
            matrix.drawPixel(i, 8, color);
            }
            break;
    case 1: case 13: for (int i = 0; i <= 2; i++){
            matrix.drawPixel(i, 5, color);
            }
            break;
    case 2: case 14: for (int i = 8; i <= 10; i++){
            matrix.drawPixel(i, 6, color);
            }
            break;
    case 3: case 15: for (int i = 6; i <= 10; i++){
            matrix.drawPixel(i, 5, color);
            }
            break;
    case 4: case 16: for (int i = 0; i <= 3; i++){
            matrix.drawPixel(i, 6, color);
            }
            break;
    case 5: case 17: for (int i = 4; i <= 7; i++){
            matrix.drawPixel(i, 6, color);
            }
            break;
    case 6: case 18: for (int i = 3; i <= 5; i++){
            matrix.drawPixel(i, 5, color);
            }
            break;
    case 7: case 19: for (int i = 0; i <= 4; i++){
            matrix.drawPixel(i, 8, color);
            }
            break;
    case 8: case 20: for (int i = 0; i <= 4; i++){
            matrix.drawPixel(i, 7, color);
            }
            break;
    case 9: case 21: for (int i = 7; i <= 10; i++){
            matrix.drawPixel(i, 4, color);
            }
            break;
    case 10: case 22: for (int i = 0; i <= 2; i++){
            matrix.drawPixel(i, 9, color);
            }
            break;
    case 11: case 23: for (int i = 5; i <= 10; i++){
            matrix.drawPixel(i, 7, color);
            }
            break;
  }
}

void hourTo(int currentHour, uint16_t color){
  switch (currentHour){
    case 11: case 23: for (int i = 5; i <= 10; i++){
            matrix.drawPixel(i, 8, color);
            }
            break;
    case 0: case 12: for (int i = 0; i <= 2; i++){
            matrix.drawPixel(i, 5, color);
            }
            break;
    case 1: case 13: for (int i = 8; i <= 10; i++){
            matrix.drawPixel(i, 6, color);
            }
            break;
    case 2: case 14: for (int i = 6; i <= 10; i++){
            matrix.drawPixel(i, 5, color);
            }
            break;
    case 3: case 15: for (int i = 0; i <= 3; i++){
            matrix.drawPixel(i, 6, color);
            }
            break;
    case 4: case 16: for (int i = 4; i <= 7; i++){
            matrix.drawPixel(i, 6, color);
            }
            break;
    case 5: case 17: for (int i = 3; i <= 5; i++){
            matrix.drawPixel(i, 5, color);
            }
            break;
    case 6: case 18: for (int i = 0; i <= 4; i++){
            matrix.drawPixel(i, 8, color);
            }
            break;
    case 7: case 19: for (int i = 0; i <= 4; i++){
            matrix.drawPixel(i, 7, color);
            }
            break;
    case 8: case 20: for (int i = 7; i <= 10; i++){
            matrix.drawPixel(i, 4, color);
            }
            break;
    case 9: case 21: for (int i = 0; i <= 2; i++){
            matrix.drawPixel(i, 9, color);
            }
            break;
    case 10: case 22: for (int i = 5; i <= 10; i++){
            matrix.drawPixel(i, 7, color);
            }
            break;
  }
}

void doSerialDuties(){
  if (Serial.available()) {
    time_t t = processSyncMessage();
    if (t != 0) {
      Teensy3Clock.set(t); // set the RTC
      setTime(t);
    }
  }
}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print((hour()+GMT)%24);
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}
