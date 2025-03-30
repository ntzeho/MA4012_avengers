enum robotState {
    // line sensor
    LINE_SENSOR_DETECTED,
    LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL,

    // long dist sensors for robot
    ROBOT_FRONT_DETECTED_BALL_IN,   // just continue moving backwards to home
    ROBOT_FRONT_DETECTED_BALL_OUT,  // evasive motion, continue
    ROBOT_REAR_DETECTED_BALL_IN,    // evasive motion, continue moving backwards to home
    ROBOT_REAR_DETECTED_BALL_OUT,   // continue

    // long dist sensor for ball
    BALL_DETECTED,                  // ball detected, no robot ard; go to ball
    BALL_DETECTED_COLLECT_BALL,     // ball detected, no robot arnd; collect ball
    BALL_SEARCH_FIRST_BALL,         // default ball search at start of competition
    BALL_SEARCH_NO_ROBOT,           // default ball search

    // limit switch for ball collection
    BALL_COLLECTED_NO_ROBOT,        // move to home

    // limit switch - rear of robot
    HOME,                           // deposit ball

    START,                          // start of competition
};

robotState robot_state = START;
robotState executed_robot_state = START;
robotState previous_executed_robot_state = START;

// only after 3 counts, then declare that the state is correct; this is to correct the random surges
robotState detected_state = START;
robotState previous_detected_state = START;
int state_counter = 0;

bool line_sensor_state_check() {
    switch (executed_robot_state) {
        case LINE_SENSOR_DETECTED:
        case LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL:
            return true;
    }
    return false;
}

bool line_sensor_home_check() {
    switch (line_sensor_state) {
        case 12:
        case 13:
        case 14:
            return true;
    }
    return false;
}

void robot_state_machine() {
    if ((SensorValue [bumper_L] == 1 && SensorValue [bumper_R] == 1) || line_sensor_home_check() && distance_robot_rear >= ROBOT_REAR_DISTANCE_THRESHOLD && (SensorValue [ball_switch] == 1 || ball_collected) && robot_orientation == NORTH) {
        detected_state = HOME;
    }
    else if (line_sensor_state > 0) {
        if (previous_executed_robot_state == BALL_DETECTED_COLLECT_BALL && distance_robot_rear >= ROBOT_REAR_DISTANCE_THRESHOLD) {
            detected_state = LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL;
        }
        else {detected_state = LINE_SENSOR_DETECTED;}
    }
    else if (distance_ball_front < ROBOT_BALL_SHORT_DISTANCE_THRESHOLD && !ball_collected && distance_robot_front > (distance_ball_front + ROBOT_SENSOR_DIFF_THRESHOLD)) {
        detected_state = BALL_DETECTED_COLLECT_BALL;
    }
    else if (distance_ball_front < ROBOT_BALL_DISTANCE_THRESHOLD && !ball_collected && distance_robot_front > (distance_ball_front + ROBOT_SENSOR_DIFF_THRESHOLD)) {
        detected_state = BALL_DETECTED;
    }
    else if ((SensorValue [ball_switch] == 1 || ball_collected) && distance_robot_front < ROBOT_FRONT_DISTANCE_THRESHOLD && distance_robot_rear >= ROBOT_REAR_DISTANCE_THRESHOLD) {
        detected_state = ROBOT_FRONT_DETECTED_BALL_IN;
    }
    else if (!ball_collected && distance_robot_front < ROBOT_FRONT_DISTANCE_THRESHOLD && distance_robot_rear >= ROBOT_REAR_DISTANCE_THRESHOLD) {
        detected_state = ROBOT_FRONT_DETECTED_BALL_OUT;
    }
    else if ((SensorValue [ball_switch] == 1 || ball_collected) && distance_robot_front >= ROBOT_FRONT_DISTANCE_THRESHOLD && distance_robot_rear < ROBOT_REAR_DISTANCE_THRESHOLD) {
        detected_state = ROBOT_REAR_DETECTED_BALL_IN;
    }
    else if ((SensorValue [ball_switch] == 1 || ball_collected) && distance_robot_front >= ROBOT_FRONT_DISTANCE_THRESHOLD && distance_robot_rear >= ROBOT_REAR_DISTANCE_THRESHOLD) {
        detected_state = BALL_COLLECTED_NO_ROBOT;
    }
    else if (ball_count == 0) {
        detected_state = BALL_SEARCH_FIRST_BALL;
    }
    else {
        detected_state = BALL_SEARCH_NO_ROBOT;
    }

    if (detected_state == previous_detected_state) {state_counter++;}
    else {state_counter = 1;}

    previous_detected_state = detected_state;
    if (state_counter >= ROBOT_STATE_CORRECT_VALUE && robot_state != detected_state) {
        robot_state = detected_state;
        state_counter = 1;
    }

}
