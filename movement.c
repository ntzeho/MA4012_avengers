void drive(int direction, int speed) {
    motor [left_motor] = speed * direction;
    motor [right_motor] = speed * direction;
}

void turn(int direction, int speed) {
	motor [left_motor] = speed * direction;
	motor [right_motor] = -speed * direction;
}

void stop_movement() {
    motor [left_motor] = 0;
    motor [right_motor] = 0;
    motor [ball_in_motor] = 0;
}

void move_field() { //move to just over halfway point to begin searching for balls
    if (time10[T1] < 12000) { //movement when total elapsed time under 2mins
        drive(1, 30);
        sleep(2000);
    } else { //movement when only 1 min left on clock
        drive(1, 30);
        sleep(1000);
    }
    
    stop_movement();
}

void collect_ball() {
    motor [ball_in_motor] = 60;
    drive(1,15);
}

void deposit_ball() {
    motor [ball_out_motor] = 60;
    sleep(3000);
    motor [ball_out_motor] = 0;
    sleep(10);
}
