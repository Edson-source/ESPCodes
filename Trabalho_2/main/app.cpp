#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "serial.h"
#include "delay.h"
#include <inttypes.h> 
#include "digital.h"

#include "esp_timer.h"

// Define pinos de trigger e eccho
#define trigPIN PIN16
#define echoPIN PIN5

// Inicializando as funções
float SetPoint();
void medeAltura();

float setPoint;

extern "C" void app_main();
int v = 0;


void app_main()
{
   serial.begin(9600);
   digital.pinMode(trigPIN, OUTPUT);
   digital.pinMode(echoPIN, INPUT);

   while(1)
   {
      printf("===========================\n");

      printf("\n\t\tMENU\n\n");
      printf("[1] Ajusta set point\n");
      printf("[2] Mede altura pessoal\n");
      printf("[0] sair\n");

      char opcao = serial.readChar();

      switch (opcao)
      {
      case '0':
         break;
      
      case '1':
         setPoint = SetPoint();
         printf("A distancia inicial eh: %ld cm\n", (long)setPoint);
         break;
      
      case '2':
         medeAltura();
         break;
      }
   }
}

float SetPoint()
{
   int64_t t1, t2, pulso_comp;
   float distancia;

   // "Limpa" o trigger
   digital.digitalWrite(trigPIN, LOW);
   delay_us(2);
   
   // Mede um pulso de 10 microsegundos
   digital.digitalWrite(trigPIN, HIGH);
   delay_us(10);
   digital.digitalWrite(trigPIN, LOW);


      while (digital.digitalRead(echoPIN) == LOW) {}

      t1 = esp_timer_get_time();

      while (digital.digitalRead(echoPIN) != LOW) {}

   t2 = esp_timer_get_time();

   pulso_comp = t2 - t1;

   distancia = (float)pulso_comp * 0.034 / 2;

   return distancia;
}

void medeAltura()
{
   float altura, diferenca;

   if(setPoint == 0)
   {
      printf("Impossivel fazer a medicao\n");
      printf("Sete um valor inicial primeiro\n");
   }
   else
   {
      printf("Pegando o valor da altura...\n");
      altura = SetPoint();
      delay_ms(100);

      diferenca = (setPoint - altura);

      delay_ms(100);
      printf("A altura calculada eh: %ld cm\n", (long)diferenca);
   }
}