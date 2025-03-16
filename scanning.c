void turn_scan() {
    switch (start_position) {
        case 'L':
            turn(1, 30);
            break;
        case 'R':
            turn(-1, 30);
            break;
    }
}

void ball_scanning() {
    clearTimer(T2);
    turn_scan();
    if (time1[T2] > 1000) { //scan too long got nth
        //change direction? go somewhere else and continue
    }
    stop_movement();
}
