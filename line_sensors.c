float right_action;
float left_action;
float forward_action;
float backward_action;
float forwardbackward_action;
float rightback_action;
float leftback_action;
float rightforward_action;
float leftforward_action;

// Enum to represent the state of the sensors
enum lineSensors {
    NONE = 0,
    LEFT = 1 << 0,      // 0001
    RIGHT = 1 << 1,     // 0010
    FRONT = 1 << 2,     // 0100
    BACK = 1 << 3       // 1000
};

// Function to react based on the sensor states
void react_to_sensors(int sensorState) {
    right_action =0;
    left_action=0;
    forward_action=0;
    backward_action=0;
    forwardbackward_action = 0;
    rightback_action=0;
    leftback_action=0;
    rightforward_action=0;
    leftforward_action=0;

    switch (sensorState) {
        case 0: //NONE
        right_action = 0;
        left_action = 0;
        forward_action = 0;
        backward_action = 0;
        forwardbackward_action = 0;
        rightback_action = 0;
        leftback_action = 0;
        rightforward_action = 0;
        leftforward_action = 0;
            //No action
            break;

        case 1: //LEFT
        left_action = 1;
            //Right action
            break;

        case 2: //RIGHT
        right_action = 1;
        //Left action
            break;

        case 3: //LEFT | RIGHT
        forwardbackward_action = 1;
        //left_action = 0;
        //right_action = 0;
        //Forward or backward action
            break;

        case 4: //FRONT
        backward_action = 1;
        // Backward action
            break;

        case 8: //BACK
        forward_action = 1;
        // Forward action
            break;

        case 5:
        rightback_action = 1;
        // Right backward action
            break;

        case 6://RIGHT | FRONT
        leftback_action = 1;
        // Left backward action
            break;

        case 9://LEFT | BACK
        rightforward_action = 1;
        // Right forward action
            break;

        case 10: //RIGHT | BACK
        leftforward_action = 1;
        // Left forward action
            break;

        // More combinations if required
        default:

        // set for none maybe
            break;
        
    }
    sleep(1);
}
