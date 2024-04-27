# Projeto de Análise do Consumo de Energia em dispositivo individual

A ideia central do projeto é monitorar o consumo de energia em dispositivos eletrônicos de maneira individual, com o objetivo de conscientizar sobre o uso consciente da energia e reduzir gastos desnecessários.

*** OBS: O código foi inspirado no código base informado na biblioteca EmonLib ***
Créditos: https://github.com/openenergymonitor/EmonLib/tree/master

Bibliotecas utilizadas:
  1 - EmonLib.h
  2 - U8glib.h

Funcionalidades: 

  1 - Medir a corrente através de um sensor
      * O sensor utilizado foi o sensor de corrente não invasivo STC-013 100A 50mA.
      
  2 - Calcular a potência através da corrente
      * A tensão para análise foi definida como 5V.
      
  3 - Dados mostrados na tela do display ST7920 128x64
  
  4 - Calcular o consumo de energia do dispositivo

  5 - Calcular o custo em reais desse consumo

  6 - Definição de um limite de custo para análise
