#include <Arduino.h>

#define LED 2

int incomingByte = 0; // for incoming serial data

typedef struct test_struct {
  int x;
  int y;
} test_struct;

test_struct test;
test_struct test2;

String x_str;

String FR_received;
String RR_received;
String FL_received;
String RL_received;

String bf1;
String bf2;
String bf3;
String bf4;

int ind1;
int ind2;
int ind3;
int ind4;
int ind5;
int ind6;
int ind7;
int ind8;

int i = 0;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100); 
  
  pinMode(LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
}

void loop() {
  // reply only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    x_str = Serial.readString();

    ind1              = x_str.indexOf('/');             //finds location of first ,
    bf1               = x_str.substring(0, ind1);       //captures first data String
    ind2              = x_str.indexOf('/', ind1+1 );
    FR_received       = x_str.substring(ind1+1, ind2);  //captures first data String
    ind3              = x_str.indexOf('/', ind2+1 );    //finds location of second ,
    bf2               = x_str.substring(ind2+1, ind3);
    ind4              = x_str.indexOf('/', ind3+1 );
    RR_received       = x_str.substring(ind3+1, ind4);  //captures second data String
    ind5              = x_str.indexOf('/', ind4+1 );
    bf3               = x_str.substring(ind4+1, ind5);
    ind6              = x_str.indexOf('/', ind5+1 );    //finds location of first ,
    FL_received       = x_str.substring(ind5+1, ind6);
    ind7              = x_str.indexOf('/', ind6+1 );    //finds location of second ,
    bf4               = x_str.substring(ind6+1, ind7);
    ind8              = x_str.indexOf('/', ind7+1 );
    RL_received       = x_str.substring(ind7+1, ind8);

    test.x  = FR_received.toFloat();

    Serial.print("Test: ");
    Serial.println(FR_received.toFloat());

    Serial.print("Test.x: ");
    Serial.println(test.x);
    // i += 1;
    // Serial.print("i: ");
    // Serial.println(i);

    // Serial.print("I received: ");
    // Serial.println(x_str);

    delay(100);
  }
}