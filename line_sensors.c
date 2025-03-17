short line_sensor_state;
bool to_avoid_boundary = false;
byte FL;
byte FR;
byte BL;
byte BR;

void get_line_sensor_state() {
    /*
    byte left;
    byte right;
    byte front;
    byte back;

    left = !SensorValue[line_FL] << 0;
    right = !SensorValue[line_FR] << 1;
    front = !SensorValue[line_BL] << 2;
    back = !SensorValue[line_BR] << 3;
    line_sensor_state = back | front | left | right;
    */

    FL = !SensorValue[line_FL] << 0;
    FR = !SensorValue[line_FR] << 1;
    BL = !SensorValue[line_BL] << 2;
    BR = !SensorValue[line_BR] << 3;
    line_sensor_state = FL | FR | BL | BR;

    switch(line_sensor_state){
        case 0:
            to_avoid_boundary = false;
            break;
        case 6:
            to_avoid_boundary = false;
            break;
        case 9:
            to_avoid_boundary = false;
            break;
        case 15:
            to_avoid_boundary = false;
            break;
        default:
            to_avoid_boundary = true;
            break;
    }
}

void react_to_line_sensors() {
    switch (line_sensor_state) {
        case 0: // NONE
            // No action
            break;

        case 1: // FL
            drive(-1, 30);
            turn_angle(1, 45); // Turn right 45 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 2: // FR  
            drive(-1, 30);
            turn_angle(-1, 45); // Turn left 45 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 3: // FL | FR             
            drive(-1, 30); // Drive backward slightly
            sleep(500);
            turn_angle(1, 180); // Rotate 180 degrees
            break;

        case 4: // BL
            drive(1, 30);
            turn_angle(1, 20); // Turn right 20 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 5: // FL | BL             
            turn_angle(1, 45); // Turn right 45 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 6: // FR | BL           
            // Ignore
            break;

        case 7: // FL | FR | BL
            turn_angle(1, 100); // Turn right 100 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 8: // BR
            drive(1, 30);
            turn_angle(-1, 20); // Turn left 20 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 9: // FL | BR          
            // Ignore
            break;
            
        case 10: // FR | BR
            turn_angle(-1, 45); // Turn left 45 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 11: // FL | FR | BR
            turn_angle(-1, 100); // Turn left 100 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 12: // BL | BR
            /*
            sensorCase12 = 1;
            if () { // Check ball present and 2 rear limit switch depressed
                deposit_ball(); 
            } else {
                drive(); // Drive forward slightly
            }
            */
            //mechanical detection better than sensor detection, HOME >> boundary
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;
        
        case 13: // FL | BL | BR
            /*
            sensorCase13 = 1;
            if () { // Check ball present and 2 rear limit switch depressed
                deposit_ball(); 
            } else {
                turn(); // Turn right 45 degrees
                drive(); // Drive forward slightly
            }
            */
            //same as case 12
            turn_angle(1, 45); // Turn right 45 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 14: // FR | BL | BR
            /*
            sensorCase14 = 1;
            if () { // Check ball present and 2 rear limit switch depressed
                deposit_ball();
            } else {
                turn(); // Turn left 45 degrees
                drive(); // Drive forward slightly
            }
            */
            //same as case 12
            turn_angle(-1, 45); // Turn left 45 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;
        
        case 15: // ALL
            //stop_movement();
            //impossibe to occur, if happens means likely bug
            break; 

        default: // For any unknown states
            break;
    }

    sleep(1);
}

/*
// Enum to represent the state of the sensors
enum lineSensors {
    NONE = 0,
    LEFT = 1 << 0,      // 0001
    RIGHT = 1 << 1,     // 0010
    FRONT = 1 << 2,     // 0100
    BACK = 1 << 3       // 1000
};

float right_action;
float left_action;
float forward_action;
float backward_action;
float forwardbackward_action;
float rightback_action;
float leftback_action;
float rightforward_action;
float leftforward_action;

// Function to react based on the sensor states
void react_to_line_sensors() {
    right_action =0;
    left_action=0;
    forward_action=0;
    backward_action=0;
    forwardbackward_action = 0;
    rightback_action=0;
    leftback_action=0;
    rightforward_action=0;
    leftforward_action=0;

    switch (line_sensor_state) {
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

float sensorCase0 = 0;
float sensorCase1 = 0;
float sensorCase2 = 0;
float sensorCase3 = 0;
float sensorCase4 = 0;
float sensorCase5 = 0;
float sensorCase6 = 0;
float sensorCase7 = 0;
float sensorCase8 = 0;
float sensorCase9 = 0;
float sensorCase10 = 0;
float sensorCase11 = 0;
float sensorCase12 = 0;
float sensorCase13 = 0;
float sensorCase14 = 0;
float sensorCase15 = 0;

// Function to react based on the sensor states
void react_to_line_sensors_bryan() {
    // Reset all cases
    sensorCase0 = sensorCase1 = sensorCase2 = sensorCase3 = sensorCase4 = sensorCase5 = sensorCase6 =
    sensorCase7 = sensorCase8 = sensorCase9 = sensorCase10 = sensorCase11 = sensorCase12 =
    sensorCase13 = sensorCase14 = sensorCase15 = 0;

    switch (line_sensor_state) {
        case 0: // NONE
            // No action
            break;

        case 1: // FL
            sensorCase1 = 1;
            turn(); // Turn right 45 degrees
            drive(); // Drive forward slightly
            break;

        case 2: // FR
            sensorCase2 = 1;            
            turn(); // Turn left 45 degrees
            drive(); // Drive forward slightly
            break;

        case 3: // FL | FR
            sensorCase3 = 1;             
            drive(); // Drive backward slightly
            turn(); // Rotate 180 degrees
            break;

        case 4: // BL
            sensorCase4 = 1; 
            turn(); // Turn right 20 degrees
            drive(); // Drive forward slightly
            break;

        case 5: // FL | BL
            sensorCase5 = 1;             
            turn(); // Turn right 45 degrees
            drive(); // Drive forward slightly
            break;

        case 6: // FR | BL
            sensorCase6 = 1;             
            // Ignore
            break;

        case 7: // FL | FR | BL
            sensorCase7 = 1; 
            turn(); // Turn right 100 degrees
            drive(); // Drive forward slightly
            break;

        case 8: // BR
            sensorCase8 = 1; 
            turn(); // Turn left 20 degrees
            drive(); // Drive forward slightly
            break;

        case 9: // FL | BR
            sensorCase9 = 1;            
            // Ignore
            break;
            
        case 10: // FR | BR
            sensorCase10 = 1;
            turn(); // Turn left 45 degrees
            drive(); // Drive forward slightly
            break;

        case 11: // FL | FR | BR
            sensorCase11 = 1;
            turn(); // Turn left 100 degrees
            drive(); // Drive forward slightly
            break;

        case 12: // BL | BR
            sensorCase12 = 1;
            if () { // Check ball present and 2 rear limit switch depressed
                deposit_ball(); 
            } else {
                drive(); // Drive forward slightly
            }
            break;
        
        case 13: // FL | BL | BR
            sensorCase13 = 1;
            if () { // Check ball present and 2 rear limit switch depressed
                deposit_ball(); 
            } else {
                turn(); // Turn right 45 degrees
                drive(); // Drive forward slightly
            }
            break;

        case 14: // FR | BL | BR
            sensorCase14 = 1;
            if () { // Check ball present and 2 rear limit switch depressed
                deposit_ball();
            } else {
                turn(); // Turn left 45 degrees
                drive(); // Drive forward slightly
            }
            break;
        
        case 15: // ALL
            sensorCase15 = 1;
            stop_movement(); 
            break; 

        default: // For any unknown states
            break;
    }

    sleep(1);
}
*/
