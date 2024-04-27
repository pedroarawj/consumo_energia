#include <U8glib.h>
#include "EmonLib.h"

#define Pino_Corrente A1

U8GLIB_ST7920_128X64_1X u8g(11, 13, 12, U8G_PIN_NONE);
EnergyMonitor emon;

char corrente_tela[6];
char potencia_tela[6];
float valor_tensao = 5.0;
double potencia;
double energia;
double custo_energia;
double potencia_tot = 0;
double potencia_media = 0;
int contador = 0;
double energia_total = 0;
double custo_total = 0;
unsigned long tempo_anterior = 0;

void setup() {
  u8g.setFont(u8g_font_6x10);

  u8g.begin();

  emon.current(Pino_Corrente, 60.6);
}

void loop() {
  contador++; // Conta quantas vezes ocorreu um loop para o cálculo da potência média
  unsigned long tempo_atual = millis();
  double corrente = emon.calcIrms(1480); //Calcula a corrente que passa pelo fio
  potencia = corrente * valor_tensao; // Calcula a potência do dispositivo
  potencia_tot += potencia; // Recebe o total dos valores das potências apresentadas

  potencia_media = potencia_tot / contador; // A média entre as potências apresentadas durante o loop 
  energia_total = potencia_media * (tempo_atual / 60); // Calcula o consumo de energia com a média das potências vezes o tempo de uso do dispositivo (seg para h)
  custo_energia = energia_total * 0.6; //Calcula o custo do consumo de acordo com a tarifa da cidade de João Pessoa
  char custo[6];
  dtostrf(custo_energia, 5, 2, custo); // Transforma de ponto flutuante para string (para exibir no display)
  
  numpotpstr(potencia);
  dtostrf(corrente, 4, 1, corrente_tela); // 4 define o tamanho max da string e 1 é a quantidade de "numeros" apos o ponto

  char energia_tela[6];
  dtostrf(energia_total, 5, 2, energia_tela);

  u8g.firstPage(); // Mostra os valores da corrente e potência no display
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(0, 20, "Corrente:");
    u8g.drawStr(70, 20, corrente_tela);
    u8g.drawStr(105, 20, "A");
    u8g.drawStr(0, 60, "Potencia:");
    u8g.drawStr(75, 60, potencia_tela);
    u8g.drawStr(108, 60, "W");
  } while (u8g.nextPage());

  delay(60000); // Tempo de 1 minuto o consumo seja calculado 

  u8g.firstPage(); // Mostra os valores do consumo e custo no display
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(0, 20, "Consumo: ");
    u8g.drawStr(55, 20, energia_tela);
    u8g.drawStr(100, 20, "kwh");
    u8g.drawStr(0, 60, "Custo: ");
    u8g.drawStr(55, 60, "R$");
    u8g.drawStr(64, 60, custo);
  } while (u8g.nextPage());

  delay(3000); // Tempo para exibir os valores de corrente e potência novamente
}

void numpotpstr(double pot){
  dtostrf(pot, 4, 1, potencia_tela);// Transforma de ponto flutuante para string (para exibir no display)
}


