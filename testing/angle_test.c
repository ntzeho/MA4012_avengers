#pragma config(Sensor, in1,    dist_long0,     sensorAnalog)
#pragma config(Sensor, in2,    dist_long1,     sensorAnalog)
#pragma config(Sensor, in3,    dist_long2,     sensorAnalog)
#pragma config(Sensor, in5,    ,               sensorAnalog)
#pragma config(Sensor, dgtl1,  compass_west,   sensorDigitalIn)
#pragma config(Sensor, dgtl2,  compass_south,  sensorDigitalIn)
#pragma config(Sensor, dgtl3,  compass_east,   sensorDigitalIn)
#pragma config(Sensor, dgtl4,  compass_north,  sensorDigitalIn)
#pragma config(Sensor, dgtl5,  on_switch,      sensorTouch)
#pragma config(Sensor, dgtl6,  line_FL,        sensorDigitalIn)
#pragma config(Sensor, dgtl7,  line_FR,        sensorDigitalIn)
#pragma config(Sensor, dgtl8,  line_BL,        sensorDigitalIn)
#pragma config(Sensor, dgtl9,  line_BR,        sensorDigitalIn)
#pragma config(Sensor, dgtl10, ball_switch,    sensorTouch)
#pragma config(Sensor, dgtl11, bumper_L,       sensorTouch)
#pragma config(Sensor, dgtl12, bumper_R,       sensorTouch)
#pragma config(Motor,  port2,           left_motor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           ball_out_motor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           ball_in_motor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           right_motor,   tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

short time_taken_to_rotate_360_degrees;
char start_position;
short ball_count = 0;

#include "compass.c"
#include "movement.c"

void wait_for_on();
task full_stop();
task detection();
task action();

//-----------end of global functions/tasks-----------

task action() {
	while (robot_orientation != NORTH) {turn(1,60);}
	//else {
	stop_movement();
	sleep(1000);
	clearTimer(T1);
	turn(-1,60);
	sleep(1000);
	while (robot_orientation != NORTH) {}
	time_taken_to_rotate_360_degrees = time1[T1];
	sleep(100);
	stop_movement();
	//}
	/*
	if (robot_orientation != NORTH) {turn(1,30);}
	else {
		stop_movement();
		sleep(1000);
		clearTimer(T1);
		turn(1,30);
		while (robot_orientation != EAST) {}
		time_taken_to_rotate_90_degrees = time1[T1];
		sleep(100);
		stop_movement();
	}

	if (robot_orientation != NORTH) {turn(1,30);}
	else {
		stop_movement();
		sleep(1000);
		clearTimer(T1);
		turn(1,30);
		while (robot_orientation != SOUTHEAST) {}
		time_taken_to_rotate_135_degrees = time1[T1];
		sleep(100);
		stop_movement();
	}

	if (robot_orientation != NORTH) {turn(1,30);}
	else {
		stop_movement();
		sleep(1000);
		clearTimer(T1);
		turn(1,30);
		while (robot_orientation != SOUTH) {}
		time_taken_to_rotate_180_degrees = time1[T1];
		sleep(100);
		stop_movement();

	}
	*/
}

task detection() {
	while (true) {
		get_direction();
	}
}

task full_stop() { // stop all tasks and movements except for emergency_stop and main
	while (SensorValue [on_switch] == 0) {/* Nothing is executed when limit switch isn't pressed to off robot */}

	stopTask(detection);
	stopTask(action);
	stop_movement();
	motor [ball_in_motor] = 0;
	motor [ball_out_motor] = 0;

	wait_for_on();
}

void wait_for_on() {
	while (SensorValue [on_switch] == 0) {/* Nothing is executed when limit switch isn't pressed */}
	clearTimer(T1);
	startTask(detection);
	startTask(action);
	startTask(full_stop);
}

task main() {
	wait_for_on();
	while (true) {/* Loop ensures that main task is not terminated */}
}
