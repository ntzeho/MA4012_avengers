float voltage_long0;
float voltage_long1;
float voltage_long2;

float distance_long0;	// robot front checker
float distance_long1;	// robot rear checker
float distance_long2;	// ball finder

const string robotStateNames[4] = {
	"BALL_DETECTED",
	"ROBOT_FRONT_DETECTED",
  "ROBOT_REAR_DETECTED",
  "BLANK",
};

enum robotState {
    ROBOT_FRONT_DETECTED,
    BALL_DETECTED,
    ROBOT_REAR_DETECTED,
    BLANK,
};
robotState robot_state = BLANK;

// only after 5 counts, then declare that the state is correct; this is to correct the random surges
robotState detected_state = BLANK;
robotState previous_detected_state = BLANK;
int state_counter = 0;

void distance_calculator() {
	voltage_long0 = (SensorValue [dist_long0]) * (5.0 / 4096.0);
	voltage_long1 = (SensorValue [dist_long1]) * (5.0 / 4096.0);
	voltage_long2 = (SensorValue [dist_long2]) * (5.0 / 4096.0);

	distance_long0 = 27.534 * pow(voltage_long0 , -1.207);
	distance_long1 = 27.534 * pow(voltage_long1 , -1.207);
	distance_long2 = 27.534 * pow(voltage_long2 , -1.207);
	//distance_short = pow(2.7818281828, 2.507) * pow(voltage_short , -1.123);

	if (distance_long0 > 50) {distance_long0 = 50;}
	if (distance_long1 > 50) {distance_long1 = 50;}
	if (distance_long2 > 50) {distance_long2 = 50;}
}

void robot_state_machine() {
    if (distance_long0 < 15) {
		detected_state = ROBOT_FRONT_DETECTED;
	}
    else if (distance_long1 < 15) {
		detected_state = ROBOT_REAR_DETECTED;
	}
	else if (((distance_long0 >15)) && (distance_long2 < 40)) {
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
