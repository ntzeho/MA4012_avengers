void drive(short direction, short speed) {
    motor [left_motor] = speed * direction;
    motor [right_motor] = speed * direction;
}

void turn(short direction, short speed) {
    //assuming 1 is forward and -1 is backward:
    //direction = 1 means turn right, direction = -1 means turn left
	motor [left_motor] = speed * direction;
	motor [right_motor] = -speed * direction;
}

void stop_movement() {
    motor [left_motor] = 0;
    motor [right_motor] = 0;
}

void turn_angle(short direction, short angle) {
    //assuming 1 is forward and -1 is backward:
    //direction = 1 means turn right, direction = -1 means turn left
    turn(direction, 30);
    const short milliseconds_per_degree = 1;
    sleep(milliseconds_per_degree * angle);
    stop_movement();
}

void turn_to_north() {
    switch (robot_orientation) {
        case NORTH:
            break;
        
        //turn left
        case NORTHEAST:
            turn(-1, 30);
            while (robot_orientation != NORTH) {}
            stop_movement();
            break;
        case EAST:
            turn(-1, 30);
            while (robot_orientation != NORTH) {}
            stop_movement();
            break;
        case SOUTHEAST:
            turn(-1, 30);
            while (robot_orientation != NORTH) {}
            stop_movement();
            break;
        case SOUTH:
            turn(-1, 30);
            while (robot_orientation != NORTH) {}
            stop_movement();
            break;

        //turn right
        case SOUTHWEST:
            turn(1, 30);
            while (robot_orientation != NORTH) {}
            stop_movement();
            break;
        case WEST:
            turn(1, 30);
            while (robot_orientation != NORTH) {}
            stop_movement();
            break;
        case NORTHWEST:
            turn(1, 30);
            while (robot_orientation != NORTH) {}
            stop_movement();
            break;
    }
}

void move_field() { //move to just over halfway point to begin searching for balls
    switch (ball_count) {
        case 0:
            drive(1, 127);
            sleep(3000);
            break;
        
        case 1:
            //movement to centre sector with appropriate turning depending on start_position value
            drive(1, 127);
            sleep(3000);
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
                drive(1, 127);
                sleep(3000);
            } else { //movement when 1min or less left on clock
                drive(1, 30);
                sleep(1000);
            }
            break;
    }
    
    stop_movement();
}

void collect_ball() {
    motor [ball_in_motor] = -127;
    drive(1,30);
}

void deposit_ball() {
    motor [ball_out_motor] = -127;
    sleep(2000);
    motor [ball_out_motor] = 0;
    sleep(1);
}
