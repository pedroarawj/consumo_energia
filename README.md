Projeto de Análise do Consumo de Energia em dispositivo individual

Este projeto foi desenvolvido como parte da disciplina Introdução a Engenharia da Computação, ministrada pelo Prof Dr. Anand Subramanian na Universidade Federal da Paraíba. O tema era livre, e deveríamos utilizar Arduino ou um dispositivo equivalente para criar um projeto inovador e funcional.

---

Descrição do Projeto

O projeto foi inspirado na biblioteca EmonLib e no projeto do Maker Hero. Utilizamos um sensor de corrente para medir a corrente e posteriormente, exibir tais dados em um display.

---


Créditos:

[Biblioteca EmonLib](https://github.com/openenergymonitor/EmonLib/tree/master)

[Projeto Maker Hero](https://www.makerhero.com/blog/medidor-de-corrente-sct013-com-arduino/)




**Bibliotecas utilizadas:**

  1 - 'EmonLib.h'
  
  2 - 'U8glib.h'
  

**Materiais utilizados:** 

  1 - Arduino Uno R3

  2 - Display Gráfico ST7920 128x64
  
  3 - Protoboard 830 pontos
  
  4 - Jumpers para as conexões
  
  5 - Sensor de Corrente Não Invasivo STC 100
  
  6 - Conector Jack P2 Fêmea
  
  7 - Capacitor 100 uF
  
  8 - 3 resistores de 10.000 ohms e 1 resistor de 30 ohms

  ---
  

**Funcionalidades:**

  1 - Medir a corrente através de um sensor
       O sensor utilizado foi o sensor de corrente não invasivo STC-013 100A 50mA.
      
  2 - Calcular a potência através da corrente
       A tensão para análise foi definida como 220V.
      
  3 - Dados mostrados na tela do display ST7920 128x64
  
  4 - Calcular o consumo de energia do dispositivo

  5 - Calcular o custo em reais desse consumo
