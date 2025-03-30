void sleep_with_state_detection(short sleep_time) {
    clearTimer(T1);
    while (executed_robot_state == robot_state && time1[T1] < sleep_time) {}
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
}

void drive_distance(short direction, short distance) {
    //distance in cm
    drive(direction, DEFAULT_MOTOR_DRIVING_SPEED);
    switch (distance) {
        case 30:
            sleep_with_state_detection(TIME_TO_TRAVEL_30_CM);
            break;

        case 60:
            sleep_with_state_detection(TIME_TO_TRAVEL_60_CM);
            break;

        case END_MOVE_FIELD_DISTANCE:
            sleep_with_state_detection(END_MOVE_FIELD_TIME);
            break;

        case START_MOVE_FIELD_DISTANCE:
            sleep_with_state_detection(START_MOVE_FIELD_TIME);
            break;
    }
    stop_movement();
}

void drive_distance_fixed(short direction, short distance) {
    //distance in cm
    drive(direction, DEFAULT_MOTOR_DRIVING_SPEED);
    switch (distance) {
        case 10:
            sleep(TIME_TO_TRAVEL_10_CM);
            break;

        case 15:
            sleep(TIME_TO_TRAVEL_15_CM);
            break;
            
        case 30:
            sleep(TIME_TO_TRAVEL_30_CM);
            break;

        case 60:
            sleep(TIME_TO_TRAVEL_60_CM);
            break;

        case END_MOVE_FIELD_DISTANCE:
            sleep(END_MOVE_FIELD_TIME);
            break;

        case START_MOVE_FIELD_DISTANCE:
            sleep(START_MOVE_FIELD_TIME);
            break;
    }
    stop_movement();
}

void turn_to_north() {
    switch (robot_orientation) {
        case NORTH:
            break;
        
        //turn left
        case NORTHEAST:
        case EAST:
        case SOUTHEAST:
        case SOUTH:
            turn(-1, DEFAULT_MOTOR_TURNING_SPEED);
            while (robot_orientation != NORTH && executed_robot_state == robot_state && !line_sensor_state_check()) {}
            stop_movement();
            break;

        //turn right
        case SOUTHWEST:
        case WEST:
        case NORTHWEST:
            turn(1, DEFAULT_MOTOR_TURNING_SPEED);
            while (robot_orientation != NORTH && executed_robot_state == robot_state && !line_sensor_state_check()) {}
            stop_movement();
            break;
    }
}

void turn_to_east() {
    switch (robot_orientation) {
        case EAST:
            break;
        
        //turn left
        case SOUTHEAST:
        case SOUTH:
        case SOUTHWEST:
        case WEST:
            turn(-1, DEFAULT_MOTOR_TURNING_SPEED);
            while (robot_orientation != EAST && executed_robot_state == robot_state && !line_sensor_state_check()) {}
            stop_movement();
            break;

        //turn right
        case NORTHWEST:
        case NORTH:
        case NORTHEAST:
            turn(1, DEFAULT_MOTOR_TURNING_SPEED);
            while (robot_orientation != EAST && executed_robot_state == robot_state && !line_sensor_state_check()) {}
            stop_movement();
            break;
    }
}

void turn_to_south() {
    switch (robot_orientation) {
        case SOUTH:
            break;
        
        //turn left
        case SOUTHWEST:
        case WEST:
        case NORTHWEST:
        case NORTH:
            turn(-1, DEFAULT_MOTOR_TURNING_SPEED);
            while (robot_orientation != SOUTH && executed_robot_state == robot_state && !line_sensor_state_check()) {}
            stop_movement();
            break;

        //turn right
        case NORTHEAST:
        case EAST:
        case SOUTHEAST:
            turn(1, DEFAULT_MOTOR_TURNING_SPEED);
            while (robot_orientation != SOUTH && executed_robot_state == robot_state && !line_sensor_state_check()) {}
            stop_movement();
            break;
    }
}

void turn_to_west() {
    switch (robot_orientation) {
        case WEST:
            break;
        
        //turn left
        case NORTHWEST:
        case NORTH:
        case NORTHEAST:
        case EAST:
            turn(-1, DEFAULT_MOTOR_TURNING_SPEED);
            while (robot_orientation != WEST && executed_robot_state == robot_state && !line_sensor_state_check()) {}
            stop_movement();
            break;

        //turn right
        case SOUTHEAST:
        case SOUTH:
        case SOUTHWEST:
            turn(1, DEFAULT_MOTOR_TURNING_SPEED);
            while (robot_orientation != WEST && executed_robot_state == robot_state && !line_sensor_state_check()) {}
            stop_movement();
            break;
    }
}

void reorientate_R() {
    switch (robot_orientation) {
        case NORTHEAST:
            turn_to_east();
            break;

        case SOUTHEAST:
            turn_to_south();
            break;

        case SOUTHWEST:
            turn_to_west();
            break;

        case NORTHWEST:
            turn_to_north();
            break;
    }
}

void reorientate_L() {
    switch (robot_orientation) {
        case NORTHEAST:
            turn_to_north();
            break;

        case SOUTHEAST:
            turn_to_east();
            break;

        case SOUTHWEST:
            turn_to_south();
            break;

        case NORTHWEST:
            turn_to_west();
            break;
    }
}

void turn_90_degrees_R() {
    switch (robot_orientation) {
        case NORTH:
            turn_to_east();
            break;

        case EAST:
            turn_to_south();
            break;

        case SOUTH:
            turn_to_west();
            break;

        case WEST:
            turn_to_north();
            break;

        default:
            reorientate_R();
    }
}

void turn_90_degrees_L() {
    switch (robot_orientation) {
        case NORTH:
            turn_to_west();
            break;

        case EAST:
            turn_to_north();
            break;

        case SOUTH:
            turn_to_east();
            break;

        case WEST:
            turn_to_south();
            break;

        default:
            reorientate_L();
    }
}

void turn_180_degrees() {
    switch (robot_orientation) {
        case NORTH:
            turn_to_south();
            break;

        case EAST:
            turn_to_west();
            break;

        case SOUTH:
            turn_to_north();
            break;

        case WEST:
            turn_to_east();
            break;
    }
}

void turn_360_degrees() {
    robotOrientation turn_start_orientation = robot_orientation;
    turn(-1, DEFAULT_MOTOR_TURNING_SPEED);
    sleep_with_state_detection(1000);
    while (executed_robot_state == robot_state && turn_start_orientation != robot_orientation) {}
    stop_movement();
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
            drive_distance_fixed(1, START_MOVE_FIELD_DISTANCE);
            break;
        
        case 1:
            //movement to centre sector with appropriate turning depending on start_position value
            drive_distance_fixed(1, START_MOVE_FIELD_DISTANCE);
            if (start_position == 'L') {turn_90_degrees_R();}
            else {turn_90_degrees_L();}
            break;
        
        default:
            drive_distance_fixed(1, END_MOVE_FIELD_DISTANCE);
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
}

void ball_scanning() {
    drive_distance(1, 60);
    if(executed_robot_state == robot_state) {turn_360_degrees();}
    stop_movement();
}
