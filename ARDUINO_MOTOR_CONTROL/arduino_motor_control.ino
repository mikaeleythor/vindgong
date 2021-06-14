
#define enPin 10
#define numMotors 3
#define motorDelay 190
#define OFF -1

int stepPin[numMotors] = {2, 4, 6};
int dirPin[numMotors] = {3, 5, 7};
int dirInput[numMotors];
long steps[numMotors];
long i;



void setup(){
    Serial.begin(115200);
    pinMode(stepPin[0], OUTPUT);
    pinMode(dirPin[0], OUTPUT);
    pinMode(stepPin[1], OUTPUT);
    pinMode(dirPin[1], OUTPUT);
    pinMode(stepPin[2], OUTPUT);
    pinMode(dirPin[2], OUTPUT);
}

void loop(){
    Serial.println("Begin loop");
    resetVariables();
    getDirection();
    writeDirection(dirPin, dirInput);
    getSteps();
    writeSteps(stepPin, steps);

}

void resetVariables(){
    Serial.println("Resetting variables");
    for (i = 0; i < numMotors; i++){
        steps[i] = OFF;
        dirInput[i] = OFF;
    }
}

void getSteps(){
    Serial.println("Getting steps");
    for (int i = 0; i < numMotors; i++){
        while (steps[i] == OFF){
            if (Serial.available() > 0){
                steps[i] = Serial.parseInt(SKIP_ALL, '\n');
            }
        }
    }
}

void getDirection(){
    // Takes in 0: LOW or 1: HIGH
    Serial.println("Getting direction");
    for (i = 0; i < numMotors; i++){
        Serial.println("Type direction (0/1): ");
        while (dirInput[i] == OFF){
            if (Serial.available() > 0){
                dirInput[i] = Serial.parseInt(SKIP_ALL, '\n');
            }
        }
    }
}

void writeDirection(int *dirPin, int *dirInput){
    Serial.println("Writing direction");
    for (int i = 0; i < numMotors; i++){
        if (dirInput[i] == 0){
            digitalWrite(dirPin[i], LOW);
        }
        else if (dirInput[i] == 1){
            digitalWrite(dirPin[i], HIGH);
        }
        else if (dirInput[i] == OFF){
            Serial.println("dirInput not assigned a value");
        }
        else
        {
            Serial.println("Unknown error in writeDirection()");
        }
    }
}

void writeSteps(int *stepPin, long *steps){
    Serial.println("Writing steps");
    int stepCount[numMotors] = {0, 0, 0};
    int maxLen = max3(steps[0], steps[1], steps[2]);
    for (int i = 0; i < maxLen; i++){
        for (int j = 0; j < numMotors; j++){
            if (stepCount[j] < steps[j]){
                stepCount[j] ++;
                digitalWrite(stepPin[j], HIGH);
                delayMicroseconds(motorDelay);
                digitalWrite(stepPin[j], LOW);
                delayMicroseconds(motorDelay);
            }
            else
            {
                delayMicroseconds(motorDelay);
                delayMicroseconds(motorDelay);
            }
        }
    }
}

int max3(int a, int b, int c)
{
   int maxguess;

   maxguess = max(a,b);  // biggest of A and B
   maxguess = max(maxguess, c);  // but maybe C is bigger?

   return(maxguess);
}