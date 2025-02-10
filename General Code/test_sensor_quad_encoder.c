#pragma config(Sensor, dgtl1,  encoder,        sensorQuadEncoder)
#pragma config(Motor,  port6,           grabmotor,     tmotorServoContinuousRotation, openLoop)


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
  wait1Msec(2000);                  // Wait 2000 milliseconds before continuing.

  int distance;                     // Create an integer variable 'distance' that will represent encoder counts.
  distance = 90;                   // 360 encoder counts is a full rotation of the axel.

  SensorValue[encoder] = 0;    /* Clear the encoders for    */

  while(SensorValue[encoder] < distance) // While the right encoder is less than distance:
  {
    motor[grabmotor] = 30;         /* Run both motors        */
  }

  motor[grabmotor] = 0;            /* Stop the motors once desired */
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
