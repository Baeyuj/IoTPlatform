#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
using namespace std;
#define LED_R	13
#define LED_Y	27
#define LED_G	18
#define BUTTON_R	24
#define BUTTON_Y	23
#define BUTTON_G	22
#define DEBOUNCE_TIME	200
bool state[3] = {0, 0, 0};

void lightLEDR(void){
	static unsigned long lastISRTime = 0;
	unsigned long currentISRTime = millis();
	if(currentISRTime - lastISRTime > DEBOUNCE_TIME){
		state[0] = !state[0];
		digitalWrite(LED_R, state[0]);
	}
	lastISRTime = currentISRTime;
}

void lightLEDY(void){
	static unsigned long lastISRTime = 0;
	unsigned long currentISRTime = millis();
	if(currentISRTime - lastISRTime > DEBOUNCE_TIME){
		state[1] = !state[1];
		digitalWrite(LED_Y, !state[1]);
	}
	lastISRTime = currentISRTime;
}

void lightLEDG(void){
	static unsigned long lastISRTime = 0;
	unsigned long currentISRTime = millis();
	if(currentISRTime - lastISRTime > DEBOUNCE_TIME){
		state[2] = !state[2];
		digitalWrite(LED_G, !state[2]);
	}
	lastISRTime = currentISRTime;
}

int main(){
	wiringPiSetupGpio();
	pinMode(LED_R, OUTPUT);
	pinMode(LED_Y, OUTPUT);
	pinMode(LED_G, OUTPUT);
	pinMode(BUTTON_R, INPUT);
	pinMode(BUTTON_Y, INPUT);
	pinMode(BUTTON_G, INPUT);

	digitalWrite(LED_R, LOW);
	digitalWrite(LED_Y, LOW);
	digitalWrite(LED_G, LOW);

	wiringPiISR(BUTTON_R, INT_EDGE_RISING, &lightLEDR);
	wiringPiISR(BUTTON_Y, INT_EDGE_RISING, &lightLEDY);
	wiringPiISR(BUTTON_G, INT_EDGE_RISING, &lightLEDG);

	for(int i=10; i>0; i--)	sleep(1);
	return 0;
}
