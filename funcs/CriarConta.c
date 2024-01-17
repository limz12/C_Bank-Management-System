

#include <stdio.h>
#include <stdlib.h>
// Library where getch() is stored
#include <conio.h>

typedef struct contaBancaria
{
    char nome[25];
    char password[30];
    int montante;
}CONTABANCARIA;

void signup()
{
    struct contaBancaria conta;
    FILE *fileptrA, *fileptrB;
    

    printf("\nBem vindo ao registo do banco XPTO!");
    printf("\nPretende criar uma conta? <s/n>");
    if (getch()== 's' )
    {
        printf("\nQual e o nome da conta?");
        scanf ("\n%s", &conta.nome);
        printf("\nQual e a palavra-passe?");
        scanf("\n%s", &conta.password);

        fileptrA = fopen("files/contas.bin","a");

        //adicionar o montante de 1000€
        conta.montante = 1000;
        //adicionar estas variaveis ao ficheiro
        fwrite(&conta, sizeof(conta), 1, fileptrA);
        printf("Conta criada com sucesso!");
        fclose(fileptrA);
     }  
 }

 void leitura()
 {
    CONTABANCARIA conta;
    FILE *fileptrB;

    fileptrB = fopen("files/contas.bin","rb");
    
    while(fread(&conta, sizeof(CONTABANCARIA), 1, fileptrB))
    { 
        printf("%s\t%s\t%i\n", conta.nome, conta.password, conta.montante);
    }
    fclose(fileptrB);
 }
    