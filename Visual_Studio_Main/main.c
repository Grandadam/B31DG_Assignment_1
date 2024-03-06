#include <stdint.h>
#include <stdio.h>

uint16_t a = 300;  // Width of first pulse
uint16_t b = 100;  // With between pulses
uint16_t c = 13;  // Number of pulses in block 
uint16_t d = 6500;  // Delay between waveforms
uint16_t e = 0; // Minimum pulse width
uint16_t inve = 650; // Maximum pulse width

 pinMode (16,INPUT);  // Pin for Switch 1
 pinMode (17,INPUT);  // Pin for Switch 2
 pinMode (25,OUTPUT); // Pin for Signal A
 pinMode (26,OUTPUT); // Pin for Signal B

 void loop()
{

 bool Switch1 = digitalRead(16); // Reads Switch1 position at start of loop.
 bool Switch2 = digitalRead(17); // Reads Switch2 position at start of loop.
  
  if(Switch1 == LOW && Switch2 == LOW) // Run Normally 
  {
     SignalB();
     SignalA();
  };
  
  if(Switch1 == LOW && Switch2 == HIGH) // Run with Signal A inverted
  {
     SignalB(); 
     InvSignalA();
   };
}

void SignalA()  // Pulse width size incrementing up but 5 micro seconds
  { 
  for(int i = 0; i < 13; i++) 
   {
    digitalWrite(25,HIGH);
    delayMicroseconds(a+e); 
    digitalWrite(25,LOW); 
    delayMicroseconds(b);
    e = e + 50; // Increaes pulse width size
   }
   delay(d);
   e = 0; 
  }

  void InvSignalA()
  { 
  for(int i = 0; i < 13; i++) 
   {
    digitalWrite(25,1);
    delayMicroseconds(a+inve);
    digitalWrite(25,0); 
    delayMicroseconds(b);
    inve = inve - 50;
   }
   delayMicroseconds(d);
   inve = 650;
  }
  
  void SignalB()
  {
    digitalWrite(26,HIGH);     // Signal B
    delayMicroseconds(pause);  // Signal B
    digitalWrite(26,LOW);      // Signal B    
  }