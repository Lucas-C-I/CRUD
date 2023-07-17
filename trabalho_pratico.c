#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
typedef struct NO{
    int code;
    int rg;
    char Nome[50]; 
    char doc[20]; 
    int vencimento[3];
    int titularidade;
    struct NO * esq;
    struct NO * dir;

}NO;

// Inicialização da raiz da árvore
NO * raiz=NULL;

NO * adicionar(NO*aux,NO*novo); // Adiciona um novo nó à árvore
NO * delete(NO* aux,int code); // Remove um nó da árvore
NO * search(int code, NO*aux); // Procura por um nó na árvore

void recuperar_dados(FILE * reg); // Lê os dados de um arquivo e cria a árvore
void arquivar(FILE * reg,NO * aux); // Salva os dados da árvore em um arquivo


void cadastrar(); // Cadastra um novo documento
void remover(int code); // Remove um documento da árvore
void alterar(int code); // Altera os dados de um documento
void buscar(int code);  // Busca por um documento na árvore


int check (); // Verifica se a árvore está vazia
int check_aux(NO*aux); // Verifica se um nó existe na árvore
NO * copiar_data (NO* aux,NO * aux2); // Copia os dados de um nó para outro
NO * sucessorinor (NO* aux2); // Encontra o sucessor de um nó na árvore

int main()
{
    // Criação do arquivo
    FILE * registro;
    int code, R;
    char ID,*arq =malloc(sizeof(char)*15);
    arq="Registro 1.txt";
    
    // Nesse trecho é possível que o usuário opte por reutilizar informações passadas em sessões anteriores no arquivo
    int N=0;
    if(fopen("registro.txt","r"))
    {
        printf("Bem vindo ao sistema de gerenciamento de arquivos!\nVoce quer\n[1] Acessar os dados da sessao anterior \n[2] Iniciar a sessao do zero(os dados da sessao anterior serao apagados)\n\n");
        scanf("%d",&R);
        
        if(R==1)
        {
            registro = fopen("registro.txt","r");
            recuperar_dados(registro);
            fclose(registro);
        }      
    
    }
    for(int a = 0; a != 5;){ // Nesse for o usuário vai escolher o que quer fazer com o documento enquanto ele não selecionar sair

        printf("\n\nO que deseja fazer?\n[1] Cadastrar um novo documento \n[2] Excluir um documento \n[3] Alterar os dados em um documento\n[4] Buscar documento \n[5] Sair e arquivar dados\n");
        scanf("%d", &a);

       // A partir daqui é chamada a função de acordo com a seleção do usuário
        if(a == 1){

            cadastrar();           
        }
       
       
        if(a == 2)
        {
            if(check())
            {
                printf("Informe a code a ser removida: \n");
                scanf("%d", &code);
                remover(code);
            }
                 
        }


        if(a == 3)
        {
            if(check())
            {
                printf("Informe a code a ter os dados alterados:\n");
                scanf("%d", &code);
                alterar(code);
            }

            
        }
        
    
        if(a == 4)
        {
            if(check())
            {
                 printf("Informe a code a ser buscada:\n");
                 scanf("%d", &code);
                 buscar(code);
            }          
                
        }
    
    
        if(a == 5)
        {
            registro=fopen("registro.txt","w");
            arquivar(registro,raiz);
            printf("Dados registrados no arquivo de nome <registro.txt>\nObrigado por usar o Sistema de Gerenciamento de Documentos!\n");
        }
    }
    
    
    
    return 0;
}

void cadastrar() // Nessa função é feito o cadastro do documento a partir das informações inseridas pelo usuário
{
    NO * Novo=malloc(sizeof(NO));
    printf("Informe o codigo do documento:\n");
    scanf("%d",&Novo->code);

    if (search(Novo->code,raiz)!=NULL)
    {
        printf("Ja existe um documento com esse codigo.\n\n");
    }
    
    else
    {
        
        printf("Informe o nome do dono do documento:\n");
        scanf("%s",&Novo->Nome);

        printf("Informe o RG do de %s\n",Novo->Nome);
        scanf("%d",&Novo->rg);

        printf("Informe qual o documento:\n");
        scanf("%s",&Novo->doc);

        printf("Informe a data de vencimento na forma dd/mm/aa:\n");
        int x=0;
        for(char temp='/';temp=='/';x++)
        {
            scanf("%d%c",&Novo->vencimento[x],&temp);
        }

        printf("A titularidade pode ser alterada?\n[0]Nao\n[1]Sim\n");
        scanf("%d",&Novo->titularidade);

        Novo->dir=NULL;
        Novo->esq=NULL;

    }
    if (raiz==NULL)
    {
        raiz=Novo;
    }
    else
    {
        adicionar(raiz,Novo);
        printf("Documento cadastrado com sucesso\n\n");
    }

} 


void remover(int code) // Nessa função será removido um documento que foi inserido no arquivo anteriormente
{
    if(check())
    {
        if(check_aux(search(code,raiz)))
        {
             if((raiz->dir==NULL) && (raiz->esq==NULL)) 
          {
            raiz=NULL;
          }       
           else
           {
             delete(raiz,code);
             printf("Remocao realizada com sucesso\n\n");
           }
        }
    }
}

void alterar(int code) // Nessa função o usuário pode alterar um dado específico de um determinado documento, de acordo com a escolha do usuário
{
    NO* aux= search(code,raiz);
    char temp;
    if(check_aux(aux))
    {
        printf("\nDocumento:%s \nDono:%s \nData de Vencimento:%d/%d/%d\n\n",aux->doc,aux->Nome,*(aux->vencimento),*(aux->vencimento+1),*(aux->vencimento+2));
        for(int R=0;R!=3;)
        {
            printf("Quais dados deseja alterar?\n[1]Data de Vencimento\n[2]Titularidade\n[3]Finalizar alteracoes\n");
            scanf("%d",&R);
            
           if(R==1)
           { 
            
            printf("Informe a data de vencimento atualizada:\n");
            int x=0;
            for(temp='/';temp=='/';x++)
            {
                scanf("%d%c",&aux->vencimento[x],&temp);
            
            }
           }

           if(R==2)
           {
            if(aux->titularidade)
            {
                printf("Informe o nome do novo dono:\n");
                scanf("%s",aux->Nome);
                printf("Informe o RG de %s",aux->Nome);
                scanf("%d",&aux->rg);
            }
            else
            {
                printf("O documento em questao nao pode ter titularidade alterada\n");
            }
           }


            if(R==3)
            {
                printf("Funcionalidade de alteracoes finalizada");       
            }
        }


    }
}

void buscar(int code) // Nessa função o usuário consegue buscar um documento e receber as informações do mesmo
{
    NO*aux=search(code,raiz);
    if(check_aux(aux))
    {
        printf("\nDono:%s \nDocumento:%s   Vencimento:%d/%d/%d",aux->Nome,aux->doc,*aux->vencimento,*(aux->vencimento+1),*(aux->vencimento+2));
    }
}

// Função para recuperar os dados do arquivo e criar a árvore correspondente
void recuperar_dados(FILE * reg) 
{
    NO * aux= malloc(sizeof(NO));
    aux->code = getw(reg);
    do
    {       
        // Lê os dados do arquivo para o nó atual
        aux->rg=getw(reg);
        aux->titularidade=getw(reg);
        *(aux->vencimento)=getw(reg);
        *(aux->vencimento+1)=getw(reg);
        *(aux->vencimento+2)=getw(reg);
        fscanf(reg,"%s",aux->Nome);
        fscanf(reg,"%s",aux->doc);

        aux->esq=aux->dir=NULL;
        if(raiz==NULL)
        {
            raiz=aux;
        }
        else
        {
            adicionar(raiz,aux);
        }
        aux= malloc(sizeof(NO));
        fgetc(reg);
        aux->code = getw(reg);
    } while (aux->code>0);
    
}

// Função para arquivar os dados da árvore em um arquivo
void arquivar(FILE * reg, NO*aux)
{
    // Salva os dados do nó atual no arquivo
     putw(aux->code,reg);         
     putw(aux->rg,reg);
     putw(aux->titularidade,reg);
     putw(*(aux->vencimento),reg);
     putw(*(aux->vencimento+1),reg);
     putw(*(aux->vencimento+2),reg);
     fprintf(reg,aux->Nome);
     fprintf(reg,"\n");
     fprintf(reg,aux->doc);
     fprintf(reg,"\n");

    // Recursivamente arquiva os nós filhos (esquerda e direita
     if(aux->esq)
     {
        arquivar(reg,aux->esq);
     }
     if(aux->dir)
     {
        arquivar(reg,aux->dir);
     }
    
}

// Função para adicionar um novo nó à árvore
NO * adicionar(NO*aux,NO*novo)
{
   
     if (aux == NULL)
     {
        // Se o nó atual for nulo, o novo nó se torna o nó atual
        aux=novo;
     }
     else if (novo->code < aux->code)
     {
        // Se o código do novo nó for menor que o código do nó atual, adicionamos o novo nó à subárvore esquerda
        aux->esq = adicionar(aux->esq,novo);
     }
     else if(novo->code> aux->code)
     {
        // Se o código do novo nó for maior que o código do nó atual, adicionamos o novo nó à subárvore direita
        aux->dir = adicionar(aux->dir,novo);
     }
     return aux;

       
    }

// Função para remover um nó da árvore
NO * delete(NO* aux,int code)
{
    
    if(aux==NULL)
    {
        // Se o nó atual for nulo, retornamos o nó atual     
        return aux;
    }
    if (code < aux->code)
    {
        // Se o código for menor que o código do nó atual, removemos o código da subárvore esquerda
        aux->esq=delete(aux->esq, code);
    }
    else if (code > aux->code)
    {
        // Se o código for maior que o código do nó atual, removemos o código da subárvore direita
        aux->dir=delete(aux->dir,code);
    }
    else
    {
        // Se encontrarmos o nó com o código desejado
        if(aux->esq==NULL)
        {
             // Se a subárvore esquerda for nula, retornamos a subárvore direita
            return aux->dir;
        }
        else if (aux->dir==NULL)
        {
            // Se a subárvore direita for nula, retornamos a subárvore esquerda
            return aux->esq;
        }
        // Caso contrário, substituímos o nó atual pelo sucessor in-order e removemos o sucessor in-order da subárvore direita
        aux=copiar_data(aux,sucessorinor(aux->dir));
        aux->dir=delete(aux->dir,code);
        
    }
    return aux;

}

// Função para buscar um nó na árvore com base no código
NO * search(int code, NO*aux)
{    
        if (aux == NULL){
            // Função para buscar um nó na árvore com base no código
            return NULL;
        }    


        if (aux->code == code)
            // Se encontrarmos o nó com o código desejado, retornamos o nó atual
            return aux;

        if (code < aux->code)
            // Se o código for menor que o código do nó atual, buscamos na subárvore esquerda
            return search(code,aux->esq);

        else if (code > aux->code)
            // Se o código for maior que o código do nó atual, buscamos na subárvore direita
            return search(code,aux->dir);


        return NULL;
}

// Função para verificar se existem documentos cadastrados no sistema
int check ()
{
    if (raiz==NULL)
    {
        // Se a raiz for nula, não há documentos cadastrados
        printf("Nao ha documentos cadastrados no sistema\n\n");
        return 0;
    }
    else{
        // Caso contrário, há documentos cadastrados
        return 1;
    }
}

// Função para verificar se um documento com o código especificado está registrado no sistema
int check_aux(NO*aux)
{
    if(aux==NULL)
    {
        // Se o nó auxiliar for nulo, não há documento registrado com o código especificado
        printf("\nNao ha documento registrado no sistema com esse codigo\n");
        return 0;
    }
    else
    {
        // Caso contrário, há um documento registrado com o código especificado
        return 1;
    }
}

// Função para copiar os dados de um nó para outro nó
NO* copiar_data (NO* aux,NO * aux2)
{
        
        aux->code = aux2->code;
        *aux->doc = *aux2->doc;
        *aux->Nome = *aux2->Nome;
        aux->rg = aux->rg;
        aux->titularidade = aux2->titularidade;
        aux->vencimento[0]= aux2->vencimento[0];
        aux->vencimento[1]= aux2->vencimento[1];
        aux->vencimento[2]= aux2->vencimento[2];
        return aux;
}

// Função para encontrar o sucessor do nó aux2 na árvore (menor nó à direita)
NO* sucessorinor (NO* aux2)
{
   
    NO * aux =malloc(sizeof(NO));
    aux= copiar_data(aux,aux2);        
        
        while (aux2->esq)
        {
            aux=copiar_data(aux,aux2->esq);
            aux2=aux2->esq;
        }
        return aux;
} 

