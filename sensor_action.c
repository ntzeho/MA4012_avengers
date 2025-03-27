void react_to_line_sensors() {
    switch (line_sensor_state) {
        case 0: // NONE
            // No action
            break;

        case 1: // FL
            stop_movement();
            drive(-1, 30);
            sleep(500);
            turn_angle(1, 45); // Turn right 45 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 2: // FR  
            stop_movement();
            drive(-1, 30);
            sleep(500);
            turn_angle(-1, 45); // Turn left 45 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 3: // FL | FR    
            stop_movement();         
            drive(-1, 30); // Drive backward slightly
            sleep(500);
            turn_angle(1, 180); // Rotate 180 degrees
            break;

        case 4: // BL
            stop_movement();
            drive(1, 30);
            sleep(500);
            turn_angle(1, 20); // Turn right 20 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 5: // FL | BL   
            stop_movement();          
            turn_angle(1, 45); // Turn right 45 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 6: // FR | BL           
            // Ignore
            break;

        case 7: // FL | FR | BL
            stop_movement();
            turn_angle(1, 100); // Turn right 100 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 8: // BR
            stop_movement();
            drive(1, 30);
            sleep(500);
            turn_angle(-1, 20); // Turn left 20 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 9: // FL | BR          
            // Ignore
            break;
            
        case 10: // FR | BR
            stop_movement();
            turn_angle(-1, 45); // Turn left 45 degrees
            drive(1, 30); // Drive forward slightly
            sleep(500);
            break;

        case 11: // FL | FR | BR
            stop_movement();
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
            stop_movement();
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
            stop_movement();
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
            stop_movement();
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