// Enum to represent the state of the sensors
enum LineSensors {
    NONE = 0,
    LEFT = 1 << 0,      // 0001
    RIGHT = 1 << 1,     // 0010
    FRONT = 1 << 2,     // 0100
    BACK = 1 << 3       // 1000
};

// Function to react based on the sensor states
void reactToSensors(int sensorState) {
    switch (sensorState) {
        case NONE:
        //No action
            break;
        case LEFT:
        //Right action
            break;
        case RIGHT:
        //Left action
            break;
        case LEFT | RIGHT:
        //Forward or backward action
            break;
        case FRONT:
        // Backward action
            break;
        case BACK:
        // Forward action
            break;
        case LEFT | FRONT:
        // Right backward action
            break;
        case RIGHT | FRONT:
        // Left backward action
            break;
        case LEFT | BACK:
        // Right forward action
            break;
        case RIGHT | BACK:
        // Left forward action
            break;

        // More combinations if required
        default:
        // set for none maybe
            break;
    }
}

task main()
{
		// read and return sensor states

    // Sensor States
    int sensorState = LEFT | RIGHT | FRONT | BACK;

    reactToSensors(sensorState);
}
