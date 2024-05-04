#include <U8glib.h>
#include "EmonLib.h"

#define Pino_Corrente A1

U8GLIB_ST7920_128X64_1X u8g(11, 13, 12, U8G_PIN_NONE);
EnergyMonitor emon;

char corrente_tela[6];
char potencia_tela[6];
char custo[6];
float valor_tensao = 5.0;
double potencia;
double consumo;
double custo_energia;
float tarifa = 0.6;

void setup() {

  u8g.setFont(u8g_font_8x13B); // Determina a fonte das letras no display
  u8g.begin();//Inicia o display

  Serial.begin(9600);

  emon.current(Pino_Corrente, 60.6); //Determina o pino do sensor e o valor para calibrar o sensor 
}

void loop() {

  double corrente = emon.calcIrms(1480); // Calcula a corrente que passa pelo fio
  delay(3000);
  potencia = corrente * valor_tensao; // Calcula a potência do dispositivo

  if (corrente < 0.3){// Se a corrente em um número ínfimo, considera-se que não há corrente passando pelo fio
    corrente = 0.0;
    potencia = 0.0;
  }
 
  consumo = potencia / 1000; // Calcula o consumo de energia em Kw
  custo_energia = consumo * (tarifa / 3600); //Calcula o custo do consumo de acordo com a tarifa da cidade de João Pessoa
  
  char consumo_tela[6];
  numcustopstr(custo_energia);
  dtostrf(corrente, 4, 1, corrente_tela); // 4 define o tamanho max da string e 1 é a quantidade de "numeros" apos o ponto
  dtostrf(potencia, 4, 1, potencia_tela);

  dtostrf(consumo, 5, 4, consumo_tela);

  delay(3000);
  u8g.firstPage(); // Mostra os valores da corrente e potência no display
  do {
    u8g.drawStr(0, 20, "Corrente:");
    u8g.drawStr(70, 20, corrente_tela);
    u8g.drawStr(105, 20, "A");
    u8g.drawStr(0, 60, "Potencia:");
    u8g.drawStr(75, 60, potencia_tela);
    u8g.drawStr(108, 60, "W");
  } while (u8g.nextPage());

  Serial.println(); 
  Serial.print("Corrente: ");
  Serial.print(corrente);
  Serial.println("A");
  Serial.print("Potência: ");
  Serial.print(potencia);
  Serial.println("W");


  u8g.firstPage(); 
  do {
    u8g.drawStr(0, 20, "Consumo: ");
    u8g.drawStr(70, 20, consumo_tela);
    u8g.drawStr(85, 35, "kwh");
    u8g.drawStr(0, 60, "Custo: ");
    u8g.drawStr(53, 60, "R$");
    u8g.drawStr(70, 60, custo);
  } while (u8g.nextPage());

  Serial.print("Consumo: ");
  Serial.print(consumo);
  Serial.println("kwh");
  Serial.print("Custo: ");
  Serial.print("R$ ");
  Serial.print(custo);
  printf("\n");

  delay(3000); // Tempo para exibir os valores de corrente e potência novamente
}

void numpotpstr(double pot){
  dtostrf(pot, 4, 1, potencia_tela);// Transforma de ponto flutuante para string (para exibir no display)
}
void numcustopstr(double c){
  dtostrf(c, 4, 3, custo); // Transforma de ponto flutuante para string (para exibir no display)
}