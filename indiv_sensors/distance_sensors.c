float voltage_robot_front_right;
float voltage_robot_rear;
float voltage_ball_front;

float distance_robot_front_right;   // robot front checker
float distance_robot_rear;   // robot rear checker
float distance_ball_front;   // ball finder

void distance_calculator() {
    voltage_robot_front_right = (SensorValue [dist_robot_front]) * (5.0 / 4096.0);
    voltage_robot_rear = (SensorValue [dist_robot_rear]) * (5.0 / 4096.0);
    voltage_ball_front = (SensorValue [dist_ball_front]) * (5.0 / 4096.0);

    distance_robot_front_right = 27.534 * pow(voltage_robot_front_right , -1.207); //to recalibrate as it is new sensor
    distance_robot_rear = 27.534 * pow(voltage_robot_rear , -1.207);
    distance_ball_front = 27.534 * pow(voltage_ball_front , -1.207);
    //distance_long2 = 27.194 * pow(voltage_long2, -1.121); //pow(2.718281828, 3.303)

    // if (distance_long0 > 50) {distance_long0 = 50;}
    // if (distance_long1 > 50) {distance_long1 = 50;}
    // if (distance_long2 > 50) {distance_long2 = 50;}

    sleep(50);
}


//distance_short = pow(2.7818281828, 2.507) * pow(voltage_short , -1.123);

/*
task test_short_sensor() {
    while (true) {
        float voltage_short = (SensorValue [dist_short]) * (5.0 / 4096.0);
        float distance_short = pow(2.718281828, 2.507) * pow(voltage_short , -1.123);
        while (distance_short < 30) {
            drive(1, 30);
            if (distance_short < 4) {
                motor [ball_in_motor] = 30;
                break;
            }
        }
    }
}
*/
