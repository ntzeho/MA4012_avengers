#pragma config(Sensor, in1,    dist_long0,     sensorAnalog)
#pragma config(Sensor, in2,    dist_long1,     sensorAnalog)
#pragma config(Sensor, in3,    dist_long2,     sensorAnalog)
#pragma config(Sensor, in4,    dist_short,     sensorAnalog)
#pragma config(Sensor, in5,    on_switch,      sensorAnalog)
#pragma config(Sensor, dgtl1,  compass_west,   sensorDigitalIn)
#pragma config(Sensor, dgtl2,  compass_south,  sensorDigitalIn)
#pragma config(Sensor, dgtl3,  compass_east,   sensorDigitalIn)
#pragma config(Sensor, dgtl4,  compass_north,  sensorDigitalIn)
#pragma config(Sensor, dgtl5,  line_FL,        sensorDigitalIn)
#pragma config(Sensor, dgtl6,  line_FR,        sensorDigitalIn)
#pragma config(Sensor, dgtl7,  line_BL,        sensorDigitalIn)
#pragma config(Sensor, dgtl8,  line_BR,        sensorDigitalIn)
#pragma config(Sensor, dgtl9,  ball_switch,    sensorTouch)
#pragma config(Sensor, dgtl10, bumper_L,       sensorTouch)
#pragma config(Sensor, dgtl11, bumper_R,       sensorTouch)
#pragma config(Sensor, dgtl12, compass_supply, sensorDigitalOut)
#pragma config(Motor,  port2,           left_motor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           ball_out_motor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           ball_in_motor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           right_motor,   tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
dist_long0 - front robot
dist_long1 - front ball
dist_long2 - back robot

line sensor
- 4 corners of robot

distance Sensors
- ball detection (ball diameter 6.5cm)
- detect robot (on top)
- if ball collected [short 4-30cm]
- one at back to know distance gg back (must be sufficiently high up)

- 2Y0A21 F 6Z * 2 (10 to 80cm)
- 2Y0A21 F 09 * 1 (10 to 80cm)
- 0A41SK * 1 (4 to 30cm)

10 to 20cm0
*/

/*
Motors (10)
- driver * 2
- ball_in * 1
- ball_out * 1

Digital inputs (12)
- line * 4
- limit switch * 2 for bumper, * 1 for ball switch, total 3
- compass * 5

Analog inputs (8)
- dist * 3
- * 1 for on-off
*/

#include "compass.c"
#include "distance_sensors.c"
#include "line_sensors.c"
#include "movement.c"

short cycles = 0; // detect number of times on-off switch was pressed while robot is on

short test;
byte left;
byte right;
byte front;
byte back;

void wait_for_on();
void stop_tasks();

task begin();
task full_stop();
task detection();
task action();

//-----------end of global functions/tasks-----------

task action() {
	while (true) {
		//add in all possible combinations of sensor values and robot state values to determine corresponding robot action
		if (distance_long1 < 45) {
			drive(1, 30);
			//motor [ball_in_motor] = 0;
			if (distance_long1 < 20 && SensorValue [ball_switch] == 0 && distance_long0 > 20) { //to change to same indentation lvl as prev
				collect_ball();
			}
		} else if (SensorValue [ball_switch] == 1) { //collected ball
			stop_movement();
			//add code to change state to return to base
		} else if (SensorValue [bumper_L] == 1 && SensorValue [bumper_R] == 1 && distance_long2 >= 15 && SensorValue [ball_switch] == 1) {
			stop_movement();
			deposit_ball();
			move_field();
		}	else {
			stop_movement();
		}
	}
}

task detection() {
	while (true) {
		get_direction();
		distance_calculator();

		left = !SensorValue[line_FL] << 0;
	 	right = !SensorValue[line_FR] << 1;
		front = !SensorValue[line_BL] << 2;
		back = !SensorValue[line_BR] << 3;
		test = back | front | left | right;
		react_to_sensors(test);
	}
}

task begin() {
	if (cycles == 1) {clearTimer(T1);}

	move_field();
	startTask(detection);
	startTask(action);

	clearTimer(T2);
}

task full_stop() {
	while (SensorValue [on_switch] == 0) {/* Nothing is executed when limit switch isn't pressed to off robot */}
	stop_tasks();
	wait_for_on();
}

void wait_for_on() {
	//while (SensorValue [on_switch] == 0) {/* Nothing is executed when limit switch isn't pressed */}
	startTask(begin);
	cycles++;
	//startTask(full_stop);
}

void stop_tasks() { //stop all tasks and movements except for emergency_stop and main
	stopTask(detection);
	stopTask(action);
	stop_movement();
}

task main() {
	wait_for_on();
	while (true) {/* Loop ensures that main task is not terminated */}
}


// temp
void robot_state_machine() {
    if (distance_long0 < 15) {
        detected_state = ROBOT_FRONT_DETECTED;
    }
    else if (distance_long1 < 15) {
        detected_state = ROBOT_REAR_DETECTED;
    }
    else if (((distance_long0 > 15)) && (distance_long2 < 40)) {
        detected_state = BALL_DETECTED;
        }
    else {
        detected_state = BLANK;
    }

    if (detected_state == previous_detected_state) {
        state_counter++;
    }
    else {
        state_counter = 1;
    }

    previous_detected_state = detected_state;

    if (state_counter >= 5 && robot_state != detected_state) {
        robot_state = detected_state;

        switch(robot_state) {
            case BALL_DETECTED:
                break;
            case ROBOT_FRONT_DETECTED:
                break;
            case ROBOT_REAR_DETECTED:
                break;
            case BLANK:
                break;
        }
        state_counter = 1;
    }
}