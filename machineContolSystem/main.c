#include "mbed.h"
// define inputs
DigitalIn Start(p5);
DigitalIn Stop (p6);
DigitalIn Guard (p7); 
DigitalIn Temp (p8);

// define outputs
DigitalOut Ready (p9);
DigitalOut Running (p10);
DigitalOut Guard_fault (p11);
DigitalOut Temp_fault (p12);

// define busout

int main(){
    while(1){
        Ready = Running = Guard_fault = Temp_fault = 0;
        while(Guard == 0 || Temp == 1){
            Running = Guard_fault = Temp_fault = 0;
            Ready = !Ready;
            wait(0.2);
        }
        Ready = 1;
        while(Start == 0);
        Running = 1;
        Ready = 0;
        while(Guard && !Temp && !Stop);
        Running = 0;
        if (!Guard){
            Guard_fault =1;
            wait(0.5);
            Guard_fault = 0;
        }
        else if (Temp){
            Temp_fault = 1;
            wait(0.5);
            Temp_fault = 0;
        }
        
            
     
        
    }
}
