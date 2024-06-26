#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>         // for the microsecond sleep function

using namespace std;
#define GPIO         "/sys/class/gpio/"
#define FLASH_DELAY  1

class LED {
private:                // the following is part of the implementation
    string gpioPath;     // private states
    int    gpioNumber;
    void writeSysfs(string path, string filename, string value);
public:                 // part of the public interface
    LED(int gpioNumber); // the constructor -- create the object
    virtual void turnOn();
    virtual void turnOff();
    virtual void displayState();
    virtual ~LED();      // the destructor -- called automatically
};

LED::LED(int gpioNumber) {  // constructor implementation
    this->gpioNumber = gpioNumber;
    gpioPath = string(GPIO "gpio") + to_string(gpioNumber) + string("/");
    writeSysfs(string(GPIO), "export", to_string(gpioNumber));
    usleep(100000);         // ensure GPIO is exported
    writeSysfs(gpioPath, "direction", "out");
}

// This implementation function is "hidden" outside of the class
void LED::writeSysfs(string path, string filename, string value) {
    ofstream fs;
    fs.open((path + filename).c_str());
    fs << value;
    fs.close();
}

void LED::turnOn() {
    writeSysfs(gpioPath, "value", "1");
}

void LED::turnOff() {
    writeSysfs(gpioPath, "value", "0");
}

void LED::displayState() {
    ifstream fs;
    fs.open((gpioPath + "value").c_str());
    string line;
    cout << "The current LED state is ";
    while (getline(fs, line)) cout << line << endl;
    fs.close();
}

LED::~LED() {  // The destructor unexports the sysfs GPIO entries
    cout << "Destroying the LED with GPIO number " << gpioNumber << endl;
    writeSysfs(string(GPIO), "unexport", to_string(gpioNumber));
}

int main(int argc, char* argv[]) {  // the main function start point
    cout << "Starting the makeLEDs program" << endl;
    LED led1(25), led2(17), led3(27);          // create two LED objects
    cout << "Flashing the LEDs for 5 seconds" << endl;
    for (int i = 0; i < 5; i++) {        // LEDs will alternate
        led1.turnOn();               
        led2.turnOff();              
        sleep(FLASH_DELAY);         
        led1.turnOff();              
        led2.turnOn();               
        sleep(FLASH_DELAY);         
        led2.turnOff();
        led3.turnOn();
        sleep(FLASH_DELAY);
        led2.turnOn();
        led3.turnOff();
	sleep(FLASH_DELAY);
    }
    led2.turnOff();
    led1.displayState();            
    led2.displayState(); 
    led3.displayState();
    cout << "Finished the makeLEDs program" << endl;
    return 0;
}
