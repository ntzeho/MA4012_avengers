void sleep_with_state_detection(short sleep_time) {
    short i = 0;
    while (executed_robot_state == robot_state && i < sleep_time) {
  	    sleep(1);
        i++;
	}
}

void drive(short direction, short speed) {
    motor [left_motor] = -speed * direction;
    motor [right_motor] = speed * direction;
}

void turn(short direction, short speed) {
    //assuming 1 is forward and -1 is backward:
    //direction = 1 means turn right, direction = -1 means turn left
	motor [left_motor] = -speed * direction;
	motor [right_motor] = -speed * direction;
}

void stop_movement() {
    motor [left_motor] = 0;
    motor [right_motor] = 0;
    sleep(1);
}

void turn_angle(short direction, short angle) {
    //assuming 1 is forward and -1 is backward:
    //direction = 1 means turn right, direction = -1 means turn left
    turn(direction, DEFAULT_MOTOR_TURNING_SPEED);
    sleep_with_state_detection(MS_PER_DEGREE * angle);
    stop_movement();
}

void move_field() { //move to just over halfway point to begin searching for balls
    switch (ball_count) {
        case 0:
            drive(1, DEFAULT_MOTOR_DRIVING_SPEED);
            sleep(START_MOVE_FIELD_TIME);
            break;
        
        case 1:
            //movement to centre sector with appropriate turning depending on start_position value
            drive(1, DEFAULT_MOTOR_DRIVING_SPEED);
            sleep(START_MOVE_FIELD_TIME);
            switch (start_position) {
                case 'L':
                    //do xxx
                    break;
                case 'R':
                    //do yyy
                    break;
            }
            break;
        
        default:
            if (time10[T1] < 12000) { //movement when total elapsed time under 2mins
                drive(1, DEFAULT_MOTOR_DRIVING_SPEED);
                sleep(START_MOVE_FIELD_TIME);
            } else { //movement when 1min or less left on clock
                drive(1, DEFAULT_MOTOR_DRIVING_SPEED);
                sleep(END_MOVE_FIELD_TIME);
            }
            break;
    }
    
    stop_movement();
}

void collect_ball() {
    motor [ball_in_motor] = -DEFAULT_BALL_MOTOR_SPEED;
    drive(1, SLOW_MOTOR_DRIVING_SPEED);
}

void deposit_ball() {
    motor [ball_out_motor] = -DEFAULT_BALL_MOTOR_SPEED;
    sleep(BALL_OUT_MOTOR_SLEEP_TIME);
    motor [ball_out_motor] = 0;
    sleep(1);
}
