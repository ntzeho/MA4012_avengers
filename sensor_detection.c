enum robotOrientation {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    NORTHEAST,
    SOUTHEAST,
    SOUTHWEST,
    NORTHWEST,
    NIL
};

robotOrientation robot_orientation = NIL;

float voltage_robot_front;
// float voltage_robot_rear;
float voltage_ball_front_right;
float voltage_ball_front_left;
float voltage_ball_front_center;
float distance_robot_front;  // robot front checker
// float distance_robot_rear;   // robot rear checker
float distance_ball_front_right;   // ball left
float distance_ball_front_left;  // ball right
float distance_ball_front_center;

float distance_ball_front_left_temp;
float distance_ball_front_right_temp;
float distance_ball_front_center_temp;

int distance_ball_front_counter_left;
int distance_ball_front_counter_right;
int distance_ball_front_counter_center;

short line_sensor_state;
byte FL;
byte FR;
byte BL;
byte BR;

void get_direction() {
    short num = 8 * SensorValue [compass_west] + 4 * SensorValue [compass_south] + 2 * SensorValue [compass_east] + SensorValue [compass_north];
    switch (num) {
        case 14:
            robot_orientation = NORTH;
            break;
        case 13:
            robot_orientation = EAST;
            break;
        case 11:
            robot_orientation = SOUTH;
            break;
        case 7:
            robot_orientation = WEST;
            break;
        case 12:
            robot_orientation = NORTHEAST;
            break;
        case 9:
            robot_orientation = SOUTHEAST;
            break;
        case 3:
            robot_orientation = SOUTHWEST;
            break;
        case 6:
            robot_orientation = NORTHWEST;
            break;
        default:
            robot_orientation = NIL;
    }
}

void distance_calculator() {
    voltage_robot_front = (SensorValue [dist_robot_front]) * (5.0 / 4096.0);
    voltage_ball_front_center = (SensorValue [dist_ball_front_center]) * (5.0 / 4096.0);
    voltage_ball_front_right = (SensorValue [dist_ball_front_right]) * (5.0 / 4096.0);
    voltage_ball_front_left = (SensorValue [dist_ball_front_left]) * (5.0 / 4096.0);

    distance_ball_front_center_temp = pow(2.718281828, 3.091) * pow(voltage_ball_front_center, -0.9937);
    distance_ball_front_left_temp = pow(2.718281828, 3.094) * pow(voltage_ball_front_left , -1.838);
    distance_ball_front_right_temp = pow(2.718281828, 3.276) * pow(voltage_ball_front_right , -1.081);

    distance_robot_front = pow(2.718281828, 2.507) * pow(voltage_robot_front , -1.123);
    //27.534 * pow(voltage_ball_front_right , -1.207);
    //distance_ball_front_temp = 27.534 * pow(voltage_ball_front , -1.207);
    // distance_ball_front = 27.534 * pow(voltage_ball_front , -1.207);
    //distance_long2 = 27.194 * pow(voltage_long2, -1.121); //pow(2.718281828, 3.303)

    // if (distance_long0 > 50) {distance_long0 = 50;}
    // if (distance_long1 > 50) {distance_long1 = 50;}
    // if (distance_long2 > 50) {distance_long2 = 50;}
    
    // added this section for far distance rejection
    // dist rejection for front left
    if (distance_ball_front_left_temp <= ROBOT_BALL_DISTANCE_THRESHOLD) {distance_ball_front_counter_left++;}
    else {distance_ball_front_counter_left = 1;}

    if (distance_ball_front_counter_left >= FRONT_DIST_CORRECT_VALUE){
        distance_ball_front_left = distance_ball_front_left_temp;
    }
    else{distance_ball_front_left = ROBOT_BALL_DISTANCE_THRESHOLD + 100;}

    //dist rejection for front right
    if (distance_ball_front_right_temp <= ROBOT_BALL_DISTANCE_THRESHOLD) {distance_ball_front_counter_right++;}
    else {distance_ball_front_counter_right = 1;}

    if (distance_ball_front_counter_right >= FRONT_DIST_CORRECT_VALUE){
        distance_ball_front_right = distance_ball_front_right_temp;
    }
    else{distance_ball_front_right = ROBOT_BALL_DISTANCE_THRESHOLD + 100;}

    //dist rejection for front right
    if (distance_ball_front_center_temp <= ROBOT_BALL_DISTANCE_THRESHOLD) {distance_ball_front_counter_center++;}
    else {distance_ball_front_counter_center = 1;}

    if (distance_ball_front_counter_center >= FRONT_DIST_CORRECT_VALUE){
        distance_ball_front_center = distance_ball_front_center_temp;
    }
    else{distance_ball_front_center = ROBOT_BALL_DISTANCE_THRESHOLD + 100;}
    
    sleep(50);
}

void get_line_sensor_state() {
    FL = !SensorValue[line_FL] << 0; //1
    FR = !SensorValue[line_FR] << 1; //2
    BL = !SensorValue[line_BL] << 2; //4
    BR = !SensorValue[line_BR] << 3; //8
    line_sensor_state = FL | FR | BL | BR;
}

task detection() {
	while (true) {
		distance_calculator();
		get_direction();
		get_line_sensor_state();
	}
}
