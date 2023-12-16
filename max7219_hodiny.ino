#include <Sprite.h>
#include <binary.h>
#include <Matrix.h>

#include <stdio.h>
#include <string.h>


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


Matrix led = Matrix(dataIn, clock, cs, pocetDisplayov);
Matrix led2 = Matrix(dataIn2, clock2, cs2, pocetDisplayov);

Sprite plny = Sprite(8, 8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
Sprite prazdny = Sprite(8, 8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);
Sprite startAnimacia[7] = {
  Sprite(8, 8, B00000000, B00000000, B00000000, B00001100, B00001100, B00000000, B00000000, B00000000),
  Sprite(8, 8, B00000000, B00000000, B00000000, B00011110, B00011110, B00000000, B00000000, B00000000),
  Sprite(8, 8, B00000000, B00000000, B00000000, B00111111, B00111111, B00000000, B00000000, B00000000),
  Sprite(8, 8, B00000000, B00000000, B00000000, B11111111, B11111111, B00000000, B00000000, B00000000),
  Sprite(8, 8, B00000000, B00000000, B11111111, B11111111, B11111111, B11111111, B00000000, B00000000),
  Sprite(8, 8, B00000000, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B00000000),
  Sprite(8, 8, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111),
};

bool stlaceneZacat, stlacenePlus, stlaceneMinus, stlaceneHotovo;
int pocet = 0;


void setup() {

  Serial.begin(9600);

  pinMode(tlacidloZacat, INPUT_PULLUP);
  pinMode(tlacidloPlus, INPUT_PULLUP);
  pinMode(tlacidloMinus, INPUT_PULLUP);
  pinMode(tlacidloHotovo, INPUT_PULLUP);
  
  led.clear();
  led2.clear();

  for (int i = 0; i < 7; i++) {
    for (int x = 0; x < 4; x++) {

      led2.write(x * 8, 0, startAnimacia[i]);
      led.write(x * 8, 0, startAnimacia[i]);
      
    }
    delay(75);
  }

  /*
  for (int x = 0; x < 4; x++) {
    led.write(x * 8, 0, prazdny);
    delay(10);
  }
  for (int x = 0; x < 4; x++) {
    led2.write(x * 8, 0, plny);
    delay(10);
  }

  led.write(0, 0, plny);
  */

}
  

void loop() {

}