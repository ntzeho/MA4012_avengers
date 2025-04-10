enum robotState {
    // line sensor
    LINE_SENSOR_DETECTED,
    LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL,
    LINE_SENSOR_DETECTED_BALL_COLLECTED,

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

bool bumper_home_check() {
    if (SensorValue [bumper_L] == 1 && SensorValue [bumper_R] == 1) {return true;}
    else if (SensorValue [bumper_L] == 1) {
        clearTimer(T2);
        while (time1[T2] < HOMING_BOTH_SIDES_CHECK_TIME) {
            if (SensorValue [bumper_R] == 1) {return true;}
        }
        return false;
    }
    else if (SensorValue [bumper_R] == 1) {
        clearTimer(T2);
        while (time1[T2] < HOMING_BOTH_SIDES_CHECK_TIME) {
            if (SensorValue [bumper_L] == 1) {return true;}
        }
        return false;
    }
    return false;
}

bool line_sensor_state_check() {
    if (robot_state == BALL_DETECTED) {return false;};
    switch (executed_robot_state) {
        case LINE_SENSOR_DETECTED:
        case LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL:
        case LINE_SENSOR_DETECTED_BALL_COLLECTED:
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
    
    if (BR == 8) {
        clearTimer(T3);
        while (time1[T3] < HOMING_BOTH_SIDES_CHECK_TIME) {
            if (BL == 1) {return true;}
        }
        return false;
    }
    else if (BL == 4) {
        clearTimer(T3);
        while (time1[T3] < HOMING_BOTH_SIDES_CHECK_TIME) {
            if (BR == 1) {return true;}
        }
        return false;
    }
    return false;
}

bool robot_orientation_home_check() {
    switch (robot_orientation) {
        case NORTH:
        case NORTHEAST:
        case NORTHWEST:
            return true;
    }
    return false;
}

bool robot_orientation_rejection_check() {
    switch (robot_orientation) {
        case SOUTH:
        case SOUTHWEST:
        case SOUTHEAST:
            return true;

        default:
            return false;
    }
}

bool ball_check(short distance_threshold) {
    if (robot_orientation_rejection_check()) {
        return false;
        //return (distance_ball_front_right > ROBOT_BALL_SOUTH_REJECTION_THRESHOLD && distance_ball_front_left > ROBOT_BALL_SOUTH_REJECTION_THRESHOLD);
    }
    return (distance_ball_front_right < distance_threshold || distance_ball_front_left < distance_threshold || distance_ball_front_center < distance_threshold);
}

void robot_state_machine() {
    if ((SensorValue [ball_switch] == 1 || ball_collected) && robot_orientation_home_check() && (bumper_home_check() && line_sensor_home_check())) {
        detected_state = HOME;
    }
    else if (line_sensor_state > 0) {
        if (previous_executed_robot_state == BALL_DETECTED_COLLECT_BALL) {
            detected_state = LINE_SENSOR_DETECTED_BALL_DETECTED_COLLECT_BALL;
        }
        else if (previous_executed_robot_state == BALL_COLLECTED_NO_ROBOT) {detected_state = LINE_SENSOR_DETECTED_BALL_COLLECTED;}
        else {detected_state = LINE_SENSOR_DETECTED;}
    }
    // else if (distance_ball_front < ROBOT_BALL_SHORT_DISTANCE_THRESHOLD && !ball_collected && distance_robot_front > (distance_ball_front + ROBOT_SENSOR_DIFF_THRESHOLD)) {
    //     //detecting metallic reflective surface
    //     if (robot_orientation == SOUTH && distance_ball_front_left < ROBOT_BALL_REJECTION_DISTANCE_THRESHOLD){ 
    //         //continue ball searching
    //         if (ball_count ==0){detected_state = BALL_SEARCH_FIRST_BALL;}
    //         else {detected_state = BALL_SEARCH_NO_ROBOT;}
    //     }
    //     // detected ball 
    //     else {detected_state = BALL_DETECTED_COLLECT_BALL;}
        
    // }
    // else if (robot_orientation != SOUTH && distance_ball_front < ROBOT_BALL_DISTANCE_THRESHOLD && !ball_collected && distance_robot_front > (distance_ball_front + ROBOT_SENSOR_DIFF_THRESHOLD)) {
    //     //detecting metallic reflective surface
    //     if (robot_orientation == SOUTH && distance_ball_front_left < ROBOT_BALL_REJECTION_DISTANCE_THRESHOLD){ 
    //         //continue ball searching
    //         if (ball_count ==0){detected_state = BALL_SEARCH_FIRST_BALL;}
    //         else {detected_state = BALL_SEARCH_NO_ROBOT;}
    //     }
    //     // detected ball 
    //     else {detected_state = BALL_DETECTED;}
    // }
    else if (ball_check(ROBOT_BALL_DISTANCE_THRESHOLD) && !ball_collected && distance_robot_front > (distance_ball_front_right + ROBOT_SENSOR_DIFF_THRESHOLD)) {
        detected_state = BALL_DETECTED;
    // } else if (ball_check(ROBOT_BALL_SHORT_DISTANCE_THRESHOLD) && !ball_collected && distance_robot_front > (distance_ball_front_right + ROBOT_SENSOR_DIFF_THRESHOLD)) {
    //     detected_state = BALL_DETECTED_COLLECT_BALL;
    }
    else if ((SensorValue [ball_switch] == 1 || ball_collected) && distance_robot_front < ROBOT_FRONT_DISTANCE_THRESHOLD) {
        detected_state = ROBOT_FRONT_DETECTED_BALL_IN;
    }
    else if (!ball_collected && distance_robot_front < ROBOT_FRONT_DISTANCE_THRESHOLD) {
        detected_state = ROBOT_FRONT_DETECTED_BALL_OUT;
    }
    else if ((SensorValue [ball_switch] == 1 || ball_collected) && distance_robot_front >= ROBOT_FRONT_DISTANCE_THRESHOLD && TIMER /*implement timer for turn_to_north_home here */) {
        detected_state = ROBOT_REAR_DETECTED_BALL_IN;
    }
    else if ((SensorValue [ball_switch] == 1 || ball_collected) && distance_robot_front >= ROBOT_FRONT_DISTANCE_THRESHOLD) {
        detected_state = BALL_COLLECTED_NO_ROBOT;
    }
    else if (ball_search_first_ball) {
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
