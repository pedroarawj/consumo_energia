#include "EmonLib.h"

#define Pino_Corrente A1
#define PinVerde 9  // Pino do LED verde
#define PinVermelho 8

EnergyMonitor emon;

float valor_tensao = 5.0; // Tensão para o cálculo da corrente
double potencia; 
double energia;
float custo_energia;
float limite_custo = 0.01;
unsigned long tempo_anterior = 0;

void setup() {
  Serial.begin(9600);

  emon.current(Pino_Corrente, 60.6); // Calibração do sensor para a análise da corrente
  pinMode(PinVerde, OUTPUT);
  pinMode(PinVermelho, OUTPUT);
}

void loop() {
  unsigned long tempo_atual = millis();
  double corrente = emon.calcIrms(1480); // A corrente é calculada com auxílio da biblioteca
  potencia = corrente * valor_tensao; // Definição de potência
  energia = potencia * (tempo_atual - tempo_anterior) / 3600 / 1000; // Consumo de energia em kwh. Conversão da potencia e do tempo
  custo_energia = energia * 0.6; // Cálculo do custo de energia com base na tarifa de João Pessoa

  Serial.print("Corrente: ");
  Serial.print(corrente);
  Serial.println(" A");

  Serial.print("Potência: ");
  Serial.print(potencia, 1);
  Serial.println(" W");
  delay(1000);

  Serial.print("Consumo: ");
  Serial.print(energia, 3);
  Serial.println(" kWh");
  Serial.print("Custo: ");
  Serial.print(custo_energia, 2);
  Serial.println(" reais");
  delay(1000);

// Estrutura condicional que depende do custo e limite fornecido
  if (custo_energia > limite_custo){
    digitalWrite(PinVerde, LOW);
    digitalWrite(PinVermelho, HIGH); // Se o custo exceder o limite, o led vermelho acenderá
    delay(500);
  } else {
    digitalWrite(PinVermelho, LOW);
    digitalWrite(PinVerde, LOW);
    delay(500);
    digitalWrite(PinVerde, HIGH); //Se o custo não exceder o limite, o led verde ficará piscando
  } 

}
