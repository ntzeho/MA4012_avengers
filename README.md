# MA4012_avengers

- constants.c - important constants in code (motor power, important sleep times, etc.)
- sensor_detection.c - determine robot orientation from compass readings, convert distance sensor readings to distance in cm, read line sensors
- robot_state.c - robot state machine to determine robot state
- movement.c - modified sleep function with built in state detection, motor controls (driving, turning, ball capture and release)
- sensor_action.c - determine robot action depending on permutations of triggered line sensors
- scanning.c - ball scanning algorithm
- main.c - source code importing above files in order
