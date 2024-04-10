#include <LiquidCrystal.h>
#include "EmonLib.h"

//Definição dos pinos referentes ao display
#define DB4 7
#define DB5 6
#define DB6 5
#define DB7 4
#define RS 12
#define E 11
#define Pino_Corrente A0 //Definição do pino analógico referente ao sensor

EnergyMonitor emon;

int tensao_padrao = 220;

LiquidCrystal lcd(RS, E, DB4, DB5, DB6, DB7);

void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2); //indica os parametros de coluna e linha
  lcd.setCursor(0,0); //indica a posição onde o texto vai ficar
  lcd.print("Corrente: "); //imprime o texto na tela
  lcd.setCursor(0, 1);
  lcd.print("Potência: ");

  emon.current(Pino_Corrente, 30.0); //Define o pino de entrada da corrente e o valor de calibração da corrente  
}

void loop() {
  //Calcula o valor da corrente e imprime no display
  double irms = emon.calcIrms(1200);
  lcd.setCursor(5, 0);
  lcd.print(irms);
  lcd.setCursor(6, 0);
  lcd.print("A");
  //Calcula o valor da potência (Corrente * Tensão) e imprime no display abaixo da corrente
  lcd.setCursor(5, 1);
  lcd.print(irms * tensao_padrao, 1);
  lcd.setCursor(6, 1);
  lcd.print("V");
}

