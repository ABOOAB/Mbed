# include "mbed.h"

// Define outputs
    // Define the Led 
    DigitalOut led(p5);
    // Define the sound output 
    PwmOut sound (p21);
// Define inputs 
    // Define the level sensor 
    AnalogIn level(p15);
    // Define the temprature sensor 
    AnalogIn temp(p16);

// produce warable tone
void warable(float volume)
{
    for(float i = 0; i < 1 ; i += 0.05)
        {
            val = 0.010 - (0.008*i);
        }
}

// produce peeb tone
void peeb (float volume)
{
    sound.period(0.005);
    wait(0.05);
                    
}

// produce steady continous tone
void steady(float volume)
{
    
    sound.period(0.00167);
    wait(0.05);
}


int main()
{
    // set the volume of the sound output
    sound = 0.3;
    while (1)
    {
        // check tank leve
        // if low level 
        while(level.read() < 0.75)
        {
            // flash led
            led = ! led;
            // produce warable tone
            warable(sound);
            

        }
        // if high level
            // turn led off
            led = 0;
            // check temprature
                // if high temp 
                if (temp.read() > 0.66)
                {
                    // produce two tones
                    peeb (sound);
                    steady (sound);               
                }
                // if not midum temprature
                else if (0.66 >= temp.read() && temp.read() > 0.33)
                {
                    // produce steady steady tone
                    steady(sound); 
        
                }
                // if low temprature
                else 
                {                
                    // produce single beeping tone
                    peeb (sound);
                            
                }  
        
    }
}