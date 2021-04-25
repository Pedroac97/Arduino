//Programa : Relogio com modulo RTC DS1307 e display oled 0.96′′ i2c
//Autor : Pedro Cordeiro

//-----------------------------------------------------------------------------------------------<< Bibliotecas
//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Carrega a biblioteca do RTC DS1307
#include <DS1307.h>

//-----------------------------------------------------------------------------------------------<< Configurção de modulos
//Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,16,2);

//Modulo RTC DS1307 ligado as portas A4 e A5 do Arduino 
DS1307 rtc(A2, A3);


//-----------------------------------------------------------------------------------------------<< Setup
void setup()
{
  // monitor serial
  Serial.begin(9600); 

  //Aciona Led
   lcd.init();
 
  //Aciona o relogio
  rtc.halt(false);

//  //As linhas abaixo setam a data e hora do modulo
//  //e podem ser comentada apos a primeira utilizacao
//  rtc.setDOW(SUNDAY);      //Define o dia da semana
//  rtc.setTime(10, 35, 10);     //Define o horario
//  rtc.setDate(25, 4, 2021);   //Define o dia, mes e ano

  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);


}

//-----------------------------------------------------------------------------------------------<< Loop 
void loop()
{
  Horas();
  Data(); 
  //Mostra as informações no Serial Monitor
  Serial.print("Hora : ");
  Serial.print(rtc.getTimeStr());
  Serial.print(" ");
  Serial.print("Data : ");
  Serial.print(rtc.getDateStr(FORMAT_SHORT));
  Serial.print(" ");
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));
   
  //Aguarda 1 segundo e repete o processo
  delay (500);
}
void Horas(){
  lcd.setBacklight(HIGH);
  lcd.setCursor(10,0);
  lcd.print("HORAS :");
  lcd.setCursor(10,1);
  lcd.print(rtc.getTimeStr());
}

void Data(){
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("DATA :");
  lcd.setCursor(0,1);
  lcd.print(rtc.getDateStr(FORMAT_SHORT));
  lcd.setCursor(0,2);
  lcd.print(rtc.getDOWStr(FORMAT_SHORT));
  lcd.setCursor(8,2);
  lcd.print("BY:PedroAC97");
}
