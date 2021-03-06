/*

Este código reconhece um cartão e acende LEDs
O monitor LCD I2C foi colocado nas porata 
A5 = SDA
A4 = SCL
*/
//biblioteca do monitor
#include <Arduino.h>
#include <Wire.h>
#include <MicroLCD.h>

//biblioteca do RFID
#include <SPI.h>
#include <MFRC522.h>

// pinos do RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

//pino do rele
#define Rele 2

//pino do BUZZER
#define BUZZER 5 

//CONFIGURACAO DO DISPLAY MICRO LCD
LCD_SSD1306 lcd;

//Demostração de imagem no LCD
const PROGMEM uint8_t logo[48 * 48 / 8] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE0,
0xF0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0x18, 0x18, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0xF0,
0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xF8,
0xF1, 0x73, 0x1F, 0x0F, 0x0F, 0x07, 0x07, 0x06, 0x04, 0x07, 0x07, 0x0F, 0x0F, 0x1F, 0x63, 0xF1,
0xF8, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF9, 0xF9, 0xF9, 0xF9, 0xFF,
0xFF, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0xFF,
0xFF, 0xF9, 0xF9, 0xF9, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x07, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F,
0x7F, 0x00, 0x00, 0x40, 0x7F, 0x4F, 0x0F, 0x03, 0x00, 0x0F, 0x4F, 0x7F, 0x7F, 0x00, 0x00, 0x7F,
0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x07, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC,
0xF8, 0xF8, 0x08, 0x04, 0x00, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0x00, 0x04, 0x08, 0xF8, 0xF8,
0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03,
0x07, 0x07, 0x0E, 0x0E, 0x0E, 0x0F, 0x0F, 0x1F, 0x1F, 0x0F, 0x0F, 0x08, 0x08, 0x0C, 0x07, 0x07,
0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup() 
{
  //Monitor Serial
  Serial.begin(9600);
  
  //RFID   
  SPI.begin();      
  mfrc522.PCD_Init(); 

  //Rele
  pinMode(Rele, OUTPUT);
  
  //LEDs  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  //LCD
  lcd.begin();
}
//comando para o BUZZER 
void tocaSom(int frequencia) {
 tone(BUZZER,frequencia, 100);
}

//comando de alerta
void alerta(){
  lcd.clear();
  lcd.setFontSize(FONT_SIZE_SMALL);
  lcd.println("Analise concluida:");
  lcd.println(" ");
  lcd.setFontSize(FONT_SIZE_MEDIUM);
  lcd.println("Entrada");
  lcd.println("nao autorizada");
  delay(1000);
}

//comando de confirmação
void ok(){
  lcd.clear();
  lcd.setFontSize(FONT_SIZE_SMALL);
  lcd.println("Analise concluida");
  lcd.println(" ");
  lcd.setFontSize(FONT_SIZE_MEDIUM);
  lcd.println("Bem vindo");
  lcd.println("Pedro Cordeiro");
  delay(1000);
}

//comando para resetar o LCD
void limpa(){
  lcd.clear(); //limpa a o lcd
  lcd.setFontSize(FONT_SIZE_MEDIUM); //tamanho da letra
  lcd.println("Analisando:");        //escreve na tela
  lcd.setCursor(40, 2);              //posiciona
  lcd.draw(logo, 48, 48);            //mostra a imagem
  delay(1000); 
}
void loop() 
{
  limpa(); 
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  Serial.print("Identificação do cartao:");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
 
  if (conteudo.substring(1) == "79 17 44 B8") //cartao 1
  {
    Serial.println("Entrada não autorizada!");
    Serial.println();
    digitalWrite(Rele, HIGH); //desliga o rele(desliga o ventilador)
    alerta();   //mostra na tela a mensagem de alerta
    digitalWrite(7, HIGH); // ativa led vermelho
    tocaSom(2800);   // liga o BUZZER no tom 2800
    delay(500);           // espera 3 segundos
    digitalWrite(7, LOW);  // desativa led vermelho
    tocaSom(0);  //Desliga o BUZZER
    delay(500); 
    digitalWrite(7, HIGH);
    tocaSom(2800); 
    delay(500);           
    digitalWrite(7, LOW);
    tocaSom(0);
    delay(500); 
    digitalWrite(7, HIGH);
    tocaSom(2800);
    delay(500);          
    digitalWrite(7, LOW);
    tocaSom(0);
    limpa();
  }  

   if (conteudo.substring(1) == "9A 89 76 1A") //cartao 2
  {
    Serial.println("Bem vindo de Volta Pedro Cordeiro!");
    Serial.println();
    digitalWrite(Rele, LOW);//Liga o rele(liga o ventilador
    ok(); //mensagem de permição na tela
    digitalWrite(6, HIGH); // ativa led verde
    tocaSom(2800);
    delay(250);                 // espera 3 segundos
    digitalWrite(6, LOW); // desativa led verde
    tocaSom(0);
    delay(250); 
    digitalWrite(6, HIGH);
    tocaSom(2800); 
    delay(250);          
    digitalWrite(6, LOW);
    tocaSom(0);
    limpa();
  }  
}
