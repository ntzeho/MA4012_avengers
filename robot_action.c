void reset_impt_variables() {
	switch(robot_state){
		case BALL_SEARCH_FIRST_BALL:
			break;

		case BALL_COLLECTED_NO_ROBOT:
			ball_search_first_ball = false;
			boundary_ball_count = 0;
			break;

		case LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL:
		case BALL_DETECTED:
			ball_search_first_ball = false;
			robot_home_turn_to_north = 0;
			clearTimer(T3);
			break;

		case BALL_SEARCH_NO_ROBOT:
			if (ball_search_time > 3000) {
				boundary_ball_count = 0;
			}
			ball_search_first_ball = false;
			robot_home_turn_to_north = 0;
			clearTimer(T3);
			break;

		default:
			ball_search_first_ball = false;
			robot_home_turn_to_north = 0;
			boundary_ball_count = 0;
			clearTimer(T3);
	}
}

task action() {
	while (true) {
		//add in all possible combinations of sensor values and robot state values to determine corresponding robot action
		switch(robot_state) {
			case BALL_SEARCH_FIRST_BALL:
				writeDebugStreamLine("BALL_SEARCH_FIRST_BALL");
				executed_robot_state = BALL_SEARCH_FIRST_BALL;
				// motor [ball_in_motor] = 0;
				turn(-1, DEFAULT_MOTOR_TURNING_SPEED);
				previous_executed_robot_state = BALL_SEARCH_FIRST_BALL;
				break;

			case BALL_SEARCH_NO_ROBOT:
				writeDebugStreamLine("BALL_SEARCH_NO_ROBOT");
				if (previous_executed_robot_state != BALL_SEARCH_NO_ROBOT) {clearTimer(T4);}
				reset_impt_variables();
				executed_robot_state = BALL_SEARCH_NO_ROBOT;
				// motor [ball_in_motor] = 0;
				ball_scanning();
				previous_executed_robot_state = BALL_SEARCH_NO_ROBOT;
				ball_search_time = time1[T4];
				break;

			case BALL_DETECTED: //drive towards ball
				writeDebugStreamLine("BALL_DETECTED");
				reset_impt_variables();
				executed_robot_state = BALL_DETECTED;
				/*
				if (previous_executed_robot_state != robot_state){
					stop_movement();
					turn(1,DEFAULT_MOTOR_TURNING_SPEED);
					sleep(50);
					stop_movement();}*/

				motor [ball_in_motor] = -DEFAULT_BALL_MOTOR_SPEED;
				// only right side detected and left and center not detected
				if (distance_ball_front_right < ROBOT_BALL_DISTANCE_THRESHOLD && distance_ball_front_left > ROBOT_BALL_DISTANCE_THRESHOLD){ //distance_ball_front_center > ROBOT_BALL_DISTANCE_THRESHOLD
					drive_left(1,SLOW_MOTOR_DRIVING_SPEED);
					writeDebugStreamLine("Veer Left");
				} // only left side detected and right and center not detected
				else if  (distance_ball_front_right > ROBOT_BALL_DISTANCE_THRESHOLD && distance_ball_front_left < ROBOT_BALL_DISTANCE_THRESHOLD){
					drive_right(1,SLOW_MOTOR_DRIVING_SPEED);
					writeDebugStreamLine("Veer Right");
				}
				else {
					drive(1, SLOW_MOTOR_DRIVING_SPEED);
					writeDebugStreamLine("Straight");
				}

				// collect_ball();
				previous_executed_robot_state = BALL_DETECTED;
				break;

			// case BALL_DETECTED_COLLECT_BALL: //drive slower towards ball, start spinning ball_in_motor as close enough to ball
			// 	executed_robot_state = BALL_DETECTED_COLLECT_BALL;
			// 	motor [ball_in_motor] = -DEFAULT_BALL_MOTOR_SPEED;
			// 	collect_ball();
			// 	previous_executed_robot_state = BALL_DETECTED_COLLECT_BALL;
			// 	break;

			case HOME: //both bumper switches pressed, ball in robot and not back robot, orientation NORTH means deposit ball
				writeDebugStreamLine("HOME");
				reset_impt_variables();
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
				writeDebugStreamLine("BALL_COLLECTED_NO_ROBOT");
				reset_impt_variables();
				if (!ball_collected) {
					// motor [ball_out_motor] = -DEFAULT_BALL_MOTOR_SPEED;
					// sleep(TIME_TO_LOCK_BALL); //lock the collected ball in place
					// motor [ball_out_motor] = 0;
					motor [ball_in_motor] = DEFAULT_BALL_MOTOR_SPEED;
					sleep(TIME_TO_SPIT_BALL); //spin the ball in motor in the opp direction to kick out any extra balls
					motor [ball_in_motor] = 0;
					ball_collected = true;
					clearTimer(T3);
				}
				/*
				if (previous_executed_robot_state != BALL_COLLECTED_NO_ROBOT){ //only stop when the prev executed robot state is not the same
					motor [ball_in_motor] = 0;
					stop_movement();
				} */
				executed_robot_state = BALL_COLLECTED_NO_ROBOT;
				is_turning = true;
				turn_to_north_home();
				is_turning = false;
				/*
				if (robot_home_turn_to_north == 0) {
					clearTimer(T3);
					is_turning = true;
					turn_to_north_home();
					is_turning = false;
				}
				else if (robot_home_turn_to_north >= 1 && robot_home_turn_to_north <= 5) {
					is_turning = true;
					turn_to_north_home();
					is_turning = false;
				}
				*/

				//motor [ball_in_motor] = 0;
				if (executed_robot_state == robot_state) {drive(-1, DEFAULT_MOTOR_HOME_DRIVING_SPEED);}
				previous_executed_robot_state = BALL_COLLECTED_NO_ROBOT;
				break;

			case ROBOT_FRONT_DETECTED_BALL_IN: //robot collected ball but robot in front, reverse away first
				writeDebugStreamLine("ROBOT_FRONT_DETECTED_BALL_IN");
				reset_impt_variables();
				executed_robot_state = ROBOT_FRONT_DETECTED_BALL_IN;
				ball_collected = true;
				motor [ball_in_motor] = 0;
				drive(-1, DEFAULT_MOTOR_DRIVING_SPEED);
				previous_executed_robot_state = ROBOT_FRONT_DETECTED_BALL_IN;
				break;

			case ROBOT_FRONT_DETECTED_BALL_OUT: //robot finding ball but robot in front, reverse slightly and turn 20 degrees
				writeDebugStreamLine("ROBOT_FRONT_DETECTED_BALL_OUT");
				reset_impt_variables();
				executed_robot_state = ROBOT_FRONT_DETECTED_BALL_OUT;
				//motor [ball_in_motor] = 0;
				//TODO ADD CODE HERE
				drive_distance(-1, 30);
				//end of added code
				previous_executed_robot_state = ROBOT_FRONT_DETECTED_BALL_OUT;
				break;

			case ROBOT_REAR_DETECTED_BALL_IN: //robot collected ball but robot behind, move foward first, turn 90 degrees, move back a bit
				writeDebugStreamLine("ROBOT_REAR_DETECTED_BALL_IN");
				reset_impt_variables();
				executed_robot_state = ROBOT_REAR_DETECTED_BALL_IN;
				ball_collected = true;

				drive_distance_robot_rear();
				clearTimer(T3);
				previous_executed_robot_state = ROBOT_REAR_DETECTED_BALL_IN;
				break;

			case LINE_SENSOR_DETECTED_BALL_COLLECTED:
				writeDebugStreamLine("LINE_SENSOR_DETECTED_BALL_COLLECTED");
				reset_impt_variables();
				executed_robot_state = LINE_SENSOR_DETECTED_BALL_COLLECTED;
				react_to_line_sensors_homing();
				previous_executed_robot_state = LINE_SENSOR_DETECTED_BALL_COLLECTED;

			case LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL:
				writeDebugStreamLine("LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL");
				reset_impt_variables();
				executed_robot_state = LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL;
				react_to_line_sensors_collect_ball();
				previous_executed_robot_state = LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL;
				break;

			case LINE_SENSOR_DETECTED:
				writeDebugStreamLine("LINE_SENSOR_DETECTED");
				reset_impt_variables();
				executed_robot_state = LINE_SENSOR_DETECTED;
				react_to_line_sensors();
				previous_executed_robot_state = LINE_SENSOR_DETECTED;
				break;

			default:
				writeDebugStreamLine("default");
				reset_impt_variables();
				motor [ball_in_motor] = 0;
				stop_movement();
				break;
		}

	}
}
