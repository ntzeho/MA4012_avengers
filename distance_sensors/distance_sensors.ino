/* 
DIFFERENT SURFACES YIELD DIFFERENT VALUES FROM DIST SENSORS.
IN TESTING I USED A WHITE SURFACE FOR CONTROL SET UP; SHOULD TEST METAL SURFACE & TENNIS BALL & THE DIFF ROBOT SURFACE.
BLACK SCREWS WITH THE SENSORS READING 100%, SHAWDOWS AT TIMES

THE VALUES FLUCTUATES, NOT STABLE!

TESTED RANGE 10CM TO 70CM ONLY
sharp_long0 & sharp_long1 accuracy  -> stable range: 10cn to 40cm; unstable range: anything above was unpredictable
sharp_long2 accuracy                -> stable range: 10cn to 50cm; unstable range: anything above was unpredictable

TESTED RANGE 4CM TO 30CM ONLY
sharp_short accuracy                -> stable range: 4cn to 20cm; unstable range: anything above was unpredictable
*/


// 2Y0A21 - 10cm to 80cm
#define sharp_long0 A0  // robot detection
#define sharp_long1 A1  // ball detection
#define sharp_long2 A2  // rear detection

// 0A41SK - 4cm to 30cm
#define sharp_short A3  // ball collection detection

const int num_sensors = 4;
int sharp_sensors[] = {sharp_long0, sharp_long1, sharp_long2, sharp_short};

float voltage[num_sensors];
float distance[num_sensors];

const char * robotStateNames[] = {
    "ROBOT_DETECTED",
    "BALL_DETECTED",
    "REAR_DETECTED",
    "BALL_COLLECTED",
    "BLANK"
};

enum robotState {
    ROBOT_DETECTED,
    BALL_DETECTED,
    REAR_DETECTED,
    BALL_COLLECTED,
    BLANK,
};
robotState robot_state = BLANK;

// only after 3 counts, then declare that the state is correct; this is to correct the random surges
robotState detected_state = BLANK;
robotState previous_detected_state = BLANK;
int state_counter = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    distance_calculator();
    robot_state_machine();
    //robot action code base on robot_state here!
}

// values are all hypothetical for testing, to update!!!
void robot_state_machine() {
    if ((distance[0] < 30) || (distance[0] < 30 && distance[1] < 30)) {
        detected_state = ROBOT_DETECTED;
        // evasive action taken
    }
    else if (distance[0] > 30 && distance[1] < 30) {
        detected_state = BALL_DETECTED;
        // drive train to go collect ball
        if (distance[3] > 4 && distance[3] < 10) {
        detected_state = BALL_COLLECTED;
        // drive train to go to home base to drop off ball
            if (distance[2] >= 10 && distance[2] <= 30) {    // what if another robot is behind us?
                detected_state = REAR_DETECTED;
                // drive train to stop & unload the ball
            }
        }
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


    if (state_counter >= 2 && robot_state != detected_state) {
        robot_state = detected_state;

        switch(robot_state) {
        case ROBOT_DETECTED:
            break;
        case BALL_DETECTED:
            break;
        case REAR_DETECTED:
            break;
        case BALL_COLLECTED:
            break;
        case BLANK:
            break;
        }
        state_counter = 1;
    }

    Serial.println(robotStateNames[robot_state]);
}

void distance_calculator() {
    for (int i = 0; i < num_sensors; i++) {
        voltage[i] = analogRead(sharp_sensors[i]) * (5.0 / 1023.0);
        
        if (i < 3) {
        distance[i] = 27.86 * pow(voltage [i], -1.15); // for long sharp dist sensors
        }
        else {
        distance[i] = 13.00 * pow(voltage[i], -1.10);   // for short sharp dist sensors
        }

        Serial.print(distance[i]);
        if (i < num_sensors -1) {
        Serial.print(", ");
        }
    }
    Serial.println();
    delay(500);
}