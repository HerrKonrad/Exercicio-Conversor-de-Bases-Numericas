#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Exercício: Programa de conversão de bases numérica
 * Autor: Arthur Konrad
 * 2021
 * Um pequeno programa para treino que consiste em transformar numeros de diferentes bases numéricas,
 * podemos transformar por exemplo binários para hexedecimais, base 5 para base 10 e por assim vai,
 * até a base 36, cujo usa todos os digitos e letras do alfabeto em inglês (0..9) (a..z)
 * Para bases acima de 10, pode se utilizar as letras do alfabeto em maisculo ou minusculo
 * A conversão de caracteres é utilizando a tabela ASCII
*/


enum ASCII
{
    INI_DIGITOS = '0',
    FIM_DIGITOS = '9',
    INI_MINUSCULO = 'a',
    FIM_MINUSCULO = 'z',
    INI_MAIUSCULO = 'A',
    FIM_MAIUSCULO = 'Z',
    MINUSCULO_PARA_DIGITO = 87,
    MAIUSCULO_PARA_DIGITO = 55



};

// Está é a parte "lógica" do programa

const char* inverterString(char str[])
{
    char* temp = str;
    int n = strlen(str);
    size_t i;

    for (i = 0; i < n / 2; i++)
    {
        char ch = temp[i];
        temp[i] = temp[n - i - 1];
        temp[n - i - 1] = ch;
    }
    const char* resultado = temp;
    return resultado;
}

int validarValorBase(size_t numeroBase)
{
    int valido = 0;

    if(numeroBase < 0 || numeroBase > 36)
    {
        valido = 0;
    }
    else
    {
        valido = 1;
    }

    return valido;
}

/*
  INI_DIGITOS = 48,
    FIM_DIGITOS = 57,
    INI_MINUSCULO = 97,
    FIM_MINUSCULO = 122,
    INI_MAIUSCULO = 65,
    FIM_MAIUSCULO = 90,
    MINUSCULO_PARA_DIGITO = 87,
    MAIUSCULO_PARA_DIGITO = 55

*/

int arrumarDigitoParaDecimal(char digito)
{
    long digitoAjustado = 0;
    if(digito >= INI_DIGITOS && digito <= FIM_DIGITOS)
    {
        digitoAjustado = digito - INI_DIGITOS;
    }
    else if (digito >= INI_MINUSCULO && digito <= FIM_MINUSCULO)
    {
        digitoAjustado = digito - MINUSCULO_PARA_DIGITO; //Aqui transformamos as letras minusculas do alfabeto [a..z] em conspondente de numeros, começando a como 10, b como 11, c como 12 assim por diantae
    }
    else if (digito >= INI_MAIUSCULO && digito <= FIM_MAIUSCULO)
    {
        digitoAjustado = digito - MAIUSCULO_PARA_DIGITO; //Aqui transformamos as letras MAIUSCULAS do alfabeto [A..Z] em conspondente de numeros, começando A como 10, B como 11, C como 12 assim por diante
    }
    else
    {
        digitoAjustado = -1; //Já que o digito realmente pode ser ZERO, bora devolver um numero diferente, vamos convencionar -1
    }
    // printf("digito arrumado: %d  \n", digitoAjustado);
    return digitoAjustado;
}

char arrumarDigitoDeDecimal(long digito)
{
    char digitoAjustado = 0;

    if(digito <= 9)
    {
        digitoAjustado = abs(digito) + 0x30; //Vamos transformar nosso digito de int para char
    }
    else if(digito >= 10 && digito <= 35)
    {
        digitoAjustado = digito + 55; //vamos transformar o 10 em A, o 11 em B, assim por diante
    }
    else
    {
        digitoAjustado = 0; //Estamos lidando com char... para nosso erro vamos retornar um char nulo (0)
    }

    return digitoAjustado;
}


int validarValorNumero(char* valor, int base)
{
    size_t i;
    int valido = 0;
    int digitoAjustado = 0;
    for(i = 0 ; i < strlen(valor) ; i++)
    {
        digitoAjustado = arrumarDigitoParaDecimal(valor[i]);
        if( digitoAjustado < base && digitoAjustado > - 1)
        {
            valido = 1;
        }
        else
        {
            valido = 0;
            break;
        }
    }
    return valido;
}

int transformarParaBaseDecimal(char *valor, int baseAtual)
{
    long numeroFinal = 0;
    long tamanhoNumero = strlen(valor);
    long numTemp = 0;
    size_t i;

    for(i = 0  ; i < tamanhoNumero ; i++ )
    {
        numTemp = arrumarDigitoParaDecimal(valor[i]);
        numeroFinal += round (numTemp *  ( pow(baseAtual, (tamanhoNumero - (i+1))))); //GAMBIARRA
    }

    return numeroFinal;
}

const char* transformarDeDecimal(long valorDecimal, int novaBase)
{
    long numTemp = valorDecimal;
    size_t i;
    char buffer[251];
    size_t fim = 0;
    const char* resultado;

    for( i = 0 ; numTemp > 0 ; i++ )
    {
        buffer[i] = arrumarDigitoDeDecimal((numTemp % novaBase));

        numTemp /= novaBase;
        fim = i + 1;
    }
    buffer[fim] = 0;
    resultado = inverterString(buffer);
    return resultado;
}

//Aqui começa a parte mais dedicada a interacao com usuario

int pedirValorBase(int opcao)
{
    int numBase = 0;

    switch(opcao)
    {
    case 1:
        puts("Digite valor da base do numero que deseja transformar (ate 36)");
        break;
    case 2:
        puts("Valor da nova base");
        break;
    default:
        puts("erro");
    }

    if(!scanf("%d", &numBase)) // ARUMAR DPS
    {

        puts("\n Por favor apenas numeros decimais!");
        while(fgetc(stdin)!='\n');
        numBase = pedirValorBase(opcao);
    }
    if(!validarValorBase(numBase))
    {
        puts("Base invalida");
        pedirValorBase(opcao);
    }

    return numBase;
}

void mostrarInterface()
{
    int base1 = pedirValorBase(1);
    char num1[128];
    int base2 = 0;

    do
    {

    printf("Digite o valor do numero: \n");
    scanf("%s", &num1);

    }while(!validarValorNumero(num1, base1));

    base2 = pedirValorBase(2);

    long numeroDecimal = transformarParaBaseDecimal(num1, base1);
    char* numeroFinal = transformarDeDecimal(numeroDecimal, base2);

    printf("Resultado: %s\n", numeroFinal);
}

int pedirContinuarPrograma()
{
    int continuar = 0;
    char escolha;

    puts("Deseja continuar? S/N");
    scanf(" %c", &escolha);

    if(escolha == 's' || escolha == 'S')
    {

        continuar = 1;
    }
    else
    {
        continuar = 0;
    }
    return continuar;
}



int main()
{
    int continuar = 0;
    printf(" ######################################### \n");
    printf(" PROGRAMA DE CONVERSAO DE BASES NUMERICAS \n");
    printf(" ######################################### \n \n");


    do
    {
        mostrarInterface();
        continuar = pedirContinuarPrograma();
    }
    while(continuar);



    return 0;
}
