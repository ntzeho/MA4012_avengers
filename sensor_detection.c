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
float voltage_robot_rear;
float voltage_ball_front;
float distance_robot_front;  // robot front checker
float distance_robot_rear;   // robot rear checker
float distance_ball_front;   // ball finder

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
    voltage_robot_rear = (SensorValue [dist_robot_rear]) * (5.0 / 4096.0);
    voltage_ball_front = (SensorValue [dist_ball_front]) * (5.0 / 4096.0);

    distance_robot_front = 27.534 * pow(voltage_robot_front , -1.207); //to recalibrate as it is new sensor
    distance_robot_rear = 27.534 * pow(voltage_robot_rear , -1.207);
    distance_ball_front = 27.534 * pow(voltage_ball_front , -1.207);
    //distance_long2 = 27.194 * pow(voltage_long2, -1.121); //pow(2.718281828, 3.303)

    // if (distance_long0 > 50) {distance_long0 = 50;}
    // if (distance_long1 > 50) {distance_long1 = 50;}
    // if (distance_long2 > 50) {distance_long2 = 50;}

    sleep(50);
}

void get_line_sensor_state() {
    FL = !SensorValue[line_FL] << 0;
    FR = !SensorValue[line_FR] << 1;
    BL = !SensorValue[line_BL] << 2;
    BR = !SensorValue[line_BR] << 3;
    line_sensor_state = FL | FR | BL | BR;
}
