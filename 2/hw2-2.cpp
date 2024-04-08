#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
using namespace std;
const int LED[2] = { 13, 18 };

int main(){
	wiringPiSetupGpio();
	pinMode(LED[0], PWM_OUTPUT);
	pinMode(LED[1], PWM_OUTPUT);
	pwmSetRange(1024);

	for(int i=0; i<2; i++){
		for(int j=1; j<1024; j++){
			pwmWrite(LED[i], j); usleep(1024);
		}
		for(int j=1023; j>=0; j--){
			pwmWrite(LED[i], j); usleep(1024);
		}
	}
	return 0;
}
