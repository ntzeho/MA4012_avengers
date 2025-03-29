void react_to_line_sensors() {
    switch (line_sensor_state) {
        case 1: // FL
        //reverse and turn right to align with nearest orientation
            break;

        case 2: // FR  
        //reverse and turn left to align with nearest orientation
            break;

        case 3: // FL | FR
            stop_movement();         
            drive_distance_fixed(-1, 30);
            if (start_position == 'L') {turn_90_degrees_R();}
            else {turn_90_degrees_L();}
            break;

        case 4: // BL
        //drive forward and turn right to align with nearest orientation
            break;

        case 5: // FL | BL
            stop_movement();
            turn_angle(1, 45);
            drive_distance(1, 30);
            break;

        case 7: // FL | FR | BL
            stop_movement();
            drive_distance_fixed(-1, 30); //will move to case 5
            break;

        case 8: // BR
        //drive forward and turn left to align with nearest orientation
            break;
            
        case 10: // FR | BR
            stop_movement();
            turn_angle(-1, 45);
            drive_distance_fixed(1, 30);
            break;

        case 11: // FL | FR | BR
            stop_movement();
            drive_distance_fixed(-1, 30); //will move to case 10
            break;

        case 12: // BL | BR
            stop_movement();
            drive_distance_fixed(1, 30);
            break;
        
        case 13: // FL | BL | BR
            stop_movement();
            drive_distance_fixed(1, 30); //will move to case 5
            break;

        case 14: // FR | BL | BR
            stop_movement();
            drive_distance_fixed(1, 30); //will move to case 10
            break;

        default:
            /*
            case 0: // NONE
            case 6: // FR | BL
            case 9: // FL | BR
            case 15: // ALL, enemy robot has their own yellow lines
            */
            break;
    }

    sleep(1);
}

void react_to_line_sensors_collect_ball() {
    switch (line_sensor_state) {
        case 1: // FL
        case 2: // FR
        case 3: // FL | FR
        case 7: // FL | FR | BL
        case 11: // FL | FR | BR
            drive_distance_fixed(1, 10);
            drive_distance_fixed(-1, 15);
            break;

        default:
            /*
            case 0: // NONE
            case 4: // BL
            case 6: // FR | BL
            case 5: // FL | BL
            case 8: // BR
            case 9: // FL | BR
            case 10: // FR | BR
            case 12: // BL | BR
            case 13: // FL | BL | BR
            case 14: // FR | BL | BR
            case 15: // ALL, enemy robot has their own yellow lines
            */
            break;
    }

    sleep(1);
}
