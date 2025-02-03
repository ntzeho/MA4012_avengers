#pragma config(Sensor, in3, light_sensor, sensorAnalog) // light sensor
#pragma config(Sensor, dgtis, limitswitch, sensorNone)  // limit switch
#pragma config(Sensor, dgtl6, button, sensorDigitalIn)  // bumper
#pragma config(Motor, port1, leftmotor, tmotorVex393_HBridge, openloop)     // motor 1
#pragma config(Motor, port10, rightmotor， tmotorVex393_HBridge, openloop)  // motor 2

task main(){
    while (1==1){
        // value is btw 0 to 500
        if (SensorValue (light_sensor) >= 350){
            // 0 for min speed, 127 for max speed
            motor[leftmotor] = 127;
            motor[rightmotor] = 127;
        }
        else{
            // 0 for min speed, 127 for max speed
            motor[leftmotor] = 0;
            motor[rightmotor] = 0;
        }
    }
}