#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <iomanip>
using namespace std;

#define USING_DHT11	true
#define DHT_GPIO	22 
#define LH_THRESHOLD	26
#define LED_R	4
#define LED_G	17

int main(){
	int humid = 0, temp = 0;
   	cout << "Starting the one-wire sensor program" << endl;
   	wiringPiSetupGpio();
   	piHiPri(99);

TRYAGAIN:                        
	while(1){
   		unsigned char data[5] = {0,0,0,0,0};
   		pinMode(DHT_GPIO, OUTPUT);                 
   		digitalWrite(DHT_GPIO, LOW);               
   		usleep(18000);                             
   		digitalWrite(DHT_GPIO, HIGH);              
   		pinMode(DHT_GPIO, INPUT);                  

   		do { delayMicroseconds(1); } while(digitalRead(DHT_GPIO)==HIGH);
   		do { delayMicroseconds(1); } while(digitalRead(DHT_GPIO)==LOW);
   		do { delayMicroseconds(1); } while(digitalRead(DHT_GPIO)==HIGH);
   		for(int d=0; d<5; d++) {      
      			for(int i=0; i<8; i++) {   
         			do { delayMicroseconds(1); } while(digitalRead(DHT_GPIO)==LOW);
         			int width = 0;          
         			do {
            				width++;
            				delayMicroseconds(1);
            				if(width>1000) break; 
         			} while(digitalRead(DHT_GPIO)==HIGH);    
         			data[d] = data[d] | ((width > LH_THRESHOLD) << (7-i));
      			}
   		}
   		if (USING_DHT11){
      			humid = data[0] * 10; 
      			temp = data[2] * 10;          
   		} else {                            
      			humid = (data[0]<<8 | data[1]);
      			temp = (data[2]<<8 | data[3]);
   		}
   		unsigned char chk = 0;
   	
		for(int i=0; i<4; i++){ chk+= data[i]; }
   		if(chk==data[4]){
			temp = temp / 10;
   			if(temp > 26) {
				digitalWrite(LED_R, HIGH);
				digitalWrite(LED_G, LOW);
			} else {
				digitalWrite(LED_R, LOW);
				digitalWrite(LED_G, HIGH);
			}
			cout << temp << endl;
			sleep(2);
		}
		else {
			cout << "Checksum bad - data error - trying again!" << endl;
			sleep(2);
			goto TRYAGAIN; 
		}
	}
}
