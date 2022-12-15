#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "serial.h"
#include "memoria.h"
#include <inttypes.h>

extern "C" void app_main();
int v = 0;

void inserirRegistro();
void listaTodosRegistros();
void pesquisaPorNome();
void pesquisaPorTelefone();
void removerRegistroPorTelefone();
void quantidadeRegistros();
void inicializarBancoDeDados();

void app_main()
{

  while (1)
  {
    printf("\n\n\n\n\n\n\n\n\n=====================================");

    serial.begin(115200);

    printf("\n\t\tMENU\n\n");
    printf("[0] - Inserir registro\n");
    printf("[1] - Lista todos os registros\n");
    printf("[2] - Pesquisa registro por nome\n");
    printf("[3] - Pesquisa registro por telefone\n");
    printf("[4] - Remove registro baseado no telefone\n");
    printf("[5] - Mostra a quantidade de registros atualmente armazenados\n");
    printf("[6] - Inicializa o banco de dados (todas as informacoes armazenadas serao perdidas)\n");
    char opcao = serial.readChar();
    switch (opcao)
    {
    case '0':
      inserirRegistro();
      break;

    case '1':
      listaTodosRegistros();
      break;

    case '2':
      pesquisaPorNome();
      break;
    case '3':
      pesquisaPorTelefone();
      break;
    case '4':
      removerRegistroPorNome();
      break;
    case '5':
      quantidadeRegistros();
      break;

    case '6':
      inicializarBancoDeDados();
      break;
    }
  }
}

typedef struct
{
  char nome[20];
  char end[30];
  char tel[14];
} registro;

typedef struct
{
  uint16_t quantidadeAtual;
  uint16_t quantidadeTotal;
} cabecalho;

void inserirRegistro()
{
  Memoria memoria_i2c = Memoria();
  memoria_i2c.init(0);
  cabecalho cab;

  memoria_i2c.le(0, (uint8_t *)&cab, sizeof(cabecalho));

  if (cab.quantidadeAtual < cab.quantidadeTotal)
  {

    registro reg;

    uint8_t leitor[100];

    printf("Cadastrar contato\n------------------\nEntre com o nome: ");

    serial.readString(leitor, 20);
    strcpy(reg.nome, (char *)leitor);
    printf("%s\n", reg.nome);

    printf("\nEntre com o endereco: ");

    serial.readString(leitor, 30);
    strcpy(reg.end, (char *)leitor);
    printf("%s\n", reg.end);

    printf("\nEntre com o telefone: ");

    serial.readString(leitor, 14);

    strcpy(reg.tel, (char *)leitor);
    printf("%s\n", reg.tel);

    registro reg2;

    memoria_i2c.escreve(4 + 64 * cab.quantidadeAtual, (uint8_t *)&reg, 64);
    memoria_i2c.le(4 + 64 * cab.quantidadeAtual, (uint8_t *)&reg2, 64);

    cab.quantidadeAtual++;
    memoria_i2c.escreve(0, (uint8_t *)&cab, 4);

    printf("\n\nValor salvo:\n");
    printf("\nNome: %s\nEndereco: %s\nTelefone: %s\n", reg2.nome, reg2.end, reg2.tel);

    char sair[1];
    printf("\n\nPressione qualquer tecla para voltar ao menu");
    serial.readString((uint8_t *)sair, 1);
  }

  else
  {
    printf("\nVoce nao possui memoria\n");
  }
}

void listaTodosRegistros()
{
  char sair[1];

  printf("Contatos\n------------------\nAqui estao todos os seus contatos:\n\n ");

  Memoria memoria_i2c = Memoria();
  memoria_i2c.init(0);
  cabecalho cab;

  memoria_i2c.le(0, (uint8_t *)&cab, 4);

  if (cab.quantidadeAtual == 0)
  {
    printf("Voce nao possui nenhum contato salvo\n");
  }

  else
  {
    printf("\nVoce possui %d contatos!\n---------------------\n", cab.quantidadeAtual);

    for (size_t i = 0; i < cab.quantidadeAtual; i++)
    {
      registro reg;
      memoria_i2c.le(4 + i * 64, (uint8_t *)&reg, 64);

      printf("\n\tNome: %s\t\tTelefone: %s\t\tEndereco: %s", reg.nome, reg.tel, reg.end);
    }
  }

  printf("\n\nPressione qualquer tecla para voltar ao menu");
  serial.readString((uint8_t *)sair, 1);
}

void pesquisaPorNome()
{
  char nome[100];

  printf("Buscar contato\n------------------\nEntre com o nome: ");

  serial.readString((uint8_t *)nome, 10);
  printf("%s\n", nome);

  registro regComp;
  strcpy(regComp.nome, nome);

  Memoria memoria_i2c = Memoria();
  memoria_i2c.init(0);
  cabecalho cab;

  memoria_i2c.le(0, (uint8_t *)&cab, 4);

  if (cab.quantidadeAtual == 0)
  {
    printf("Voce nao possui nenhum contato salvo\n");
  }

  else
  {

    int achou = 0;
    for (size_t i = 0; i < cab.quantidadeAtual; i++)
    {
      registro reg;
      memoria_i2c.le(4 + i * 64, (uint8_t *)&reg, 64);

      int comparei = strcmp(reg.nome, regComp.nome);

      if (comparei == 0)
      {
        printf("\n\tNome: %s\t\tTelefone: %s\t\tEndereco: %s", reg.nome, reg.tel, reg.end);
        achou++;
      }
    }

    if (achou == 0)
    {
      printf("\nNenhum registro encontrado\n");
    }
  }

  printf("\n\nPressione qualquer tecla para voltar ao menu");
  serial.readString((uint8_t *)nome, 1);
}

void pesquisaPorTelefone()
{
  char tel[100];

  printf("Buscar contato\n------------------\nEntre com o tel: ");

  serial.readString((uint8_t *)tel, 10);
  printf("%s\n", tel);

  registro regComp;
  strcpy(regComp.tel, tel);

  Memoria memoria_i2c = Memoria();
  memoria_i2c.init(0);
  cabecalho cab;

  memoria_i2c.le(0, (uint8_t *)&cab, 4);

  if (cab.quantidadeAtual == 0)
  {
    printf("Voce nao possui nenhum contato salvo\n");
  }

  else
  {

    int achou = 0;
    for (size_t i = 0; i < cab.quantidadeAtual; i++)
    {
      registro reg;
      memoria_i2c.le(4 + i * 64, (uint8_t *)&reg, 64);

      int comparei = strcmp(reg.tel, regComp.tel);

      if (comparei == 0)
      {
        printf("\n\tNome: %s\t\tTelefone: %s\t\tEndereco: %s", reg.nome, reg.tel, reg.end);
        achou++;
      }
    }

    if (achou == 0)
    {
      printf("\nNenhum registro encontrado\n");
    }
  }

  printf("\n\nPressione qualquer tecla para voltar ao menu");
  serial.readString((uint8_t *)tel, 1);
}

void removerRegistroPorNome()
{

  printf("\tRemover contato\n------------------\nEntre com o nome: ");

  char nome[100];

  serial.readString((uint8_t *)nome, 20);
  printf("%s\n", nome);

  registro regComp;
  strcpy(regComp.nome, nome);

  Memoria memoria_i2c = Memoria();
  memoria_i2c.init(0);
  cabecalho cab;

  memoria_i2c.le(0, (uint8_t *)&cab, 4);

  if (cab.quantidadeAtual == 0)
  {
    printf("Voce nao possui nenhum contato salvo\n");
  }

  else
  {

    int achou = 0;
    for (size_t i = 0; i < cab.quantidadeAtual; i++)
    {
      registro reg;
      memoria_i2c.le(4 + i * 64, (uint8_t *)&reg, 64);

      int comparei = strcmp(reg.nome, regComp.nome);

      if (comparei == 0)
      {

        registro ultimoReg;
        memoria_i2c.le(4 + (cab.quantidadeAtual-1) * 64, (uint8_t *)&ultimoReg, 64);
        memoria_i2c.escreve(4 + i * 64, (uint8_t *)&ultimoReg, 64);

        cabecalho cab;
        memoria_i2c.le(0, (uint8_t *)&cab, 4);
        cab.quantidadeAtual--;
        memoria_i2c.escreve(0, (uint8_t *)&cab, 4);

        achou++;
        printf("\n\tNome: %s\t\tTelefone: %s\t\tEndereco: %s\n", reg.nome, reg.tel, reg.end);
        printf("\t--Contato removido\n");

        break;
      }
    }

    if (achou == 0)
    {
      printf("\nNenhum registro encontrado\n");
    }
  }

  printf("\n\nPressione qualquer tecla para voltar ao menu");
  serial.readString((uint8_t *)tel, 1);
}

void quantidadeRegistros()
{

  Memoria memoria_i2c = Memoria();
  memoria_i2c.init(0);

  cabecalho cab;

  memoria_i2c.le(0, (uint8_t *)&cab, 4);

  printf("\nQuantidade de contatos\n------------------\nVoce possui %d contatos registrados.", cab.quantidadeAtual);

  char sair[1];
  printf("\n\nPressione qualquer tecla para voltar ao menu");
  serial.readString((uint8_t *)sair, 1);
}

void inicializarBancoDeDados()
{
  printf("\nInicializar banco de dados!\n");

  Memoria memoria_i2c = Memoria();
  memoria_i2c.init(0);

  cabecalho cab;
  cab.quantidadeAtual = 0;
  cab.quantidadeTotal = 1023;

  memoria_i2c.escreve(0, (uint8_t *)&cab, 4);

  printf("Cabecalho: %d e %d\n", cab.quantidadeAtual, cab.quantidadeTotal);

  printf("\n------------------\nBanco de dados inicializado!");

  char sair[1];
  printf("\n\nPressione qualquer tecla para voltar ao menu");
  serial.readString((uint8_t *)sair, 1);
}