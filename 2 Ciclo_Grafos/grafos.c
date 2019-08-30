#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>

struct Vertice
{
    int cor;
    char label;
    struct Vertice *prox;
};

typedef struct Vertice v[10];

int vercores(struct Vertice **l, int k, int i, int cor);

void MudarCor(int cor);
struct Vertice* Criar(struct Vertice **l, int tam);
void imprimir(struct Vertice **l);
void colorir(struct Vertice **l);
struct Vertice * insere(struct Vertice **l, char num);

int cores[10] = {1,2,3,4,5,6,7,8,9,10};
int tam = 6;

int main()
{
    setlocale(LC_ALL, "portuguese");
    int op1 = 0, op = 0;
    char nova;
    struct Vertice *l[tam];
    struct Vertice *outra;
    outra = (struct Vertice*)malloc(sizeof(struct Vertice));
    outra = NULL;
    system("cls");
    printf("1- Utilizar Grafo pré-definido\n2- Adicionar Grafo\n");
    scanf("%d", &op);
    if(op == 1)
    {
        system("cls");
        printf("1 - Grafo 1\n2 - Grafo 2\n");
        scanf("%d", &op1);
        if(op1 == 1)
        {
            tam = 8;
            Criar(l, tam);
            insere(&outra, '1');
            insere(&outra, '8');
            insere(&outra, '3');
            insere(&outra, '2');
            l[0] = outra;
            outra = NULL;
            insere(&outra, '2');
            insere(&outra, '1');
            insere(&outra, '3');
            insere(&outra, '7');
            l[1] = outra;
            outra = NULL;
            insere(&outra, '3');
            insere(&outra, '1');
            insere(&outra, '2');
            insere(&outra, '4');
            insere(&outra, '5');
            insere(&outra, '6');
            insere(&outra, '7');
            insere(&outra, '8');
            l[2] = outra;
            outra = NULL;
            insere(&outra, '4');
            insere(&outra, '3');
            insere(&outra, '5');
            insere(&outra, '6');
            l[3] = outra;
            outra = NULL;
            insere(&outra, '5');
            insere(&outra, '3');
            insere(&outra, '4');
            insere(&outra, '8');
            l[4] = outra;
            outra = NULL;
            insere(&outra, '6');
            insere(&outra, '3');
            insere(&outra, '4');
            insere(&outra, '7');
            l[5] = outra;
            outra = NULL;
            insere(&outra, '7');
            insere(&outra, '2');
            insere(&outra, '3');
            insere(&outra, '6');
            l[6] = outra;
            outra = NULL;
            insere(&outra, '8');
            insere(&outra, '1');
            insere(&outra, '3');
            insere(&outra, '5');
            l[7] = outra;
            outra = NULL;

        }
        else if(op1 == 2)
        {
            tam = 7;
            Criar(l,tam);
            insere(&outra, 'A');
            insere(&outra, 'B');
            insere(&outra, 'F');
            insere(&outra, 'G');
            l[0] = outra;
            outra = NULL;
            insere(&outra, 'B');
            insere(&outra, 'C');
            insere(&outra, 'A');
            l[1] = outra;
            outra = NULL;
            insere(&outra, 'C');
            insere(&outra, 'D');
            insere(&outra, 'F');
            insere(&outra, 'B');
            l[2] = outra;
            outra = NULL;
            insere(&outra, 'D');
            insere(&outra, 'C');
            insere(&outra, 'F');
            insere(&outra, 'E');
            l[3] = outra;
            outra = NULL;
            insere(&outra, 'E');
            insere(&outra, 'D');
            insere(&outra, 'G');
            l[4] = outra;
            outra = NULL;
            insere(&outra, 'F');
            insere(&outra, 'A');
            insere(&outra, 'C');
            insere(&outra, 'D');
            insere(&outra, 'G');
            l[5] = outra;
            outra = NULL;
            insere(&outra, 'G');
            insere(&outra, 'A');
            insere(&outra, 'F');
            insere(&outra, 'E');
            l[6] = outra;
            outra = NULL;

        }
    }
    else if(op == 2)
    {
        int w = 0, escolha = 0, erro1 = 0, erro2 = 0, i = 0, pos1 = 0, pos2 = 0;
        char ve, ve1, ve2;
        system("cls");
        printf("Digite quantos vértices serão necessários: ");
        scanf("%d", &tam);
        Criar(l, tam);
        while(escolha != 3)
        {
            system("cls");
            printf("1 - Adicionar vértice\n2 - Adicionar ligação\n3 - Coloração\n");
            scanf("%d", &escolha);
            if(escolha == 1)
            {
                if(i == tam)
                {
                    system("cls");
                    printf("Não é possível adicionar mais vértices!!\nVocê já adicionou os %d vértices !", tam + 1);
                    system("pause");
                }
                else
                {
                    system("cls");
                    printf("\nDigite o vértice a ser adicionado: ");
                    ve = getche();
                    insere(&outra, ve);
                    l[i] = outra;
                    outra = NULL;
                    i++;
                }
            }
            else if(escolha == 2)
            {
                system("cls");
                printf("Digite o primeiro vértice da ligação: ");
                ve1 = getche();
                for(w = 0; w <= i; w++)
                {
                    if(l[w]->label == ve1)
                    {
                        pos1 = w;
                        erro1 = 0;
                        break;
                    }
                    else
                    {
                        erro1 = 1;
                    }
                }
                printf("\nDigite o primeiro vértice da ligação: ");
                ve2 = getche();
                for(w = 0; w <= i; w++)
                {
                    if(l[w]->label == ve2)
                    {
                        pos2 = w;
                        erro2 = 0;
                        break;
                    }
                    else
                    {
                        erro2 = 1;
                    }
                }
                if(erro1 == 0 && erro2 == 0)
                {
                    outra = NULL;
                    outra = l[pos2];
                    insere(&outra, ve1);
                    l[pos2] = outra;
                    outra = NULL;
                    outra = l[pos1];
                    insere(&outra, ve2);
                    l[pos1] = outra;
                    outra = NULL;
                }

            }

        }
    }
    else
    {
        printf("Opção inválida!!\nTente novamente\n");
        system("pause");
        main();
    }
    colorir(l);
    imprimir(l);
    do
    {
        printf("\nDeseja executar novamente?(s/n)\n");
        nova = getche();
        if(nova == 'N' || nova == 'n')
        {
            return 0;
        }
        else if(nova == 's' || nova == 'S')
        {
            main();
        }

    }while(nova != 's' && nova != 'S' && nova != 'n' && nova != 'N');

    return 0;
}


struct Vertice * Criar(struct Vertice **l, int tam)
{
    int i;
    for(i=0; i<tam+2; i++)
    {
        l[i] = (struct Vertice*)malloc(sizeof(struct Vertice));
        l[i]->label = 'a';
        l[i]->prox = NULL;
        l[i]->cor = 0;
    }
    return *l;
}

struct Vertice * insere(struct Vertice **l, char num)
{
    struct Vertice *novo;
    struct Vertice *atual;
    if (*l==NULL)
    {
        novo = (struct Vertice*)malloc(sizeof (struct Vertice));
        novo->label = num;
        novo->prox = NULL;
        *l = novo;
    }
    else
    {
        atual = *l;
        while(atual->prox != NULL)
        {
            atual = atual->prox;
        }
        novo = (struct Vertice*)malloc(sizeof (struct Vertice));
        novo-> label = num;
        novo -> prox = atual->prox;
        atual-> prox = novo;

    }
    return *l;

}

int vercores(struct Vertice **l, int k, int i, int cor)
{
    struct Vertice *p;
    p = (struct Vertice*)malloc(tam * sizeof(struct Vertice));
    struct Vertice *aux;
    aux = (struct Vertice*)malloc(tam * sizeof(struct Vertice));
    int check = 1, tem = 0, w = 0;
    p = l[i]->prox;
    aux = l[k];

    p = l[i]->prox;
    aux = l[w];
    while(p != NULL)
    {
        w = 0;
        aux=l[w];
        while(aux->prox != NULL)
        {
            aux = l[w];
            if(aux->label == p->label)
            {
                if(cor == aux->cor)
                {
                    return 0;
                }
                else
                {
                    check = 1;
                    tem = 1;
                }
            }
            w++;
        }
        p = p->prox;
    }
    if(tem == 0)
    {
        return 1;
    }


    return check;

}

void colorir(struct Vertice **l)
{
    struct Vertice *p;
    struct Vertice *aux;
    int k = 0, c = 0 , corAux = 0, entrou = 0, w = 0, cor = 0, i = 0;
    p = (struct Vertice*)malloc(tam * sizeof(struct Vertice));
    aux = (struct Vertice*)malloc(tam * sizeof(struct Vertice));
    p = NULL;
    aux = NULL;

    l[0]->cor = cores[1];
    p = l[0]->prox;
    c = 2;
    while(p->prox != NULL)
    {
        p->cor = cores[c];
        p = p->prox;
    }
    //COLOCAR COR DO VERTICE EM TODOS OS LUGARES


    for(i = 1; i<tam; i++)
    {
        p = l[i];
        k = i-1;
        while(k != -1)
        {
            aux = l[k];
            do
            {
                if(aux->label == p->label)
                {
                    entrou = 0;
                    break;
                }
                else
                {
                    cor = l[k]->cor;
                    cor = vercores(l,k,i,cor);
                    entrou = 1;
                    if(cor == 1)
                    {
                        w = 1;
                        corAux = l[k]->cor;
                    }
                    else
                    {
                        entrou = 0;
                    }
                }
                aux = aux->prox;
            }
            while(aux != NULL);
            k--;
        }
        //ENTROU = 1 , NÃO TEM CONEXÃO
        if(entrou == 1 || w == 1)
        {
            p->cor = corAux;

            //SE A CORAUX for diferente das cores dos vértices ligados
        }
        else if(entrou == 0 && w == 0)
        {
            p->cor = cores[c++];
        }
        w = 0;
    }
    w = 0;
    i = 0;
    p = NULL;
    aux = NULL;
    for(i=0; i<tam; i++)
    {
        for(w=0; w<tam; w++)
        {
            for (p = l[w]; p != NULL; p = p->prox)
            {
                if(p->label == l[i]->label)
                {
                    p->cor = l[i]->cor;
                }
            }
        }
    }

}



void imprimir(struct Vertice **l)
{
    int tamimprimir = 1, j = 0, cor = 0;
    struct Vertice *p;

    p = (struct Vertice*) malloc (tamimprimir * sizeof(struct Vertice));
    for(j=0; j<tam; j++)
    {
        cor = l[j]->cor;
        MudarCor(cor);
        printf("\n%d.o vertice %c ->", j + 1, l[j]->label);

        l[j]->label = l[j]->prox->label;
        for (p = l[j]->prox; p != NULL; p = p->prox)
        {
            cor = p->cor;
            MudarCor(cor);
            printf("\t%c", p->label);
        }

    }
    printf("\n");
    system("pause");
}

void MudarCor(int cor)
{

    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, cor);
}
