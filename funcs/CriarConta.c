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
char contaTransf[25];

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
            exit(1); //fecha o programa
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
                printf("\nBem vindo %s!",conta.nome);
                fclose(ptrfile);
                menuEscolhas();
                
            }
        } else{
            printf("\nERROR! Password ou Username errado!");
        }
    }
    fclose(ptrfile);

}  


void menuEscolhas()
{
    FILE *ptrFile;
    struct conta conta; //para poder usar na func
    int escolha;

    printf("\nO que pretendes fazer?");
    printf("\n1 : Ver informacao da conta");
    printf("\n2 : Fazer transferencia monetaria para outra conta\n");
    scanf("\n%i",&escolha);

    if(escolha == 1)
    {
        ptrFile = fopen("files/contas.bin","rb");

        while(fread(&conta,sizeof(conta), 1, ptrFile))
        {
            if (strcmp(conta.nome, verificarConta) == 0)
            {
                printf("\nInfo da conta ");
                printf("\nNome : %s\t Password : %s\t Montante: %i", conta.nome, conta.password, conta.montante);
            } 
        }
        fclose(ptrFile);
    }
    if (escolha == 2)
    {
        //FAZER A TRANSEFERENCIA DE SALDO
        int transferir;
        
        // 1-> abrir um file em modo leitura
        FILE *ptr, *ptr2;
        ptr = fopen("files/contas.bin", "rb"); //para ler o conteudo do ficheiro
        ptr2 = fopen("files/replica.bin", "wb"); //este ficheiro sera a copia do anterior com todas as contas menos a do user em questão
        printf("\nQuanto queres transeferir? ( € )");
        scanf("%i",&transferir);
        //COPIAR TODAS AS INFOS DAS CONTAS PARA O replica.bin MENOS DO USER EM QUESTAO
        
        while(fread(&conta,sizeof(conta), 1, ptr))
        {
            if (strcmp(conta.nome, verificarConta) == 0) //SE O USER FOR IGUAL
            {
                if(conta.montante > transferir)
                {
                    conta.montante = conta.montante - transferir; //subtrair o saldo em conta
                }
                else{
                    printf("\nERROR! NAO TENS DINHEIRO QUE PARA EFETUAR ESTA TRANSFERENCIA");
                }
            }else{
                fwrite(&conta,sizeof(conta),1,ptr2); //COPIA AS INFOS PARA O NOVO FICHEIRO
            }
        }

        fwrite(&conta,sizeof(conta),1,ptr2); // ISTO E PARA ASSEGURAR QUE APENAS UMA INSTANCIA DE DADOS DO MESMO USER E GRAVADA

        fclose(ptr);
        fclose(ptr2);
      
       // remove("files/contas.bin");
       // rename("files/replica.bin", "files/contas.bin");

        //adicionar o saldo a outra conta

        printf("\nPara qual conta queres transferir?");
        scanf("%s",&contaTransf);

        //abrir o ficheiro para leitura
       rewind(ptr);
       rewind(ptr2);

       remove("files/contas.bin");
       rename("files/replica.bin", "files/contas.bin");

       ptr = fopen("files/contas.bin", "rb"); //para ler o conteudo do ficheiro
       ptr2 = fopen("files/replica2.bin", "wb");

       //rewind(ptr);
       //rewind(ptr2);

        //percorrer o ficheiro pela conta que recebe o saldo
        while(fread(&conta, sizeof(conta), 1, ptr))
        {
            if (strcmp(conta.nome , contaTransf) == 0) //se o nome for igual no ficheiro
            {
                printf("A transferir!");
                conta.montante = conta.montante + transferir;
                fwrite(&conta, sizeof(conta),1,ptr2);
            }else{
                fwrite(&conta, sizeof(conta),1,ptr2);
            }   
            
        }

        fwrite(&conta, sizeof(conta), 1,ptr2);

        fclose(ptr);
        fclose(ptr2);

        remove("files/contas.bin");
        rename("files/replica2.bin", "files/contas.bin");

         //se nao resolver trocar o fileptr2 para "ab" e a abrir o contas.bin 
    }
}


    

