

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
            while (robot_orientation != NORTH && executed_robot_state == robot_state) {}
            stop_movement();
            break;

        //turn right
        case SOUTHWEST:
        case WEST:
        case NORTHWEST:
            turn(1, DEFAULT_MOTOR_TURNING_SPEED);
            while (robot_orientation != NORTH && executed_robot_state == robot_state) {}
            stop_movement();
            break;
    }
}

void reorient(robotOrientation target_orientation) {
    switch (target_orientation) {
        case NORTH:
            turn_to_north();
            break;

        case SOUTH:
            break;

        case EAST:
            break;

        case WEST:
            break;
    }
}

void ball_scanning() {
    turn_angle(-1, 360);
    if (executed_robot_state == robot_state) {
        drive(1, DEFAULT_MOTOR_DRIVING_SPEED);
        sleep_with_state_detection(1000); //amount of time taken to travel 60cm
    }
    stop_movement();
}
