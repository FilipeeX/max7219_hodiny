#include <Sprite.h>
#include <binary.h>
#include <Matrix.h>


// Pocet displayov na 1 pasik (serivovo zapojeny).
#define pocetDisplayov 4

#define dataIn 3
#define clock 4
#define cs 5

#define dataIn2 A0
#define cs2 A2
#define clock2 A1

#define tlacidloZacat 10
#define tlacidloPlus 9
#define tlacidloMinus 8
#define tlacidloHotovo 7


Matrix led = Matrix(dataIn, clock, cs, pocetDisplayov);
Matrix led2 = Matrix(dataIn2, clock2, cs2, pocetDisplayov);

Sprite plny = Sprite(8, 8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
Sprite prazdny = Sprite(8, 8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);

bool stlaceneZacat, stlacenePlus, stlaceneMinus, stlaceneHotovo;


void setup() {

  // Serial.begin(9600);

  pinMode(tlacidloZacat, INPUT_PULLUP);
  pinMode(tlacidloPlus, INPUT_PULLUP);
  pinMode(tlacidloMinus, INPUT_PULLUP);
  pinMode(tlacidloHotovo, INPUT_PULLUP);
  
  led.clear();
  led2.clear();

}


void loop() {

  for (int i = 0; i < 4; i++) {
    led2.write(i*8, 0, plny);
    led.write(i*8, 0, plny);
    delay(1000);
    led.clear();
    led2.clear();
  }

}
