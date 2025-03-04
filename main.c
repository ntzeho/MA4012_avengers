#pragma config(Sensor, in1,    dist_long0,     sensorAnalog)
#pragma config(Sensor, in2,    dist_long1,     sensorAnalog)
#pragma config(Sensor, in3,    dist_long2,     sensorAnalog)
#pragma config(Sensor, in4,    dist_short,     sensorAnalog)
#pragma config(Sensor, in5,    line_FL,        sensorAnalog)
#pragma config(Sensor, in6,    line_FR,        sensorAnalog)
#pragma config(Sensor, in7,    line_BL,        sensorAnalog)
#pragma config(Sensor, in8,    line_BR,        sensorAnalog)
#pragma config(Sensor, dgtl1,  encoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  ball_switch,    sensorTouch)
#pragma config(Sensor, dgtl10, bumper_L,       sensorTouch)
#pragma config(Sensor, dgtl11, bumper_R,       sensorTouch)
#pragma config(Sensor, dgtl12, on_switch,      sensorTouch)
#pragma config(Motor,  port2,           left_motor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           ball_out_motor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           ball_in_motor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           right_motor,   tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* SENSOR VARIABLE
dist_long0 - front robot
dist_long1 - front ball
dist_long2 - back robot
*/

/*
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

10 to 20cm


limit switch
- 2/3 for back?
if (limitVal1 == 1 && limitVal2 ==1) {return true}

- 1 for redundacy for ball catching

// check back distance sensor got nth
// then deposit ball
// then move forward to disengage limit switches


driver motors
- left right is one forward one back (scanning and turning)
- forward
- backward

catcher motor
- continuous motor

*/

/*
Motors (10)
- driver * 2
- grab * 1

Digital inputs (12)
- limit switch * 2 for bumper, * 1 for ball switch, total 3
- limit switch for starting competition * 1
- encoder * 2 (encoder need 2 ports)
- compass * 1 (or 5??)

Analog inputs (8)
- dist * 4
- line * 4

*/

/*define global parameters



*/

#include "distance_sensors.c"

float bumper_hit;

void wait_for_on();
void drive(int direction, int speed);
void move_field();
void turn(int direction, int speed);
void get_direction();
void stop_movement();
void stop_tasks();

task begin();
task detection();
task detect_reached_base();
task full_stop();

//-----------end of global functions/tasks

void drive(int direction, int speed) {
	motor [left_motor] = speed * direction;
	motor [right_motor] = speed * direction;
}

void move_field() { //move to just over halfway point to begin searching for balls

}

void turn(int direction, int speed) {
	motor [left_motor] = speed * direction;
	motor [right_motor] = -speed * direction;
}

void stop_movement() {
	motor [left_motor] = 0;
	motor [right_motor] = 0;
}

void get_direction() {

}

void stop_tasks() { //stop all tasks and movements except for emergency_stop and main
	stopTask(begin);
	stopTask(detection);
	stopTask(detect_reached_base);
	stop_movement();
}

task detection() {
	while (true) { // detect ball
		distance_calculator();
		if (distance_long1 < 45) {
			drive(1, 30);
			//motor [ball_in_motor] = 0;
			if (distance_long1 < 20 && SensorValue [ball_switch] == 0 && distance_long0 > 20) {
				motor [ball_in_motor] = 120;
				drive(1, 15);
			}
		} else if (SensorValue [ball_switch] == 1) { //collected ball
			stop_movement();
			motor [ball_in_motor] = 0;
		}else {
			stop_movement();
			//motor [ball_in_motor] = 0;
		}
	}
}

task test_short_sensor() {
	while (true) {
		float voltage_short = (SensorValue [dist_short]) * (5.0 / 4096.0);
		float distance_short = pow(2.7818281828, 2.507) * pow(voltage_short , -1.123);
		while (distance_short < 30) {
			drive(1, 30);
			if (distance_short < 4) {
				motor [ball_in_motor] = 30;
				break;
			}
		}
	}
}

task detect_reached_base() {
	//deposit ball
	while (true) {
		bumper_hit = 0;
		if (SensorValue [bumper_L] == 1 && SensorValue [bumper_R] == 1 && distance_long2 >= 15 && bumper_hit == 0) {
			stop_movement();
			bumper_hit = 1;
			motor [ball_out_motor] = 30;
			sleep(3000);
			motor [ball_out_motor] = 0;
			sleep(1000);
			//add code here to move forward
		}
	}
}

task begin() {
	//move_field();
	startTask(detection);
	startTask(detect_reached_base);
}

task full_stop() {
	while (true) {
		if (SensorValue [on_switch] == 1) {
			stop_tasks();
			break;
		}
	}
	wait_for_on();
}

void wait_for_on() {
	//while (SensorValue [on_switch] == 0) {/* Nothing is executed when limit switch isn't pressed */}
	startTask(begin);
	//startTask(full_stop);
}

task main() {
	wait_for_on();
	while (true) {}
}
