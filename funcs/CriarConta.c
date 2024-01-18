#include <stdio.h>
#include <stdlib.h>
// Library where getch() is stored
#include <conio.h>

typedef struct conta
{
    char nome[25];
    char password[30];
    int montante;
}CONTABANCARIA;

char verificarConta[25];
char veriricarPass[30];

void signup()
{
    struct conta conta;
    FILE *fileptrA;

    printf("\nBem vindo ao registo do banco XPTO!");
    printf("\nPretende criar uma conta? <s/n>");
    if (getch()== 's' )
    {
        printf("\nQual e o nome da conta? :");
        scanf ("\n %s", &conta.nome);
        printf("Repete o nome da conta :");
        scanf ("\n %s", &verificarConta);
        printf("Qual e a palavra-passe? :");
        scanf("\n %s", &conta.password);
        
        fileptrA = fopen("files/contas.bin","ab");
        if (strcmp(conta.nome,verificarConta) == 0)
        {
            leituraVerificar();

            //adicionar o montante de 1000€
            conta.montante = 1000;
            //adicionar estas variaveis ao ficheiro
            fwrite(&conta, sizeof(conta), 1, fileptrA); //GUARDAR TUDO O QUE É DA CONTA
            printf("Conta criada com sucesso!");
            fclose(fileptrA);
        }else{
            printf("ERRO! Introduziste nomes diferentes!");
        }
    }

}
 void leituraVerificar() //Verificar se a conta já existe no ficheiro se sim da exit do programa!
 {
    struct conta conta;
    FILE *fileptrB;

    fileptrB = fopen("files/contas.bin","rb");
    while(fread(&conta, sizeof(CONTABANCARIA), 1, fileptrB)) // LE LINHA A LINHA E DA PRINT DO CONTEUDO
    { 
        if(strcmp(conta.nome, verificarConta) == 0)
        {
            printf("ERRO! Esta conta ja existe!\n");
            fclose(fileptrB);
            exit(1); //E salta novamente para o signup() continuando da linha 36 para a frente
        }
    }
 }
  
  
void login() //FUNCAO PARA DAR  LOGIN NA CONTA
{  
    struct conta conta; //para poder usar na func

    
    printf("\nBem vindo ao sistema de Login do Banco XPTO!");
    printf("\nInsira a nome da sua conta : ");
    scanf("\n%s",&verificarConta);
    printf("Insira a sua palavra passe : ");
    scanf("\n%s",&veriricarPass);

    //ABRIR O ficheiro para leitura
    FILE *ptrfile;
    ptrfile = fopen("files/contas.bin","rb");

    //Ler o ficheiro à procura de um user igual com a mesma passe
    while(fread(&conta,sizeof(CONTABANCARIA), 1, ptrfile)) //VAI LER O FICHEIRO LINHA A LINHA
    {
        if(strcmp(conta.nome, verificarConta) == 0)
        {
            if(strcmp(conta.password, veriricarPass) == 0)
            {
                printf("\nBem vindo à conta %s!",conta.nome);
                printf("\nTens na conta : %i€",conta.montante);
                fclose(ptrfile);
            }
        } else{
            printf("\nERROR! Password ou Username errado!");
        }
    }
    fclose(ptrfile);
}  