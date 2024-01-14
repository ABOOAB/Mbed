

#include "mbed.h"

// define interrupts
InterruptIn alarm(p5);
InterruptIn adult_req(p6);
InterruptIn child_req(p7); 

// define outputs
DigitalOut no_entery(p8);
DigitalOut barb_ch1(p9);
DigitalOut barb_ch2(p10);
DigitalOut barb_ch3(p11);
DigitalOut wall_clock(p12);

BusOut waiting_seats(p13, p14, p15, p16, p17, p18, p19, p20);

// some varialbles 

int ch1_time, ch2_time, ch3_time;
int adult_num, child_num;


// interrupt functions

void adult_entery(){
    if ((adult_num + child_num) < 8){
        adult_num ++;
       
        waiting_seats = waiting_seats<< 1;
        waiting_seats = waiting_seats | 0x01;
        
    }
    else{ 
    no_entery = 1;
    wait_ms(40);
    no_entery = 0;
        
    }
}

void child_entery(){
    if ((adult_num + child_num) < 7) {
        adult_num ++;
        child_num ++;
      
        waiting_seats = waiting_seats << 2;
        waiting_seats = waiting_seats | 0x03;
        
    }
    else {
        no_entery = 1;
        wait_ms(40);
        no_entery = 0;
        
    }
}

void alarm_emrg(){
    
    no_entery = 1;
    // all ppl should exit
    barb_ch1 = barb_ch2 = barb_ch3 = 0;
    while (waiting_seats != 0){
        waiting_seats = waiting_seats >> 1;
        wait_ms(600);
        
    }
    adult_num = 0;
    child_num = 0;
    wait(20);
    no_entery = 0;
    
    // wait for fire engine 
}

int main(){
    adult_req.rise(&adult_entery);
    child_req.rise(&child_entery);
    alarm.rise(&alarm_emrg);
    waiting_seats = 0x00;
    
    while(1){
        if (barb_ch1 == 1){
            ch1_time --;
            if (ch1_time == 0) barb_ch1 = 0;
        }
        else if (adult_num > 0){
                barb_ch1 = 1;
                adult_num --;
                waiting_seats = waiting_seats >> 1;
                ch1_time = 12;
           
        }
        
        if (barb_ch2 == 1){
            ch2_time --;
            if (ch2_time == 0) barb_ch2 = 0;
        }
        else if (adult_num > 0){
                barb_ch2 = 1;
                adult_num --;
                waiting_seats = waiting_seats >> 1;
                ch2_time = 12;
           
        }
        
        
        if (barb_ch3 == 1){
            ch3_time --;
            if (ch3_time == 0) {
            barb_ch3 = 0;
            child_num --;
            waiting_seats = waiting_seats >> 1;
            }
        
        }
        else if (child_num != 0){
                barb_ch3 = 1;
                waiting_seats = waiting_seats >> 1;
                ch3_time = 12;
           
        }
        
        wait_ms(1000);
        wall_clock = ! wall_clock;
         

    }
}















































































































































































