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

void move_field() { //move to just over halfway point to begin searching for balls
    if (time10[T1] < 12000 && ball_count == 0) { //movement when total elapsed time under 2mins
        drive(1, 127);
        sleep(3000);
    } else if (ball_count == 1) {
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
    } else { //movement when only 1 min left on clock
        drive(1, 30);
        sleep(1000);
    }
    
    stop_movement();
}

void collect_ball() {
    motor [ball_in_motor] = 127;
    drive(1,15);
}

void deposit_ball() {
    motor [ball_out_motor] = -127;
    sleep(2000);
    motor [ball_out_motor] = 0;
    sleep(10);
}
