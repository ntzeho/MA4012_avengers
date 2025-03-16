float voltage_long0;
float voltage_long1;
float voltage_long2;

float distance_long0;   // robot front checker
float distance_long1;   // robot rear checker
float distance_long2;   // ball finder

void distance_calculator() {
    voltage_long0 = (SensorValue [dist_long0]) * (5.0 / 4096.0);
    voltage_long1 = (SensorValue [dist_long1]) * (5.0 / 4096.0);
    voltage_long2 = (SensorValue [dist_long2]) * (5.0 / 4096.0);

    distance_long0 = 27.534 * pow(voltage_long0 , -1.207);
    distance_long1 = 27.534 * pow(voltage_long1 , -1.207);
    distance_long2 = 27.534 * pow(voltage_long2 , -1.207);

    if (distance_long0 > 50) {distance_long0 = 50;}
    if (distance_long1 > 50) {distance_long1 = 50;}
    if (distance_long2 > 50) {distance_long2 = 50;}

    sleep(50);
}


//distance_short = pow(2.7818281828, 2.507) * pow(voltage_short , -1.123);

/*
task test_short_sensor() {
    while (true) {
        float voltage_short = (SensorValue [dist_short]) * (5.0 / 4096.0);
        float distance_short = pow(2.7818281828, 2.507) * pow(voltage_short , -1.123);
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
