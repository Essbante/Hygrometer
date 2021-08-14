#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

int H = A4;
int T = A5;

int ULT = 8;
int ULB = 9;
int UT  = 5;
int UB  = 7;
int UM  = 6;
int URT = 3;
int URB = 4;

int TLT = A2;
int TLB = A3;
int TT  = 13;
int TB  = A1;
int TM  = A0;
int TRT = 10;
int TRB = 11;

int END = 999;

int U0[] = {ULT, ULB, UT, UB, URT, URB, END};
int U1[] = {URT, URB, END};
int U2[] = {UT, UM, UB, URT, ULB, END};
int U3[] = {UT, UM, UB, URT, URB, END};
int U4[] = {ULT, URT, UM, URB, END};
int U5[] = {UT, UM, UB, ULT, URB, END};
int U6[] = {UT, UM, UB, ULT, URB, ULB, END};
int U7[] = {UT, URT, URB, END};
int U8[] = {UT, UM, UB, URT, URB, ULT, ULB, URB, END};
int U9[] = {UT, UM, UB, URT, ULT, URB, END};

int T0[] = {TLT, TLB, TT, TB, TRT, TRB, END};
int T1[] = {TRT, TRB, END};
int T2[] = {TT, TM, TB, TRT, TLB, END};
int T3[] = {TT, TM, TB, TRT, TRB, END};
int T4[] = {TLT, TRT, TM, TRB, END};
int T5[] = {TT, TM, TB, TLT, TRB, END};
int T6[] = {TT, TM, TB, TLT, TRB, TLB, END};
int T7[] = {TT, TRT, TRB, END};
int T8[] = {TT, TM, TB, TRT, TRB, TLT, TLB, TRB, END};
int T9[] = {TT, TM, TB, TRT, TLT, TRB, END};

int TE[] = {TT, TM, TB, TLT, TLB, END};
int UE[] = {UM, ULB, END};

int *units[10] = {U0, U1, U2, U3, U4, U5, U6, U7, U8, U9};
int *tens[10] = {T0, T1, T2, T3, T4, T5, T6, T7, T8, T9};

int all[] = {H, T, UT, UM, UB, URT, URB, ULT, ULB, TT, TM, TB, TRT, TRB, TLT, TLB};
int unitsPins[] = {UT, UM, UB, URT, URB, ULT, ULB};
int tensPins[] = {TT, TM, TB, TRT, TRB, TLT, TLB};
int otherPins[] = {H, T};

void setPins()
{
  for (int index = 0; index < 16; index++)
  {
    pinMode(all[index], OUTPUT);
  }
}

void setup() {

  Serial.begin(9600);
  Serial.println(F("DHT!"));

  setPins();
  dht.begin();
}

void displayUnits(int u) {

  int* array = units[u];

  for (int k = 0; k < 7; k++) {
    digitalWrite(unitsPins[k], LOW);   // turn LED off
  }

  for (int j = 0; array[j] != END; j++) {
    digitalWrite(array[j], HIGH);  // turn LED on
  }
}

void displayTens(int t) {

  int* array = tens[t];

  for (int k = 0; k < 7; k++) {
    digitalWrite(tensPins[k], LOW);   // turn LED off
  }

  for (int j = 0; array[j] != END; j++) {
    digitalWrite(array[j], HIGH);  // turn LED on
  }
}

void displayErr() {

  int* array = TE;

  for (int k = 0; k < 7; k++) {
    digitalWrite(tensPins[k], LOW);   // turn LED off
  }

  for (int j = 0; array[j] != END; j++) {
    digitalWrite(array[j], HIGH);  // turn LED on
  }

  array = UE;

  for (int k = 0; k < 7; k++) {
    digitalWrite(unitsPins[k], LOW);   // turn LED off
  }

  for (int j = 0; array[j] != END; j++) {
    digitalWrite(array[j], HIGH);  // turn LED on
  }
}

void clear() {
  for (int k = 0; k < 7; k++) {
    digitalWrite(unitsPins[k], LOW);   // turn LED off
  }
  for (int k = 0; k < 7; k++) {
    digitalWrite(tensPins[k], LOW);   // turn LED off
  }
  digitalWrite(H, LOW);
  digitalWrite(T, LOW);
}

void displayTemp(int value) {
  digitalWrite(H, LOW);
  digitalWrite(T, HIGH);
  displayUnits(value % 10);
  displayTens((value - (value % 10)) / 10);
}

void displayHumidity(int value) {
  digitalWrite(H, HIGH);
  digitalWrite(T, LOW);
  displayUnits(value % 10);
  displayTens((value - (value % 10)) / 10);
}


void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    displayErr();
    delay(500);
    clear();
    delay(500);
    return;
  }

  displayTemp((int)t);
  delay(3000);

  displayHumidity((int)h);
  delay(3000);
}
