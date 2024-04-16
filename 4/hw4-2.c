#include <stdio.h>
#include <wiringPi.h>
#include <mcp3004.h>
#include <unistd.h>

#define	BASE	200
#define SPI_CHAN	0

#define LED_R	4
#define LED_G	17
#define LED_B	27

int main(void){
	//wiringPiSetup();
	wiringPiSetupGpio();
	pinMode(LED_R, OUTPUT);
	pinMode(LED_G, OUTPUT);
	pinMode(LED_B, OUTPUT);

	mcp3004Setup(BASE, SPI_CHAN);

	int x;

	while(1){
		x = analogRead(BASE);
		printf("%d\n", x);
		
		if(x<100){
			digitalWrite(LED_R, HIGH);
			digitalWrite(LED_G, LOW);
			digitalWrite(LED_B, LOW);
		} else if(x<200){
			digitalWrite(LED_R, LOW);
			digitalWrite(LED_G, HIGH);
			digitalWrite(LED_B, LOW);
		} else if(x<300){
			digitalWrite(LED_R, LOW);
			digitalWrite(LED_G, LOW);
			digitalWrite(LED_B, HIGH);
		} else {
			digitalWrite(LED_R, LOW);
			digitalWrite(LED_G, LOW);
			digitalWrite(LED_B, LOW);	
		}
		usleep(100);
	}
}
