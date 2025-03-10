enum robotState {
    // line sensor
    LINE_SESNOR_DETECTED,           // line sensor detected, ignore all get back in game
    // long dist sensors for robot
    ROBOT_FRONT_DETECTED_BALL_IN,   // just continue moving backwards to home
    ROBOT_FRONT_DETECTED_BALL_OUT,  // evasive motion, continue
    ROBOT_REAR_DETECTED_BALL_IN,    // evasive motion, continue moving backwards to home
    ROBOT_REAR_DETECTED_BALL_OUT,   // continue
    // long dist sensor for ball
    BALL_DETECTED,                  // ball detected, no robot ard; go to ball
    BALL_SEARCH_NO_ROBOT,           // default ball search
    // limit switch for ball collection
    BALL_COLLECTED_NO_ROBOT,        // move to home
    // limit switch - rear of robot
    HOME,                           // deposit ball
    BLANK,
};
robotState robot_state = BLANK;

// only after 5 counts, then declare that the state is correct; this is to correct the random surges
robotState detected_state = BLANK;
robotState previous_detected_state = BLANK;
int state_counter = 0;