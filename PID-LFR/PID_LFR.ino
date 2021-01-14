#include <QTRSensors.h>
QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

#define Kp 2 
#define Kd 40
#define MaxSpeed 225
#define BaseSpeed 155
#define speedturn 100

//int STBY = 10; 
//Motor A
int PWMA = 5; //for speed control
int AIN1 = 11; //Direction
int AIN2 = 12; //Direction
//Motor B
int PWMB = 3; //for speed control
int BIN1 = 9; //Direction
int BIN2 = 8; //Direction

int lastError=0;

void setup()
{   
    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6,A7}, SensorCount);
    //qtr.setEmitterPin(2);pinMode(STBY, OUTPUT);
    pinMode(PWMA, OUTPUT);pinMode(AIN1, OUTPUT);pinMode(AIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);pinMode(BIN1, OUTPUT);pinMode(BIN2, OUTPUT);
    delay(500);pinMode(LED_BUILTIN, OUTPUT);digitalWrite(LED_BUILTIN, HIGH);
    delay(3000);
    int i;
    for (int i = 0; i < 100; i++)
    {   
        if ( i  < 25 || i >= 75 ) 
        {   move(0,speedturn, 1);
            move(1,speedturn, 0);
        }
        else
        {   move(0,speedturn, 0);
            move(1,speedturn, 1);
        }
        qtr.calibrate();delay(20);
    }
    delay(3000); 
}  

void loop()
{   
    uint16_t position = qtr.readLineBlack(sensorValues);
    if(position>6700)
    {   move(1, speedturn, 1);move(0, speedturn, 0);return;    
    }
    if(position<300)
    {   move(1, speedturn, 0);move(0, speedturn, 1);return;
    }
    int error = position - 3500;
    int motorSpeed = Kp * error + Kd * (error - lastError);
    lastError = error;

    int rightMotorSpeed = BaseSpeed + motorSpeed;
    int leftMotorSpeed = BaseSpeed - motorSpeed;
  
    if (rightMotorSpeed > MaxSpeed ) rightMotorSpeed = MaxSpeed; 
    if (leftMotorSpeed > MaxSpeed ) leftMotorSpeed = MaxSpeed;
    if (rightMotorSpeed < 0)rightMotorSpeed = 0;    
    if (leftMotorSpeed < 0)leftMotorSpeed = 0;
    
    move(1, rightMotorSpeed, 1);
    move(0, leftMotorSpeed, 1);
}

void move(int motor, int speed, int direction)
{   
    boolean inPin1=HIGH,inPin2=LOW;
    if(direction == 1){inPin1 = HIGH;inPin2 = LOW;}  
    if(direction == 0){inPin1 = LOW; inPin2 = HIGH;}
    if(motor == 0)
    {   digitalWrite(AIN1, inPin1);digitalWrite(AIN2, inPin2);analogWrite(PWMA, speed);
    }
    if(motor == 1)
    {   digitalWrite(BIN1, inPin1);digitalWrite(BIN2, inPin2);analogWrite(PWMB, speed);
    }  
}
