#include <math.h>
#include <Wire.h>
#include "MMA7660.h"
MMA7660 accelemeter;

<<<<<<< HEAD
//comment by Aidan
=======
//Sachin pushing
//Anton pushing
>>>>>>> origin/master

// rotary sensor
#define ROTARY_ANGLE_SENSOR A2
#define ADC_REF 5//reference voltage of ADC is 5v.If the Vcc switch on the seeeduino
         //board switches to 3V3, the ADC_REF should be 3.3
#define GROVE_VCC 5//VCC of the grove interface is normally 5v
#define FULL_ANGLE 300//full value of the rotary angle is 300 degrees

//sound sensor
#define SOUND_SENSOR A1
#define THRESHOLD_VALUE 760 //The threshold to turn the led on 400.00*5/1024 = 1.95v

const int ledPin =  3;      // the number of the LED pin

//button variables
const int buttonPin = 4;     // the number of the pushbutton pin
int buttonState = 0; 

//temperature sensor variables
int a;
float temperature;
int B=3975;                  //B value of the thermistor
float resistance;
const int temp_pin = 0;

// light sensor variables
const int thresholdvalue=10;         //The threshold for which the LED should turn on. 
float Rsensor; //Resistance of sensor in K
int light_trig = 0;
const int light_pin = 3;

// rotary sensor variables
float degree = 0;
float voltage;
int rotary_in;
int degree_int;

// sound sensor variables
int sound_in;
int sound_trig;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
  // button setup 
  pinMode(buttonPin, INPUT);

  //temperature sensor
  pinMode(temp_pin, INPUT);

  // light sensor
  pinMode(light_pin, INPUT);
  
  //rotary sensor
  pinMode(ROTARY_ANGLE_SENSOR, INPUT);

  //sound sensor
  pinMode(SOUND_SENSOR, INPUT);

  //accelerometer
  accelemeter.init(); 

}

void loop() {
  button_sens();
  temperature_sens();
  light_sens();
  rotary_sens();
  sound_sens();
  accel_sens();
  
  //rotary sensor code
  degree_int = (int) degree / 10;
}

// button function
void button_sens() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
}

//temperature function
void temperature_sens() {
  a=analogRead(temp_pin);
  resistance=(float)(1023-a)*10000/a; //get the resistance of the sensor;
  temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;//convert to temperature via datasheet ;
}

//light function
void light_sens() {
  int sensorValue = analogRead(light_pin); 
  Rsensor=(float)(1023-sensorValue)*10/sensorValue;
    
  if(Rsensor>thresholdvalue) {
    light_trig = 1;
  }
  else {
    light_trig = 0;
  }
}

void rotary_sens() {
  rotary_in = analogRead(ROTARY_ANGLE_SENSOR);
  voltage = (float)rotary_in*ADC_REF/1023;
  degree = (voltage*FULL_ANGLE)/GROVE_VCC;
}

void sound_sens() {
    sound_in = analogRead(SOUND_SENSOR); //use A0 to read the electrical signal
    Serial.print("sound level: ");
    Serial.println(sound_in);
    if(sound_in > THRESHOLD_VALUE)
    {
      sound_trig = 1;
    }
    else {
      sound_trig = 0;
    }
}

void accel_sens() {
  int8_t x;
  int8_t y;
  int8_t z;
  float ax,ay,az;
  accelemeter.getXYZ(&x,&y,&z);
  accelemeter.getAcceleration(&ax,&ay,&az);
}

