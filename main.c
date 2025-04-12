#pragma config(Sensor, in2,    dist_ball_front_center, sensorAnalog)
#pragma config(Sensor, in3,    dist_ball_front_right, sensorAnalog)
#pragma config(Sensor, in6,    dist_robot_front, sensorAnalog)
#pragma config(Sensor, in8,    dist_ball_front_left, sensorAnalog)
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

short cycles = 0;                     //detect number of times on-off switch was pressed while robot is on
short ball_count = 0;                 //number of balls collected by robot
short boundary_ball_count = 0;        //number of tries to pick up ball at boundary
char start_position = 'R';            //starting position of robot, default at right side
bool ball_collected = false;          //true when ball is collected
short robot_home_turn_to_north = 0;   //no of times robot has made the turn to north
short robot_rear_detected_count = 0;  //no of times robot has detected rear robot when returning to base
short ball_search_time = 0;           //duration of robot staying in BALL_SEARCH_NO_ROBOT state
bool ball_search_first_ball = true;   //false when first ball search has been done once

//-----debugging variables
bool is_turning = false;
bool is_moving_after_first_ball = false;
bool is_turning_360 = false;
//-----end of debugging variables

#include "constants.c"
#include "sensor_detection.c"
#include "robot_state.c"
#include "movement.c"
#include "sensor_action.c"
#include "robot_action.c"

void wait_for_on();

task full_stop() { // stop all tasks and movements except for emergency_stop and main
	while (SensorValue [on_switch] == 0) {/* Nothing is executed when limit switch isn't pressed to off robot */}

	stopTask(detection);
	stopTask(action);
	stopTask(robot_state_manager);
	stop_movement();
	motor [ball_in_motor] = 0;
	motor [ball_out_motor] = 0;
	sleep(2000);
	wait_for_on();
}

void wait_for_on() {
	while (SensorValue [on_switch] == 0) {/* Nothing is executed when limit switch isn't pressed */}
	if (cycles == 0) {clearTimer(T1);}
	while (SensorValue [on_switch] == 1) {sleep(100);}
	cycles++;
	if (cycles == 1) {
		if (time1[T1] >= 2000) {start_position = 'L';} // robot start on left position when on switch held for at least 2s
		move_field(); //move field only if robot did not start again
	}
	startTask(detection);
	startTask(robot_state_manager);
	startTask(action);
	startTask(full_stop);
}

task main() {
	wait_for_on();
	while (true) {/* Loop ensures that main task is not terminated */}
}
