#define Visor 12
#define BTN 5

int pressionado = 0;
int modo = 0;

//--------------------------------------<<
void setup(){
  Serial.begin(9600); 
  pinMode(Visor, OUTPUT);
    pinMode(BTN, INPUT);
}

//------------------------------------------<<
void loop(){
  Serial.println(modo);
  Serial.println("--------");
  pressionado = digitalRead(BTN);
  Serial.println(modo);
  Serial.println("--------");
  
  botao();
  
  if(modo == 0){
    Ligado();
  }
  if(modo == 1){
    Abrir();
  }
}
//------------------------------------------------<<
// função capacete
void Ligado(){
    delay(100);
    digitalWrite(Visor, HIGH);   // Visor ligado
    //myservo.write(0); // posição do Servo motor   
}
void Abrir(){
    delay(100);
    digitalWrite(Visor, LOW);   // Visor ligado
    //myservo.write(85); // posição do Servo motor   
}



// função Botão
void botao(){
  if(pressionado == HIGH){
    if(modo == 0){
      modo += 1;
      Serial.println(modo);
      Serial.println("--------");
      delay(150); // tempo para coreção de botão. problemas com conato
    }
    else{
      modo -= 1;
      Serial.println(modo);
      Serial.println("--------");
      delay(150); // tempo para coreção de botão.
    }
  }
}
