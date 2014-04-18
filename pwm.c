/*
 * pwm.c:
 *	This tests the hardware PWM channel.
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (void)
{
  int rb;

  printf ("Raspberry Pi wiringPi PWM test program\n") ;

  if (wiringPiSetup () == -1)
    exit (1) ;

  pinMode (0, OUTPUT) ;
  pinMode (1, PWM_OUTPUT) ;
  pinMode (2, OUTPUT) ;

  digitalWrite(0,1);
  digitalWrite(2,0);

  for (;;)
  {
    for (rb = 0 ; rb < 1024 ; ++rb)
      {
      		pwmWrite (1, rb) ;
		//printf("%04d  %04d  %04d\n",rb,gb,bb);
      		delay (1) ;
    	}

    digitalWrite(0,0);
    digitalWrite(2,1);
    for (rb = 1023 ; rb >= 0 ; --rb)
    {
      pwmWrite (1, rb) ;
      delay (1) ;
    }
    digitalWrite(0,1);
    digitalWrite(2,0);
  }

  return 0 ;
}
