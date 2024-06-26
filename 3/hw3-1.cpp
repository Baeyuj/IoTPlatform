#include <iostream>
#include <wiringPi.h>
using namespace std;

#define PIN_TRIG	23
#define PIN_ECHO	24
#define RANGE_MAX	200
#define RANGE_MIN	0
#define LED_R	4
#define LED_G	17
#define LED_B	27

int main(int argc, char* argv[]){
	wiringPiSetupGpio(); 
	unsigned int T, L;
	pinMode(PIN_TRIG, OUTPUT);
	pinMode(PIN_ECHO, INPUT);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_G, OUTPUT);
	pinMode(LED_B, OUTPUT);

	while (1) {
		digitalWrite(PIN_TRIG, LOW); delayMicroseconds(2);
		digitalWrite(PIN_TRIG, HIGH); delayMicroseconds(20);
		digitalWrite(PIN_TRIG, LOW);

		while (digitalRead(PIN_ECHO) == LOW);
		
		unsigned int startTime = micros();
 		while (digitalRead(PIN_ECHO) == HIGH);
 		T = micros() - startTime;
 		L = T / 58.2;

		if(L >= 0 && L <= 10){
			digitalWrite(LED_R, HIGH);
			digitalWrite(LED_G, LOW);
			digitalWrite(LED_B, LOW);
		} else if (L > 10 && L <= 15){
			digitalWrite(LED_R, LOW);
			digitalWrite(LED_G, HIGH);
			digitalWrite(LED_B, LOW);
		} else if (L > 15 && L <= 30 ){
			digitalWrite(LED_R, LOW);
			digitalWrite(LED_G, LOW);
			digitalWrite(LED_B, HIGH);
		} else {
			digitalWrite(LED_R, LOW);
			digitalWrite(LED_G, LOW);
			digitalWrite(LED_B, LOW);
		}
		delay(50);
	}
}
