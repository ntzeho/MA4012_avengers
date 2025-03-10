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
