#include <DS3231.h>
#include <Wire.h>

#include <Sprite.h>
#include <binary.h>
#include <Matrix.h>


// Pocet displayov na 1 pasik (serivovo zapojeny).
#define pocetDisplayov 4

#define dataIn 3
#define clock 4
#define cs 5

#define dataIn2 A0
#define clock2 A1
#define cs2 A2

#define tlacidloZacat 10
#define tlacidloPlus 9
#define tlacidloMinus 8
#define tlacidloHotovo 7


DS3231 rtc;

bool century = true;
bool h12flag, pmFlag;

Matrix led = Matrix(dataIn, clock, cs, pocetDisplayov);
Matrix led2 = Matrix(dataIn2, clock2, cs2, pocetDisplayov);

Sprite plny = Sprite(8, 8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
Sprite prazdny = Sprite(8, 8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);

Sprite a[2] = {
  Sprite(8, 8, B00110011, B00110011, B00110011, B00110011, B00110011, B00110011, B00111111, B00111111),
  Sprite(8, 8, B00110011, B00110011, B00110011, B00110011, B00110011, B00110011, B00111111, B00111111)
};

Sprite cifra0[2] = {
  Sprite(8, 8, B00110011, B00110011, B00110011, B00110011, B00110011, B00110011, B00111111, B00111111),
  Sprite(8, 8, B00111111, B00111111, B00110011, B00110011, B00110011, B00110011, B00110011, B00110011)
};
Sprite cifra1[2] = {
  Sprite(8, 8, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000),
  Sprite(8, 8, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000)
};
Sprite cifra2[2] = {
  Sprite(8, 8, B00111111, B00110000, B00110000, B00110000, B00110000, B00110000, B00111111, B00111111),
  Sprite(8, 8, B00111111, B00111111, B00000011, B00000011, B00000011, B00000011, B00000011, B00111111)
};
Sprite cifra3[2] = {
  Sprite(8, 8, B00111111, B00110000, B00110000, B00110000, B00110000, B00110000, B00111111, B00111111),
  Sprite(8, 8, B00111111, B00111111, B00110000, B00110000, B00110000, B00110000, B00110000, B00111111)
};
Sprite cifra4[2] = {
  Sprite(8, 8, B00111111, B00011011, B00000011, B00000011, B00000011, B00000011, B00000011, B00000011),
  Sprite(8, 8, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00111111)
};
Sprite cifra5[2] = {
  Sprite(8, 8, B00111111, B00000011, B00000011, B00000011, B00000011, B00000011, B00111111, B00111111),
  Sprite(8, 8, B00111111, B00111111, B00110000, B00110000, B00110000, B00110000, B00110000, B00111111)
};
Sprite cifra6[2] = {
  Sprite(8, 8, B00111111, B00000011, B00000011, B00000011, B00110011, B00110011, B00111111, B00111111),
  Sprite(8, 8, B00111111, B00111111, B00110011, B00110011, B00110011, B00110011, B00110011, B00111111)
};
Sprite cifra7[2] = {
  Sprite(8, 8, B00111110, B00111110, B00011000, B00011000, B00011000, B00011000, B00011111, B00011111),
  Sprite(8, 8, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000)
};
Sprite cifra8[2] = {
  Sprite(8, 8, B00111111, B00110011, B00110011, B00110011, B00110011, B00110011, B00111111, B00111111),
  Sprite(8, 8, B00111111, B00111111, B00110011, B00110011, B00110011, B00110011, B00110011, B00111111)
};
Sprite cifra9[2] = {
  Sprite(8, 8, B00111111, B00110011, B00110011, B00110011, B00110011, B00110011, B00111111, B00111111),
  Sprite(8, 8, B00111111, B00111111, B00110000, B00110000, B00110000, B00110000, B00110000, B00111111)
};

Sprite startAnimacia[7] = {
  Sprite(8, 8, B00000000, B00000000, B00000000, B00001100, B00001100, B00000000, B00000000, B00000000),
  Sprite(8, 8, B00000000, B00000000, B00000000, B00011110, B00011110, B00000000, B00000000, B00000000),
  Sprite(8, 8, B00000000, B00000000, B00000000, B00111111, B00111111, B00000000, B00000000, B00000000),
  Sprite(8, 8, B00000000, B00000000, B00000000, B11111111, B11111111, B00000000, B00000000, B00000000),
  Sprite(8, 8, B00000000, B00000000, B11111111, B11111111, B11111111, B11111111, B00000000, B00000000),
  Sprite(8, 8, B00000000, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B00000000),
  Sprite(8, 8, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111),
};
Sprite loadingAnimacia[23] = {
  Sprite(8, 8, B00000000, B00000000, B00000000, B00000000, B00000000, B00000011, B00000011, B00000000),
  Sprite(8, 8, B00000000, B00000000, B00000000, B00000000, B00000000, B00000111, B00000111, B00000000), 
  Sprite(8, 8, B00000000, B00000000, B00000000, B00000000, B00000000, B00001111, B00001111, B00000000), 
  Sprite(8, 8, B00000000, B00000000, B00000000, B00000000, B00000000, B00011111, B00011111, B00000000), 
  Sprite(8, 8, B00000000, B00000000, B00000000, B00000000, B00000000, B00111111, B00111111, B00000000), 
  Sprite(8, 8, B00000000, B00000000, B00000000, B00000000, B00110000, B00111110, B00111110, B00000000), 
  Sprite(8, 8, B00000000, B00000000, B00000000, B00110000, B00110000, B00111100, B00111100, B00000000), 
  Sprite(8, 8, B00000000, B00000000, B00110000, B00110000, B00110000, B00111000, B00111000, B00000000), 
  Sprite(8, 8, B00000000, B00110000, B00110000, B00110000, B00110000, B00110000, B00110000, B00000000), 
  Sprite(8, 8, B00000000, B00111000, B00111000, B00110000, B00110000, B00110000, B00000000, B00000000), 
  Sprite(8, 8, B00000000, B00111100, B00111100, B00110000, B00110000, B00000000, B00000000, B00000000), 
  Sprite(8, 8, B00000000, B00111110, B00111110, B00110000, B00000000, B00000000, B00000000, B00000000), 
  Sprite(8, 8, B00000000, B00111111, B00111111, B00000000, B00000000, B00000000, B00000000, B00000000), 
  Sprite(8, 8, B00000000, B00011111, B00011111, B00000011, B00000000, B00000000, B00000000, B00000000), 
  Sprite(8, 8, B00000000, B00001111, B00001111, B00000011, B00000011, B00000000, B00000000, B00000000), 
  Sprite(8, 8, B00000000, B00000111, B00000111, B00000011, B00000011, B00000011, B00000000, B00000000), 
  Sprite(8, 8, B00000000, B00000011, B00000011, B00000011, B00000011, B00000011, B00000011, B00000000),
  Sprite(8, 8, B00000000, B00000000, B00000011, B00000011, B00000011, B00000011, B00000011, B00000000), 
  Sprite(8, 8, B00000000, B00000000, B00000011, B00000011, B00000011, B00000011, B00000011, B00000000),
  Sprite(8, 8, B00000000, B00000000, B00000000, B00000011, B00000011, B00000011, B00000011, B00000000),
  Sprite(8, 8, B00000000, B00000000, B00000000, B00000000, B00000011, B00000011, B00000011, B00000000),
  Sprite(8, 8, B00000000, B00000000, B00000000, B00000000, B00000000, B00000011, B00000011, B00000000),
  Sprite(8, 8, B00000000, B00000000, B00000000, B00000000, B00000000, B00000011, B00000011, B00000000)
};

bool stlaceneZacat, stlacenePlus, stlaceneMinus, stlaceneHotovo;
int pocet = 0;


void setup() {

  // Serial.begin(9600);

  pinMode(tlacidloZacat, INPUT_PULLUP);
  pinMode(tlacidloPlus, INPUT_PULLUP);
  pinMode(tlacidloMinus, INPUT_PULLUP);
  pinMode(tlacidloHotovo, INPUT_PULLUP);

  Wire.begin();
  
  led.clear();
  led2.clear();

  for (int i = 0; i < 7; i++) {
    for (int x = 0; x < 4; x++) {

      led2.write(x * 8, 0, startAnimacia[i]);
      led.write(x * 8, 0, startAnimacia[i]);
      
    }
    delay(60);
  }

  led.clear();
  led2.clear();

  for (int i = 0; i < 23; i++) {
    for (int x = 0; x < 4; x++) {

      led2.write(x * 8, 0, loadingAnimacia[i]);
      led.write(x * 8, 0, loadingAnimacia[i]);
      
    }
  }

  led.clear();
  led2.clear();

}
  

void loop() {

  int month = rtc.getMonth(century);
  int day = rtc.getDate();
    
  int hours = rtc.getHour(h12flag, pmFlag);
  int minutes = rtc.getMinute();

  int seconds = rtc.getSecond();

  hodiny(hours);
  minuty(minutes);

  delay(100);

}


void hodiny(int hodnota) {

  if (hodnota < 10) {
    zobraz(0, -1);
    zobraz(1, hodnota);
  } else {
    zobraz(0, hodnota / 10);
    zobraz(1, hodnota % 10);
  }

}


void minuty(int hodnota) {

  if (hodnota < 10) {
    zobraz(2, 0);
    zobraz(3, hodnota);
  } else {
    zobraz(2, hodnota / 10);
    zobraz(3, hodnota % 10);
  }

}


void zobraz(int segment, int cifra) {

  switch (cifra) {

    case 0:
      led.write(segment * 8, 0, cifra0[0]);
      led2.write(segment * 8, 0, cifra0[1]);
      break;
    
    case 1:
      led.write(segment * 8, 0, cifra1[0]);
      led2.write(segment * 8, 0, cifra1[1]);
      break;
    
    case 2:
      led.write(segment * 8, 0, cifra2[0]);
      led2.write(segment * 8, 0, cifra2[1]);
      break;
    
    case 3:
      led.write(segment * 8, 0, cifra3[0]);
      led2.write(segment * 8, 0, cifra3[1]);
      break;
    
    case 4:
      led.write(segment * 8, 0, cifra4[0]);
      led2.write(segment * 8, 0, cifra4[1]);
      break;
    
    case 5:
      led.write(segment * 8, 0, cifra5[0]);
      led2.write(segment * 8, 0, cifra5[1]);
      break;
    
    case 6:
      led.write(segment * 8, 0, cifra6[0]);
      led2.write(segment * 8, 0, cifra6[1]);
      break;
    
    case 7:
      led.write(segment * 8, 0, cifra7[0]);
      led2.write(segment * 8, 0, cifra7[1]);
      break;

    case 8:
      led.write(segment * 8, 0, cifra8[0]);
      led2.write(segment * 8, 0, cifra8[1]);
      break;
    
    case 9:
      led.write(segment * 8, 0, cifra9[0]);
      led2.write(segment * 8, 0, cifra9[1]);
      break;
    
    default:
      led.write(segment * 8, 0, prazdny);
      led2.write(segment * 8, 0, prazdny);
    
  }

}