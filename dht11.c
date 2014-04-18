#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
//#include <softPwm.h>

#define DATA_PIN 0
int bits[250],data[200];
int bitidx = 0;

int main ()
{

  int pin = DATA_PIN;
  int counter = 0;
  int laststate = 1;
  int i,j=0;

  wiringPiSetup ()  ;
  piHiPri (80) ;
  pinMode(pin,OUTPUT);

  digitalWrite(pin,1);
  usleep(500000);

  // Start sequence

  // Pull down for 20ms
  digitalWrite(pin,0);
  usleep(20000); 

  pinMode(pin,INPUT);

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;

  // wait for pin to drop
  while( digitalRead(pin) == 1)
  {
	//usleep(1);
	;
  };

  for (i=0; i < 100; i++)
  {
	counter = 0;
	while (digitalRead(pin) == laststate)
	{
		counter++;
		//nanosleep(1);		// overclocking might change this?
        	if (counter == 1000)
	  		break;
    	};

    	laststate = digitalRead(pin);
    	if (counter == 1000) break;
    		bits[bitidx++] = counter;

    	if ((i>3) && (i%2 == 0))
	{
      		// shove each bit into the storage bytes
      		data[j/8] <<= 1;
      		if (counter > 200)
        		data[j/8] |= 1;
      		j++;
    	}
  }


  for (i=3; i<bitidx; i+=2)
  {
    printf("bit %d: %d\n", i-3, bits[i]);
    printf("bit %d: %d (%d)\n", i-2, bits[i+1], bits[i+1] > 200);
  }

  printf("Data (%d): 0x%x 0x%x 0x%x 0x%x 0x%x\n", j, data[0], data[1], data[2], data[3], data[4]);

  if ((j >= 39) &&
      (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) )
  {
    printf("Temp = %d*C, Hum = %d%% \n",(int) data[2],(int) data[0]);
    return 1;
  }

  return 0;
}
