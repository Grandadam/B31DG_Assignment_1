#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <driver/gpio.h>

//#define DEBUG_Timing
#ifdef DEBUG_Timing
#define Timing = 1000
#ifndef DEBUG_Timing
#define Timing = 1
#endif

 uint16_t a = 300;  // Width of first pulse
 uint16_t b = 100;  // With between pulses
 uint16_t c = 13;  // Number of pulses in block d
 uint16_t d = 6500;  // Delay between waveforms
 uint16_t e = 0; // Minimum pulse width
 uint16_t inve = 650; // Maximum pulse width
 uint16_t b_pause = 500; // 500 microseconds for signal B delay

void GPIO_Setup()
{
    gpio_set_direction(GPIO_NUM_16, GPIO_MODE_INPUT);  // Pin for Switch 1
    gpio_pulldown_en(GPIO_NUM_16); // Sets pin as a Pulldown 
    gpio_set_direction(GPIO_NUM_17, GPIO_MODE_INPUT);  // Pin for Switch 2
    gpio_pulldown_en(GPIO_NUM_17); // Sets pin as a Pulldown
    gpio_set_direction(GPIO_NUM_25, GPIO_MODE_OUTPUT); // Pin for Signal A
    gpio_set_direction(GPIO_NUM_26, GPIO_MODE_OUTPUT); // Pin for Signal B
};

void SignalA()  // Pulse width size incrementing up but 5 micro seconds
  { 
  for(int i = 0; i < 13; i++) 
   {
    gpio_set_level(GPIO_NUM_25, 1);
    usleep(a+e); 
    gpio_set_level(25, 0);
    usleep(b);
    e = e + 50; // Increaes pulse width size
   }
   usleep(d);
   e = 0; 
  }

  void InvSignalA()
  { 
  for(int i = 0; i < 13; i++) 
   {
    gpio_set_level(GPIO_NUM_25, 1);
    usleep(a+inve);
    gpio_set_level(GPIO_NUM_25, 0); 
    usleep(b);
    inve = inve - 50;
   }
   usleep(d);
   inve = 650;
  }
  
  void SignalB()
  {
    gpio_set_level(GPIO_NUM_26, 1);     // Signal B
    usleep(b_pause);  // Signal B
    gpio_set_level(GPIO_NUM_26, 0);      // Signal B    
  }



void app_main(void)
{

 bool Switch1 = gpio_get_level(GPIO_NUM_16); // Reads Switch1 position at start of loop.
 bool Switch2 = gpio_get_level(GPIO_NUM_17); // Reads Switch2 position at start of loop.
  
  if(Switch1 == 0 && Switch2 == 0) // Run Normally 
  {
     SignalB();
     SignalA();
  };
  
  if(Switch1 == 0 && Switch2 == 1) // Run with Signal A inverted
  {
     SignalB(); 
     InvSignalA();
   };
}
