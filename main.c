#pragma config(Sensor, in2,    dist_robot_front, sensorAnalog)
#pragma config(Sensor, in3,    dist_ball_front, sensorAnalog)
#pragma config(Sensor, in6,    dist_robot_rear, sensorAnalog)
#pragma config(Sensor, in8,    dist_ball_rejection, sensorAnalog)
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

short cycles = 0;            //detect number of times on-off switch was pressed while robot is on
short ball_count = 0;        //number of balls collected by robot
short boundary_ball_count = 0; //number of tries to pick up ball at boundary
char start_position = 'R';   //starting position of robot, default at right side
bool ball_collected = false; //true when ball is collected

//-----debugging variables
bool is_turning = false;
bool is_moving_after_first_ball = false;
//-----end of debugging variables

#include "constants.c"
#include "sensor_detection.c"
#include "robot_state.c"
#include "movement.c"
#include "sensor_action.c"

void wait_for_on();

task action() {
	while (true) {
		//add in all possible combinations of sensor values and robot state values to determine corresponding robot action
		switch(robot_state) {
			case BALL_SEARCH_FIRST_BALL:
				executed_robot_state = BALL_SEARCH_FIRST_BALL;
				// motor [ball_in_motor] = 0;
				turn(-1, DEFAULT_MOTOR_TURNING_SPEED);
				previous_executed_robot_state = BALL_SEARCH_FIRST_BALL;
				break;

			case BALL_SEARCH_NO_ROBOT:
				executed_robot_state = BALL_SEARCH_NO_ROBOT;
				// motor [ball_in_motor] = 0;
				ball_scanning();
				previous_executed_robot_state = BALL_SEARCH_NO_ROBOT;
				break;
			
			case BALL_DETECTED: //drive towards ball
				executed_robot_state = BALL_DETECTED;
				if (previous_executed_robot_state != robot_state){
					stop_movement();
					turn(1,DEFAULT_MOTOR_TURNING_SPEED);
					sleep(50);
					stop_movement();}
				motor [ball_in_motor] = 0;
				drive(1, DEFAULT_MOTOR_DRIVING_SPEED);
				previous_executed_robot_state = BALL_DETECTED;
				break;

			case BALL_DETECTED_COLLECT_BALL: //drive slower towards ball, start spinning ball_in_motor as close enough to ball
				executed_robot_state = BALL_DETECTED_COLLECT_BALL;
				collect_ball();
				previous_executed_robot_state = BALL_DETECTED_COLLECT_BALL;
				break;

			case HOME: //both bumper switches pressed, ball in robot and not back robot, orientation NORTH means deposit ball
				executed_robot_state = HOME;
				stop_movement();
				deposit_ball();
				ball_collected = false;
				ball_count++;
				is_moving_after_first_ball = true;
				move_field();
				is_moving_after_first_ball = false;
				previous_executed_robot_state = HOME;
				break;

			case BALL_COLLECTED_NO_ROBOT: //robot collected ball and no nearby robots
				if (previous_executed_robot_state != BALL_COLLECTED_NO_ROBOT){ //only stop when the prev executed robot state is not the same
					motor [ball_in_motor] = 0;
					stop_movement();
				}
				executed_robot_state = BALL_COLLECTED_NO_ROBOT;
				ball_collected = true;
				is_turning = true;
				turn_to_north();
				is_turning = false;
				if (executed_robot_state == robot_state) {drive(-1, DEFAULT_MOTOR_HOME_DRIVING_SPEED);}
				previous_executed_robot_state = BALL_COLLECTED_NO_ROBOT;
				break;

			case ROBOT_FRONT_DETECTED_BALL_IN: //robot collected ball but robot in front, reverse away first
				executed_robot_state = ROBOT_FRONT_DETECTED_BALL_IN;
				ball_collected = true;
				motor [ball_in_motor] = 0;
				drive(-1, DEFAULT_MOTOR_DRIVING_SPEED);
				previous_executed_robot_state = ROBOT_FRONT_DETECTED_BALL_IN;
				break;

			case ROBOT_FRONT_DETECTED_BALL_OUT: //robot finding ball but robot in front, reverse slightly and turn 20 degrees
				executed_robot_state = ROBOT_FRONT_DETECTED_BALL_OUT;
				motor [ball_in_motor] = 0;
				//TODO ADD CODE HERE
				drive_distance(-1, 30);
				//end of added code
				previous_executed_robot_state = ROBOT_FRONT_DETECTED_BALL_OUT;
				break;

			case ROBOT_REAR_DETECTED_BALL_IN: //robot collected ball but robot behind, move foward first, turn 90 degrees, move back a bit
				executed_robot_state = ROBOT_REAR_DETECTED_BALL_IN;
				ball_collected = true;
				motor [ball_in_motor] = 0;
				//TODO ADD CODE HERE
				drive_distance(1, 30);
				//end of added code
				previous_executed_robot_state = ROBOT_REAR_DETECTED_BALL_IN;
				break;

			case LINE_SENSOR_DETECTED_BALL_COLLECTED:
				executed_robot_state = LINE_SENSOR_DETECTED_BALL_COLLECTED;
				react_to_line_sensors_homing();
				previous_executed_robot_state = LINE_SENSOR_DETECTED_BALL_COLLECTED;

			case LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL:
				executed_robot_state = LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL;
				react_to_line_sensors_collect_ball();
				previous_executed_robot_state = LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL;
				break;

			case LINE_SENSOR_DETECTED:
				executed_robot_state = LINE_SENSOR_DETECTED;
				react_to_line_sensors();
				previous_executed_robot_state = LINE_SENSOR_DETECTED;
				break;

			default:
				motor [ball_in_motor] = 0;
				stop_movement();
				break;
		}

	}
}

task detection() {
	while (true) {
		distance_calculator();
		get_direction();
		get_line_sensor_state();
	}
}

task robot_state_manager() {
	while (true) {robot_state_machine();}
}

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
