//Servo Motor
#include <Servo.h>
Servo myservo;

#define Visor 12
#define BTN1 5
#define BTN2 4

int pressionado1 = 0;
int pressionado2 = 0;
int modo = 0;

//------------------------------------------------<< setup
void setup(){
  Serial.begin(9600); 
  pinMode(Visor, OUTPUT);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  
  //Servo
   myservo.attach(13); 
}

//------------------------------------------------<< loop
void loop(){
  Serial.println(modo);
  Serial.println("--------");
  pressionado1 = digitalRead(BTN1);
  pressionado2 = digitalRead(BTN2);
  
  botao();
  
  if(modo == 0){
    Ligado();
  }
  if(modo == 1){
    Fechar();
  }
  if(modo == 2){
    Abrir();
  }
}
//------------------------------------------------<< função
// função capacete
void Ligado(){
  delay(100);
  digitalWrite(Visor, HIGH);   // Visor ligado
  
  myservo.write(0); // posição do Servo motor   
}

void Abrir(){
  delay(100);
  digitalWrite(Visor, LOW);   // Visor ligado
  
  myservo.write(85); // posição do Servo motor   
}

void Fechar(){
  myservo.write(0); // posição do Servo motor
  delay(100);
  digitalWrite(Visor, HIGH);   // Visor ligado    
}

// função Botão
void botao(){
  if(pressionado1 == HIGH){
      if(modo == 0){
        modo += 2;
        Serial.println(modo);
        Serial.println("--------");
        delay(200); // tempo para coreção de botão. problemas com conato
      }
      if(modo == 1){
        modo += 1;
        Serial.println(modo);
        Serial.println("--------");
        delay(200); // tempo para coreção de botão.
      }
  }
  if(pressionado2 == HIGH){
      if(modo == 2){
        modo -= 1;
        Serial.println(modo);
        Serial.println("--------");
        delay(200); // tempo para coreção de botão.
      }
  }
}
