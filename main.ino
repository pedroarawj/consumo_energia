#include <LiquidCrystal.h>
#include "EmonLib.h"

// Definição dos pinos referentes ao display
#define DB4 7
#define DB5 6
#define DB6 5
#define DB7 4
#define RS 12
#define E 11
#define Pino_Corrente A1 // Definição do pino analógico referente ao sensor

EnergyMonitor emon;

int valor_tensao = 5; 
double potencia;
double energia;
float custo_energia;
unsigned long tempo_anterior = 0; 

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

  emon.current(Pino_Corrente, 60.6); // Define o pino de entrada da corrente e o valor de calibração da corrente
}

void loop() {
  unsigned long tempo_atual = millis(); // Variável que recebe o tempo de operação do arduino
  double corrente = emon.calcIrms(1480); // Função que calcula a corrente
  potencia = corrente * valor_tensao;
  energia = potencia * (tempo_atual - tempo_anterior) / 3600 / 1000; // Conversão da potencia em W para kW e multiplicação da mesma pelo tempo (s para h)
  custo_energia = energia * 0.6; // Cálculo do custo em reais em função do consumo

  // Imprime a corrente e potência no display
  lcd.setCursor(0, 0);
  lcd.print("Corrente: ");
  lcd.print(corrente);
  lcd.print(" A");

  lcd.setCursor(0, 1);
  lcd.print("Potencia: ");
  lcd.print(potencia, 1);
  lcd.print(" W");

  delay(2000); // Tempo que a informação é exibida no display

  lcd.clear(); // Retira a corrente e potencia do display para a exibição do consumo e custo

  // Imprime o consumo e custo no display
  lcd.setCursor(0, 0);
  lcd.print("Consumo: ");
  lcd.print(energia, 3);
  lcd.print(" kWh");

  lcd.setCursor(0, 1);
  lcd.print("Custo: ");
  lcd.print(custo_energia, 2);
  lcd.print(" reais");

  delay(2000); // Tempo para a informação e retornar as anteriores


  if (corrente > 2){
    while (1){
      digitalWrite(pinVermelho, HIGH);
      digitalWrite(pinVermelho, LOW);
      digitalWrite(pinVerde, LOW);
    }
  } else {
    digitalWrite(pinVerde, HIGH);
    digitalWrite(pinVermelho, LOW);
  }
  
}