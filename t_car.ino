#include <SD.h>
#include <SPI.h>

const int chipSelect = 4;
const int speed = 255;
const int curving_speed = 20;
String bt_sig;
const int B1_R_PWM = 5;
const int B1_L_PWM = 6;
const int B2_R_PWM = 9; 
const int B2_L_PWM = 10;

void setup() {
    Serial.begin(9600);
    Serial.print("Initializing SD card...");
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    pinMode(SS, OUTPUT);
    if (!SD.begin(chipSelect)) {
        Serial.println("SD card initialization failed!");
        Serial.println("Things to check:");
        Serial.println("* is a card inserted?");
        Serial.println("* is your wiring correct?");
        Serial.println("* did you change the chipSelect pin to match your shield or module?");
        Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");
        while (1);
    }
    Serial.println("SD card initialization done.");
    if (SD.exists("path.txt")) {
        SD.remove("path.txt");
        Serial.println("Existing path.txt removed");
    }
    File dataFile = SD.open("path.txt", FILE_WRITE);
    if (dataFile) {
        dataFile.println("Movement Log Start");
        dataFile.close();
        Serial.println("New path.txt created");
    }
    pinMode(B1_R_PWM, OUTPUT);
    pinMode(B1_L_PWM, OUTPUT);
    pinMode(B2_R_PWM, OUTPUT);
    pinMode(B2_L_PWM, OUTPUT);
}

void logMovement(const char* movement) {
    File dataFile = SD.open("path.txt", FILE_WRITE);
    if (dataFile) {
        dataFile.println(movement);
        dataFile.close();
    } else {
        Serial.println("Error opening path.txt");
    }
}

void loop() {
    bt_sig = "";
    while(Serial.available()) {
        bt_sig = (char)Serial.read();
    }

    if(bt_sig == "F") {
        forward();
        Serial.println("move forward");
        logMovement("forward");
    }
    else if(bt_sig == "L") {
        turn_left();
        Serial.println("move left");
        logMovement("left");
    }
    else if(bt_sig == "R") {
        turn_right();
        Serial.println("move right");
        logMovement("right");
    }
    else if(bt_sig == "B") {
        backward();
        Serial.println("move back");
        logMovement("backward");
    }
    else if (bt_sig == "S") {
        stop_bot();
        Serial.println("stop");
    }
    else if (bt_sig == "G") {
        Left_forward();
        Serial.println("Fwd left");
    }
    else if (bt_sig == "I") {
        right_forward();
        Serial.println("Fwd Right");
    }
    else if (bt_sig == "H") {
        left_backward();
        Serial.println("Back left");
    }
    else if (bt_sig == "J") {
        right_backward();
        Serial.println("Back right");
    }
    else if(bt_sig == "X") {
        kachra_dance();
        delay(600);
        stop_bot();
        kachra_dance_2();
        Serial.println("Kachra dance");
    }
}

void stop_bot() {
    analogWrite(B1_R_PWM, 0);
    analogWrite(B1_L_PWM, 0);
    analogWrite(B2_R_PWM, 0);
    analogWrite(B2_L_PWM, 0);
}

void forward() {
    analogWrite(B1_R_PWM, speed);
    analogWrite(B1_L_PWM, 0);
    analogWrite(B2_R_PWM, speed);
    analogWrite(B2_L_PWM, 0);
}

void backward() {
    analogWrite(B1_R_PWM, 0);
    analogWrite(B1_L_PWM, speed);
    analogWrite(B2_R_PWM, 0);
    analogWrite(B2_L_PWM, speed);
}

void turn_left() {
    analogWrite(B1_R_PWM, 0);
    analogWrite(B1_L_PWM, speed);
    analogWrite(B2_R_PWM, speed);
    analogWrite(B2_L_PWM, 0);    
}

void turn_right() {
    analogWrite(B1_R_PWM, speed);
    analogWrite(B1_L_PWM, 0);
    analogWrite(B2_R_PWM, 0);
    analogWrite(B2_L_PWM, speed);
}

void Left_forward() {
    analogWrite(B1_R_PWM, curving_speed);
    analogWrite(B1_L_PWM, 0);
    analogWrite(B2_R_PWM, speed);
    analogWrite(B2_L_PWM, 0);  
}

void right_forward() {
    analogWrite(B1_R_PWM, speed);
    analogWrite(B1_L_PWM, 0);
    analogWrite(B2_R_PWM, curving_speed);
    analogWrite(B2_L_PWM, 0);
}

void left_backward() {
    analogWrite(B1_R_PWM, 0);
    analogWrite(B1_L_PWM, curving_speed);
    analogWrite(B2_R_PWM, 0);
    analogWrite(B2_L_PWM, speed);
}

void right_backward() {
    analogWrite(B1_R_PWM, 0);
    analogWrite(B1_L_PWM, speed);
    analogWrite(B2_R_PWM, 0);
    analogWrite(B2_L_PWM, curving_speed);
}

void kachra_dance() {
    analogWrite(B1_R_PWM, 0);
    analogWrite(B1_L_PWM, speed);
    analogWrite(B2_R_PWM, 0);
    analogWrite(B2_L_PWM, 75);
}

void kachra_dance_2() {
    analogWrite(B1_R_PWM, speed);
    analogWrite(B1_L_PWM, 0);
    analogWrite(B2_R_PWM, 0);
    analogWrite(B2_L_PWM, 65);
}
