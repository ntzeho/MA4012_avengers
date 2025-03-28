void reorientate(robotOrientation target_orientation) {
    switch (target_orientation) {
        case NORTH:
            turn_to_north();
            break;

        case SOUTH:
            turn_to_south();
            break;

        case EAST:
            turn_to_east();
            break;

        case WEST:
            turn_to_west();
            break;
    }
}

void ball_scanning() {
    turn_360_degrees();
    if (executed_robot_state == robot_state) {drive_distance(1, 60);}
    stop_movement();
}
