#include <U8glib.h>
#include "EmonLib.h"

#define Pino_Corrente A1
#define amarelo 8
#define vermelho 9

U8GLIB_ST7920_128X64_1X u8g(11, 13, 12, U8G_PIN_NONE);
EnergyMonitor emon;

char corrente_tela[6];
char potencia_tela[6];
float valor_tensao = 5.0;
double potencia;
double consumo;
double custo_energia;
float tarifa = 0.600;
unsigned long tempo_anterior = 0;
double total_custo = 0;
double limite_custo = 0.002;
double c;

void setup() {
  u8g.setFont(u8g_font_gdb12r);

  u8g.begin();

  emon.current(Pino_Corrente, 60.6);
  
}

void loop() {

  unsigned long tempo_atual = millis();
  double corrente = emon.calcIrms(1480); //Calcula a corrente que passa pelo fio
  potencia = corrente * valor_tensao; // Calcula a potência do dispositivo

  if (corrente < 0.4){
    corrente = 0.0;
    potencia = 0.0;
  }
 
  consumo = potencia / 1000; // Calcula o consumo de energia me Kw
  custo_energia = consumo * (tarifa / 60); //Calcula o custo do consumo de acordo com a tarifa da cidade de João Pessoa
  total_custo = total_custo + custo_energia; // Variável que recebe o custo e atualiza a cada loop
  char custo[6];
  dtostrf(total_custo, 5, 4, custo); // Transforma de ponto flutuante para string (para exibir no display)

  char limite[6];
  dtostrf(limite_custo, 5, 1, limite);
  
  numpotpstr(potencia);
  dtostrf(corrente, 4, 1, corrente_tela); // 4 define o tamanho max da string e 1 é a quantidade de "numeros" apos o ponto

  char consumo_tela[6];
  dtostrf(consumo, 5, 4, consumo_tela);

  piscarled(8, 9, total_custo, limite_custo);
  u8g.firstPage(); // Mostra os valores da corrente e potência no display
  do {
    u8g.setFont(u8g_font_8x13B);
    u8g.setContrast(100);
    u8g.drawStr(0, 20, "Corrente:");
    u8g.drawStr(70, 20, corrente_tela);
    u8g.drawStr(105, 20, "A");
    u8g.drawStr(0, 40, "----------------");
    u8g.drawStr(0, 60, "Potencia:");
    u8g.drawStr(75, 60, potencia_tela);
    u8g.drawStr(108, 60, "W");
  } while (u8g.nextPage());

  if (tempo_atual - tempo_anterior  >= 60000){
    u8g.firstPage(); // Mostra os valores do consumo e custo no display após um minuto
    do {
      u8g.drawStr(0, 20, "Consumo: ");
      u8g.drawStr(70, 20, consumo_tela);
      u8g.drawStr(85, 35, "kwh");
      u8g.drawStr(0, 40, "----------------");
      u8g.drawStr(0, 60, "Custo: ");
      u8g.drawStr(53, 60, "R$");
      u8g.drawStr(70, 60, custo);
    } while (u8g.nextPage());
    tempo_anterior = tempo_atual;

  }
  delay(3000); // Tempo para exibir os valores de corrente e potência novamente
}

void numpotpstr(double pot){
  dtostrf(pot, 4, 1, potencia_tela);// Transforma de ponto flutuante para string (para exibir no display)
}

void piscarled(int pino1, int pino2, double tot_custo, double lim_custo){
    if (tot_custo > lim_custo){
      digitalWrite(pino1, LOW);
      digitalWrite(pino2, HIGH);
      delay(50);
      digitalWrite(pino2, LOW);
    } else {
      digitalWrite(pino1, LOW);
      digitalWrite(pino2, LOW);
      delay(50);
      digitalWrite(pino1, HIGH);
    }
}


