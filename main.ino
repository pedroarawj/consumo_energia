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
#define LED_VERDE 8      // Pino para o LED verde
#define LED_VERMELHO 9   // Pino para o LED vermelho

EnergyMonitor emon;

float valor_tensao = 220.0; //110.0 dependendo da tomada

double limite_consumo = 0.150; // Limite de consumo ideal em kW/min 

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

  emon.current(Pino_Corrente, 2000); // Define o pino de entrada da corrente e o valor de calibração da corrente
}

void loop() {

  emon.calcVI(20, 2000); //Mede a corrente 
  // Calcula o valor da corrente
  double corrente = emon.Irms;

  // Calcula o valor da potência (Corrente * Tensão) 
  double potencia = emon.RealPower;

  // Calcula o consumo de energia (Potência * Tempo decorrido) 
  double energia = power * (millis() / 60000.0);  // Calcula a energia em kW/min

  //Laço de repetição para alternar a exibição de diferentes informações no display
  while(1){
    lcd.setCursor(9, 0);
    lcd.print(corrente); //Imprime no display o valor da corrente
    lcd.print(" A");

    lcd.setCursor(9, 1);
    lcd.print(potencia, 1);//Imprime no display o valor da potência
    lcd.print(" W");

    delay(2000);
    lcd.clear(); //Retira os elementos anteriores da tela para exibir apenas o consumo

    // Controle dos LEDs com base no consumo de energia
  if (energia <= limite_consumo) {
    digitalWrite(LED_VERMELHO, LOW); // Apaga o LED vermelho
    digitalWrite(LED_VERDE, HIGH);
    delay(500);
    digitalWrite(LED_VERDE, LOW);//Faz o LED verde piscar
    delay(500);
  } else {
    digitalWrite(LED_VERDE, LOW); // Apaga o LED verde
    // Faz o LED vermelho piscar
    digitalWrite(LED_VERMELHO, HIGH);
    delay(500);
    digitalWrite(LED_VERMELHO, LOW);
    delay(500);
  }
    lcd.setCursor(0, 1);
    lcd.print("Consumo: ");
    lcd.print(energia, 3);//Imprime no display o consumo de energia
    lcd.print(" kW/min");

    delay(2000); // Definição de tempo para voltar a informação da corrente e potência na tela
  }
}
