#include <stdio.h>
#include <wiringPi.h>
#include <mcp3004.h>

#define BASE 100 //mcp3004/8
#define SPI_CH 0

bool armed = true;

int main(int argc, char *argv[])
{
   int dev;
   if (wiringPiSetup() == -1) {
      printf("wiringPi init failed\n");
      return -1;
   }

   mcp3004Setup(BASE,SPI_CH);

   pinMode(2, OUTPUT);
   digitalWrite(2,HIGH);
   delay(1000);
   digitalWrite(2,LOW);
   while (1)
   {
      int val = analogRead(BASE+7);
      if (val > 200) { // around 1V, same as scope trigger level 
         digitalWrite(2,HIGH);
         val = analogRead(BASE+7);
         printf("TRIGGER!\n",val);
         delay(1000);
         digitalWrite(2,LOW);
         armed = false;
      }
   }
}
