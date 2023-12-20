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

#define odpocetTlacidiel 5 // ms


DS3231 rtc;

bool century = true;
bool h12flag, pmFlag;

Matrix led = Matrix(dataIn, clock, cs, pocetDisplayov);
Matrix led2 = Matrix(dataIn2, clock2, cs2, pocetDisplayov);

Sprite plny = Sprite(8, 8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
Sprite prazdny = Sprite(8, 8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);

// m, s, i, c, d, n, h, o, t, e, k, u
Sprite c = Sprite(8, 8, B00111100, B00000010, B00000001, B00000001, B00000001, B00000010, B00111100, B00000000);
Sprite d = Sprite(8, 8, B00000000, B00001110, B00010010, B00100010, B00100010, B00010010, B00001110, B00000000);
Sprite e = Sprite(8, 8, B00000000, B00011110, B00000010, B00000010, B00001110, B00000010, B00011110, B00000000);
Sprite h = Sprite(8, 8, B00000000, B00010010, B00010010, B00010010, B00011110, B00010010, B00010010, B00000000);
Sprite i = Sprite(8, 8, B00000000, B00001110, B00000100, B00000100, B00000100, B00000100, B00001110, B00000000);
Sprite k = Sprite(8, 8, B00000000, B00010010, B00010010, B00001010, B00000110, B00001010, B00010010, B00000000);
Sprite m = Sprite(8, 8, B00000000, B10100000, B10100000, B10100100, B10101010, B00010001, B00000000, B00000000);
Sprite n = Sprite(8, 8, B00000000, B00000000, B00100010, B00110010, B00101010, B00100110, B00100010, B00000000);
Sprite o = Sprite(8, 8, B00000000, B00011110, B00100001, B00100001, B00100001, B00100001, B00011110, B00000000);
Sprite s = Sprite(8, 8, B00000000, B00011110, B00010000, B00010000, B00011110, B00000010, B00011110, B00000000);
Sprite t = Sprite(8, 8, B00000000, B00000100, B00000100, B00000100, B00000100, B00000100, B00011111, B00000000);
Sprite u = Sprite(8, 8, B00000000, B00001100, B00010010, B00100001, B00100001, B00100001, B00100001, B00000000);

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

int zacatOdpocet = 0;
int plusOdpocet = 0;
int minusOdpocet = 0;
int hotovoOdpocet = 0;
int pocitadlo = 0;

// 0 = HODINY
// 1 = NASTAVOVANIE ROKU
// 2 = NASTAVOVANIE MESIACU
// 3 = NASTAVOVANIE DNA
// 4 = NASTAVOVANIE HODINY
// 5 = NASTAVOVANIE MINUT
// 6 = NASTAVOVANIE SEKUND
int status = 0;

int rok = 23;
int mesiac;
int den;
int hodina = 12;
int minuta = 30;
int sekunda = 30;


void setup() {

  // Serial.begin(9600);

  pinMode(tlacidloZacat, INPUT_PULLUP);
  pinMode(tlacidloPlus, INPUT_PULLUP);
  pinMode(tlacidloMinus, INPUT_PULLUP);
  pinMode(tlacidloHotovo, INPUT_PULLUP);

  Wire.begin();
  mesiac = rtc.getMonth(century);
  den = rtc.getDate();
  
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


// 1 loop ~ 1 ms
void loop() {

  if (pocitadlo >= 100) {

    if (status == 0) {
      rutinaHodiny();
    }

    pocitadlo = 0;
  }

  pocitadlo++;
  delay(1);

  bool statusZacat = digitalRead(tlacidloZacat) == LOW;
  bool statusPlus = digitalRead(tlacidloPlus) == LOW;
  bool statusMinus = digitalRead(tlacidloMinus) == LOW;
  bool statusHotovo = digitalRead(tlacidloHotovo) == LOW;

  if (zacatOdpocet > 0) {
    statusZacat = false;
    zacatOdpocet--;
  } else if (statusZacat) {
    zacatOdpocet = odpocetTlacidiel;
  }
  
  if (status == 0) {
    if (plusOdpocet > 0) {
      statusPlus = false;
      plusOdpocet--;
    } else if (statusPlus) {
      plusOdpocet = odpocetTlacidiel;
    }

    if (minusOdpocet > 0) {
      statusMinus = false;
      minusOdpocet--;
    } else if (statusMinus) {
      minusOdpocet = odpocetTlacidiel;
    }
  }

  if (hotovoOdpocet > 0) {
    statusHotovo = false;
    hotovoOdpocet--;
  } else if (statusHotovo) {
    hotovoOdpocet = odpocetTlacidiel;
  }


  if (status == 0) {
    if (statusZacat) {
      status = 1;
      load();
      return;
    }
  }

  if (status == 1) {

    if (statusPlus && rok <= 98) {
      rok++;
    }
    if (statusMinus && rok >= 1) {
      rok--;
    }
    
    hodiny(20);
    minuty(rok);

    if (statusHotovo) {
      status = 2;
      load();
      return;
    }

  }

  if (status == 2) {

    if (statusPlus && mesiac <= 11) {
      mesiac++;
    }
    if (statusMinus && mesiac >= 2) {
      mesiac--;
    }
    
    if (mesiac < 10) {
      led.write(0, 0, m);
      led.write(8, 0, s);
      led2.write(0, 0, i);
      led2.write(8, 0, c);
      zobraz(2, -1);
      zobraz(3, mesiac);
    } else {
      led.write(0, 0, m);
      led.write(8, 0, s);
      led2.write(0, 0, i);
      led2.write(8, 0, c);
      zobraz(2, mesiac / 10);
      zobraz(3, mesiac % 10);
    }

    if (statusHotovo) {
      status = 3;
      load();
      return;
    }

  }

  if (status == 3) {

    if (statusPlus && den <= 30) {
      den++;
    }
    if (statusMinus && den >= 2) {
      den--;
    }
    
    hodiny(den);
    led.write(16, 0, d);
    led.write(24, 0, e);
    led2.write(16, 0, n);
    led2.write(24, 0, prazdny);

    if (statusHotovo) {
      status = 4;
      load();
      return;
    }

  }

  if (status == 4) {

    if (statusPlus && hodina <= 22) {
      hodina++;
    }
    if (statusMinus && hodina >= 1) {
      hodina--;
    }
    
    hodiny(hodina);
    led.write(16, 0, h);
    led.write(24, 0, o);
    led2.write(16, 0, d);
    led2.write(24, 0, n);

    if (statusHotovo) {
      status = 5;
      load();
      return;
    }

  }

  if (status == 5) {

    if (statusPlus && minuta <= 58) {
      minuta++;
    }
    if (statusMinus && minuta >= 2) {
      minuta--;
    }
    
    minuty(minuta);
    led.write(0, 0, m);
    led.write(8, 0, i);
    led2.write(0, 0, n);
    led2.write(8, 0, t);

    if (statusHotovo) {
      status = 6;
      load();
      return;
    }

  }

  if (status == 6) {

    if (statusPlus && sekunda <= 58) {
      sekunda++;
    }
    if (statusMinus && sekunda >= 2) {
      sekunda--;
    }
    
    minuty(sekunda);
    led.write(0, 0, s);
    led.write(8, 0, e);
    led2.write(0, 0, k);
    led2.write(8, 0, n);

    if (statusHotovo) {
      status = 0;
      rtc.setYear(rok);
      rtc.setMonth(mesiac);
      rtc.setDate(den);
      rtc.setHour(hodina);
      rtc.setMinute(minuta);
      rtc.setSecond(sekunda);
      load();
      return;
    }

  }

}


void load() {

  for (int i = 0; i < 23; i++) {
    for (int x = 0; x < 4; x++) {

      led2.write(x * 8, 0, loadingAnimacia[i]);
      led.write(x * 8, 0, loadingAnimacia[i]);
      
    }
  }

}


void rutinaHodiny() {

  int month = rtc.getMonth(century);
  int day = rtc.getDate();
    
  int hours = rtc.getHour(h12flag, pmFlag);
  int minutes = rtc.getMinute();

  int seconds = rtc.getSecond();

  hodiny(hours);
  minuty(minutes);

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