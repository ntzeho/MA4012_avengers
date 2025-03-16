#pragma config(Sensor, dgtis, limitswitch, sensorNone) // limit switch
#pragma config(Sensor, dgtl3,  limitSwitch1,    sensorTouch) // limitswtich 1
#pragma config(Sensor, dgtl4,  limitSwitch2,    sensorTouch) // limitswitch 2
#pragma config(Sensor, dgtl4,  limitSwitch3,    sensorTouch) // limitswitch 3
#pragma config(Sensor, dgtl6, button, sensorDigitalIn) // bumper
#pragma config(Motor, port1, leftmotor, tmotorVex393_HBridge, openloop)     // motor 1
#pragma config(Motor, port10, rightmotor， tmotorVex393_HBridge, openloop)  // motor 2

// task main(){
//     while (1==1){
//         // "||" means or
//         if (SensorValue(button)==1 || SensorValue (limitswitch) == 1){
//             // 0 for min speed, 127 for max speed
//             motor[leftmotor] = 127;
//             motor[rightmotor] = 127;
//         }
//         else{
//             // 0 for min speed, 127 for max speed
//             motor[leftmotor] = 0;
//             motor[rightmotor] = 0;
//         }
//     }
// }

/*
IDEA:
limit switch
- 2 for back
if (limitVal1 == 1 && limitVal2 ==1) {return true}

- 1 for redundacy for ball catching

check back distance sensor got nth
then deposit ball
then move forward to disengage limit switches
*/

bool depositBall(){
    // check if both limit switch at the back are depressed
    if (limitSwitch1 == 1 && limitSwitch2 == 1) {
        // call function to check if top-rear distance sensor captures something (enemy robot)
        if (enemyDetected()){
            // ran into enemy robot with both limit switch detected
            // CALL EVASIVE MANEUVUER HERE, DONT ACTIVATE BALL DEPOSIT
            return false;
        }
        else{
            // top-rear distance sensor is clear, means we have reached the ball deposit area successfully
            // ACTIVATE BALL DEPOSIT MOVEMENT HERE (control the motor for release mechanism)
            // alternatviely, can return true and call depositBall function that works on depositing the ball
            return true;
        }
    }
    return false;   // both not fully triggered
}

bool ballCaptured(){
    // check if ball is successfully captured
    return (limitSwitch3 == 1)
}