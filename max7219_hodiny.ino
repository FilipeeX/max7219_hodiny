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

Sprite startAnimacia[7] = {Sprite(8, 8, B00000000, B00000000, B00000000, B00011000, B00011000, B00000000, B00000000, B00000000), 
                        Sprite(8, 8, B00000000, B00000000, B00011000, B00111100, B00111100, B00011000, B00000000, B00000000), 
                        Sprite(8, 8, B00000000, B00011000, B00111100, B01111110, B01111110, B00111100, B00011000, B00000000), 
                        Sprite(8, 8, B00011000, B00111100, B01111110, B11111111, B11111111, B01111110, B00111100, B00011000), 
                        Sprite(8, 8, B00111100, B01111110, B11111111, B11111111, B11111111, B11111111, B01111110, B00111100), 
                        Sprite(8, 8, B01111110, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B01111110), 
                        Sprite(8, 8, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111)};


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

  for (int i = 0; i < 7; i++) {
    for (int x = 0; x < 4; x++) {

      int tlacidla[4] = {tlacidloZacat, tlacidloPlus, tlacidloMinus, tlacidloHotovo};

      if (digitalRead(tlacidla[x]) == LOW) {

        led.write(x*8, 0, startAnimacia[i]);
        delay(1);
        led2.write(x*8, 0, startAnimacia[i]);

      } else {

        led.write(x*8, 0, prazdny);
        delay(1);
        led2.write(x*8, 0, prazdny);

      }

    }

    delay(10);

  } 

}
