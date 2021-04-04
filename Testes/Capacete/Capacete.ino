
//Servo Motor
#include <Servo.h>
Servo myservo;
int sataus = 0;

#define Visor 12 // Leds do visor 12

//#define BTN 9

// the setup routine runs once when you press reset:
void setup() {     
  // initialize the digital pin as an output.
   pinMode(Visor, OUTPUT);
   myservo.attach(13); 
   
//   pinMode(BTN, INPUT); 
}

// the loop routine runs over and over again forever:
void loop() {
  
 
  while (sataus == 0) {
    Ligado(); 
  }  
  
}

void Ligado(){
    digitalWrite(Visor, HIGH);   // Visor ligado
    myservo.write(0); // posição do Servo motor   
}
//void Abrir(){
//    delay(100);
//    digitalWrite(Visor, LOW);   // Visor ligado
//    myservo.write(85); // posição do Servo motor   
//}
