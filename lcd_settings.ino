#include <LiquidCrystal.h>
#include "EmonLib.h"

// Definição dos pinos referentes ao display
#define DB4 7
#define DB5 6
#define DB6 5
#define DB7 4
#define RS 12
#define E 11
#define Pino_Corrente A0 // Definição do pino analógico referente ao sensor
#define LED_VERDE 8      // Pino para o LED verde
#define LED_VERMELHO 9   // Pino para o LED vermelho

EnergyMonitor emon;

int tensao_padrao = 220;
double limite_consumo = 1.0; // Limite de consumo ideal em kWh 

LiquidCrystal lcd(RS, E, DB4, DB5, DB6, DB7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Indica os parametros de coluna e linha
  lcd.setCursor(0, 0); // Indica a posição onde o texto vai ficar
  lcd.print("Corrente: "); // Imprime o texto na tela
  lcd.setCursor(0, 1);
  lcd.print("Potência: ");

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  emon.current(Pino_Corrente, 30.0); // Define o pino de entrada da corrente e o valor de calibração da corrente
}

void loop() {
  // Calcula o valor da corrente
  double irms = emon.calcIrms(1200);

  // Calcula o valor da potência (Corrente * Tensão) 
  double potencia = irms * tensao_padrao;

  // Calcula o consumo de energia (Potência * Tempo decorrido) 
  static double energiaTotal = 0.0;
  unsigned long tempoAtual = millis();
  static unsigned long tempoAnterior = 0;

  double tempoPassado = (tempoAtual - tempoAnterior) / 1000.0;
  double energiaConsumida = potencia * tempoPassado / 3600000.0;
  energiaTotal += energiaConsumida;
  tempoAnterior = tempoAtual;

  //Laço de repetição para alternar a exibição de diferentes informações no display
  while(1){
    lcd.setCursor(9, 0);
    lcd.print(irms); //Imprime no display o valor da corrente
    lcd.print(" A");

    lcd.setCursor(9, 1);
    lcd.print(potencia, 1);//Imprime no display o valor da potência
    lcd.print(" W");

    delay(2500);
    lcd.clear(); //Retira os elementos anteriores da tela para exibir apenas o consumo

    lcd.setCursor(0, 1);
    lcd.print("Consumo: ");
    lcd.print(energiaTotal, 2);//Imprime no display o consumo de energia
    lcd.print(" kWh");

    delay(2500); // Definição de tempo para voltar a informação da corrente e potência na tela
  }

  // Controle dos LEDs com base no consumo de energia
  if (energiaTotal <= limite_consumo) {
    digitalWrite(LED_VERDE, HIGH); // Acende o LED verde
    digitalWrite(LED_VERMELHO, LOW); // Apaga o LED vermelho
  } else {
    digitalWrite(LED_VERDE, LOW); // Apaga o LED verde
    // Faz o LED vermelho piscar
    digitalWrite(LED_VERMELHO, HIGH);
    delay(500);
    digitalWrite(LED_VERMELHO, LOW);
    delay(500);
  }
}