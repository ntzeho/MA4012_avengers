const short STATE_CORRECT_VALUE = 3;

enum robotState {
    // line sensor
    LINE_SENSOR_DETECTED,           // line sensor detected, ignore all get back in game
    // long dist sensors for robot
    ROBOT_FRONT_DETECTED_BALL_IN,   // just continue moving backwards to home
    ROBOT_FRONT_DETECTED_BALL_OUT,  // evasive motion, continue
    ROBOT_REAR_DETECTED_BALL_IN,    // evasive motion, continue moving backwards to home
    ROBOT_REAR_DETECTED_BALL_OUT,   // continue
    // long dist sensor for ball
    BALL_DETECTED,                  // ball detected, no robot ard; go to ball
    BALL_DETECTED_COLLECT_BALL,     // ball detected, no robot arnd; collect ball
    BALL_SEARCH_NO_ROBOT,           // default ball search
    // limit switch for ball collection
    BALL_COLLECTED_NO_ROBOT,        // move to home
    // limit switch - rear of robot
    HOME,                           // deposit ball
    START,                          // start of competition
    BLANK,
};

robotState robot_state = START;

// only after 3 counts, then declare that the state is correct; this is to correct the random surges
robotState detected_state = START;
robotState previous_detected_state = START;
int state_counter = 0;

void robot_state_machine() {
    if ((SensorValue [bumper_L] == 1 && SensorValue [bumper_R] == 1) || line_sensor_state == 12 || line_sensor_state == 13 || line_sensor_state == 14 && distance_robot_rear >= 15 && SensorValue [ball_switch] == 1) {
        detected_state = HOME;
    } else if (to_avoid_boundary) {
        detected_state = LINE_SENSOR_DETECTED;
    } else if (distance_ball_front < 20 && SensorValue [ball_switch] == 0 && distance_robot_front > distance_ball_front + 5) {
        detected_state = BALL_DETECTED_COLLECT_BALL;
    } else if (distance_ball_front < 70 && SensorValue [ball_switch] == 0 && distance_robot_front > distance_ball_front + 5) {
        detected_state = BALL_DETECTED;
    } else if (SensorValue [ball_switch] == 1 && distance_robot_front < 15 && distance_robot_rear >= 15) {
        detected_state = ROBOT_FRONT_DETECTED_BALL_IN;
    } else if (SensorValue [ball_switch] == 0 && distance_robot_front < 15 && distance_robot_rear >= 15) {
        detected_state = ROBOT_FRONT_DETECTED_BALL_OUT;
    } else if (SensorValue [ball_switch] == 1 && distance_robot_front >= 15 && distance_robot_rear < 15) {
        detected_state = ROBOT_REAR_DETECTED_BALL_IN;
    } else if (SensorValue [ball_switch] == 0 && distance_robot_front >= 15 && distance_robot_rear < 15) {
        detected_state = ROBOT_REAR_DETECTED_BALL_OUT;
    } else if (SensorValue [ball_switch] == 1 && distance_robot_front >= 15 && distance_robot_rear >= 15) {
        detected_state = BALL_COLLECTED_NO_ROBOT;
    } else {
        detected_state = BALL_SEARCH_NO_ROBOT;
    }

    if (detected_state == previous_detected_state) {state_counter++;}
    else {state_counter = 1;}

    previous_detected_state = detected_state;
    if (state_counter >= STATE_CORRECT_VALUE && robot_state != detected_state) {
        robot_state = detected_state;
        state_counter = 1;
    }

}

/*
void robot_state_machine() {
    if (distance_robot_front < 15) {
        detected_state = ROBOT_FRONT_DETECTED;
    }
    else if (distance_robot_rear < 15) {
        detected_state = ROBOT_REAR_DETECTED;
    }
    else if (((distance_robot_front > 15)) && (distance_ball_front < 40)) {
        detected_state = BALL_DETECTED;
        }
    else {
        detected_state = BLANK;
    }

    if (detected_state == previous_detected_state) {
        state_counter++;
    }
    else {
        state_counter = 1;
    }

    previous_detected_state = detected_state;

    if (state_counter >= 5 && robot_state != detected_state) {
        robot_state = detected_state;

        switch(robot_state) {
            case BALL_DETECTED:
                break;
            case ROBOT_FRONT_DETECTED:
                break;
            case ROBOT_REAR_DETECTED:
                break;
            case BLANK:
                break;
        }
        state_counter = 1;
    }
}
*/
