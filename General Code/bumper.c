#pragma config(Sensor, dgtl6, button, sensorDigitalIn) // bumper
#pragma config(Motor, port1, leftmotor, tmotorVex393_HBridge, openloop)     // motor 1
#pragma config(Motor, port10, rightmotor， tmotorVex393_HBridge, openloop)  // motor 2
task main(){
    while (1==1){
        if (SensorValue(button)==1){
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