//
//  main.c
//  grafo_02
//
//  Created by Paulo Henrique on 03/09/16.
//  Copyright ¬© 2016 Paulo Henrique. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define inf 999999999

//Estrutura das Arestas;
struct no{
    int rotulo;
    int peso;
    int destino;
    struct no* prox;
};

//Estrutura dos Vertices;
struct vertice{
    int num;
    int estimativa;
    int aberto;
    
    struct no *prox_aresta;
    struct vertice *prox_vertice;
};

struct vertice *inserir_vertice(struct vertice *grafo,int num){
    struct vertice *v1;
    struct vertice *aux;
    struct vertice *procura;
    //Se o Grafo for Nulo, aloca um vertice
    if(grafo == NULL){
        v1 = (struct vertice*)malloc(sizeof(struct vertice));
        if(v1 == NULL)
            return grafo;
        v1->num = num;
        v1->prox_vertice = NULL;
        v1->prox_aresta = NULL;
        v1->estimativa = inf;
        v1->aberto = 0;
        grafo = v1;
    }else{
        //Se o Vertice já existir, não deixa adicionar outro vertice;
        for(procura = grafo; procura != NULL; procura = procura->prox_vertice){
            if(num == (procura)->num){
                printf("Vertice existente! Por favor insira outro\n");
                return grafo;
            }
        }
        //Se o Grafo não tiver vazio, e o vertice não existir no Grafo, aloca o vertice na ordem crescente;
        if(num < (grafo)->num){
            aux = (struct vertice*)malloc(sizeof(struct vertice));
            if(aux == NULL)
                return grafo;
            
            aux->num = num;
            aux->prox_vertice = grafo;
            v1->estimativa = inf;
            v1->aberto = 0;
            aux->prox_aresta = NULL;
            grafo = aux;
            return grafo;
        }
        
        if(num > (grafo)->num){
            aux = grafo;
            v1 = (struct vertice*)malloc(sizeof(struct vertice));
            if(v1 == NULL)
                return grafo;
            v1->num = num;
            v1->estimativa = inf;
            v1->aberto = 0;
            v1->prox_aresta = NULL;
            
            while(aux->prox_vertice != NULL && num > aux->prox_vertice->num){
                aux = aux->prox_vertice;
            }
            v1->prox_vertice = aux->prox_vertice;
            aux->prox_vertice = v1;
        }
    }
    return grafo;
}

struct vertice *buscar_vertice(struct vertice *grafo, int origem){
    struct vertice *busca = grafo;
    //Busca um vertice no grafo, se o grafo for nulo, diz q o Grafo ta vazio;
    if(grafo == NULL){
        printf("Lista vazia!\n");
        return grafo;
    }
    //Se o numero desejado for o primeiro, retorna o proprio grafo;
    if(grafo->num == origem){
        return grafo;
    }
    //Se não for o primeiro, vai de vertice em vertice na procura dele;
    while(busca->prox_vertice != NULL){
        if(busca->prox_vertice->num == origem){
            return busca->prox_vertice;
        }
        busca = busca->prox_vertice;
    }
    return NULL;
}


struct vertice *inserir_aresta(struct vertice *grafo, int origem, int destino, int valor_aresta, int peso){
    struct no *a1;
    struct no *a2;
    struct vertice *procurar_origem;
    struct vertice *procurar_destino;
    struct vertice *aux_procurar;
    aux_procurar = grafo;
    
    //Usa a função buscar_vertice pra saber se o vertice exite na origem e no destino que deseja inserir o vertice;
    
    procurar_origem = buscar_vertice(grafo, origem);
    if(procurar_origem == NULL){
        printf("Vertice de Origem inxistente!\n");
    }
    else{
        procurar_destino = buscar_vertice(grafo, destino);
        
        if(procurar_destino == NULL){
            printf("Vertice de Destino inxistente!\n");
        }else{
            if(procurar_origem->prox_aresta == NULL || procurar_origem->prox_aresta->destino > procurar_destino->num){
                
                //Se o vertice não tiver arestas, insere Aresta aqui, como a primeira aresta;
                
                a1 = (struct no*)malloc(sizeof(struct no));
                if(a1 == NULL)
                    return grafo;
                
                a1->rotulo = valor_aresta;
                a1->peso = peso;
                a1->destino = procurar_destino->num;
                a1->prox = procurar_origem->prox_aresta;
                procurar_origem->prox_aresta = a1;
            }else{
                //Se já existir uma aresta, a proxima será alocada na ordem Crescente;
                a1 = (struct no*)malloc(sizeof(struct no));
                if(a1 == NULL)
                    return grafo;
                
                a1->rotulo = valor_aresta;
                a1->peso = peso;
                a1->destino = procurar_destino->num;
                
                a2 = procurar_origem->prox_aresta;
                while(a2->prox != NULL && a2->prox->destino < procurar_destino->num)
                    a2 = a2->prox;
                
                a1->prox = a2->prox;
                a2->prox = a1;
            }
            
        }
    }
    
    return grafo;
}

struct vertice *remover_aresta(struct vertice *grafo, int num){
    struct vertice *i;
    struct no *v1_before,*v2_next,*aux;
    
    if(grafo == NULL)
        return grafo;
    //Aqui, faz a procura das Arestas com Rótulo que o usuário solicitou, o For vai de vertice em Vertice;
    for(i = grafo; i != NULL ; i = i->prox_vertice){
        //Se esse i->prox_aresta for Nulo, significa que não existe arestas no Vertice;
        if(i->prox_aresta != NULL) {
            v1_before = i->prox_aresta;
            //Enquanto o vertice não for nulo, procura o rotulo;
            while(v1_before != NULL){
                //Se o rotulo for o primeiro que se deseja apagar, exclui a Aresta em questão;
                if(v1_before->rotulo == num) {
                    printf("As arestas com Rotulo %d foram removidas do Vertice %d\n",v1_before->rotulo,i->num);
                    i->prox_aresta = i->prox_aresta->prox;
                    free(v1_before);
                    v1_before = i->prox_aresta;
                } else
                    break;
            }
            //Faz uma procura nas demais arestas;
            if(i->prox_aresta != NULL)
                for(v1_before = i->prox_aresta, v2_next = i->prox_aresta->prox; v2_next != NULL;){
                    if(v2_next->rotulo == num){
                        printf("As arestas com Rotulo %d foram removidas do Vertice %d\n",v2_next->rotulo,i->num);
                        v1_before->prox = v2_next->prox;
                        aux = v2_next;
                        v2_next = v2_next->prox;
                        free(aux);
                    }else
                        v2_next = v2_next->prox;
                }// Fecha o for de dentro;
        }// Fecha IF;
    }// Fecha outro for;
    return grafo;
}

struct vertice *remover_vertice(struct vertice *grafo, int num){
    struct vertice *before = NULL;
    struct vertice *next;
    struct vertice *v1,*i,*achei;
    //struct no *j;
    struct no *v1_before,*v2_next,*aux;
    
    if(grafo == NULL)
        return grafo;
    v1 = grafo;
    
    achei = buscar_vertice(grafo, num);
    
    if(achei == NULL){
        printf("Vertice nao existe\n");
        return 0;
    }
    
    //Aqui, remove primeiro as Arestas com Ligações para os Vertices;
    
    for(i = grafo; i != NULL ; i = i->prox_vertice){
        if(i->prox_aresta != NULL) {
            v1_before = i->prox_aresta;
            while(v1_before != NULL){
                if(v1_before->destino == num) {
                    printf("As arestas com Rotulo %d foram removidas do Vertice %d\n",v1_before->rotulo,i->num);
                    i->prox_aresta = i->prox_aresta->prox;
                    free(v1_before);
                    v1_before = i->prox_aresta;
                } else
                    break;
            }
            if(i->prox_aresta != NULL)
                for(v1_before = i->prox_aresta, v2_next = i->prox_aresta->prox; v2_next != NULL;){
                    if(v2_next->destino == num){
                        printf("As arestas com Rotulo %d foram removidas do Vertice %d\n",v2_next->rotulo,i->num);
                        v1_before->prox = v2_next->prox;
                        aux = v2_next;
                        v2_next = v2_next->prox;
                        free(aux);
                    } else
                        v2_next = v2_next->prox;
                }// Fecha o for de dentro;
        }// Fecha IF;
    }// Fecha outro for;
    
    //Depois de Remover as Arestas, remove o Vertice;
    next = grafo->prox_vertice;
    before = grafo;
    
    if(grafo->num == num){
        printf("O numero %d foi removido com sucesso\n",grafo->num);
        grafo = next;
        free(before);
        return grafo;
    }
    
    while(next != NULL && next->num != num){
        before = next;
        next = next->prox_vertice;
    }
    
    if (next == NULL){
        printf("\nNumero n√£o encontrado!\n");
        return grafo;
    }
    
    before->prox_vertice = next->prox_vertice;
    free(next);
    printf("\nO numero %d foi removido com sucesso\n",num);
    return grafo;
}

void imprimir(struct vertice *grafo){
    struct vertice *i;
    struct no *j;
    //Se o Grafo for nulo
    if(grafo == NULL) {
        printf("GRAFO VAZIO\n");
        return;
    }
    //Dois for, um pra varrer os vertices e um pras Arestas;
    printf("Vertices:");
    for(i = grafo; i != NULL ; i = i->prox_vertice){
        printf("\n%d->", i->num);
        for(j = i->prox_aresta; j != NULL; j = j->prox){
            printf("%d{r:%d|p:%d}->",j->destino,j->rotulo,j->peso);
        }
    }
    printf("\n");
}

void imprimir_busca(struct vertice *grafo, int num){
    struct vertice *i;
    struct no *j;
    int cont = 0;
    
    if(grafo == NULL) {
        printf("GRAFO VAZIO\n");
        return;
    }
    //Dois for, um pra varrer os vertices e um pras Arestas. Mas só imprime o número buscado;
    printf("Vertice Buscado:\n");
    for(i = grafo; i != NULL ; i = i->prox_vertice){
        if(num == i->num){
            printf("%d->", i->num);
            cont++;
            for(j = i->prox_aresta; j != NULL; j = j->prox){
                printf("%d{r:%d|p:%d}->",j->destino,j->rotulo,j->peso);
            }
            printf("\n");
        }
        
    }
    if(cont == 0)
        printf("Vertice Inexistente!\n");
}

void imprimir_adjacentes(struct vertice *grafo, int num){
    struct vertice *i;
    struct no *j;
    int cont = 0;
    
    if(grafo == NULL) {
        printf("GRAFO VAZIO\n");
        return;
    }
    //Varre o grafo e conta qual o grau de Adjacentes do Vertice. Imprime no final o contador;
    for(i = grafo; i != NULL ; i = i->prox_vertice){
        for(j = i->prox_aresta; j != NULL; j = j->prox){
            if(j->destino == num){
                cont++;
            }
        }
    }
    
    if(cont == 0)
        printf("Vertice Nao possui Incidentes!\n");
    if(cont>0)
        printf("Vertice [%d] - Grau de Incidencia [%d]\n",num,cont);
}

int verificar(struct vertice *grafo, int destino, int origem){
    struct vertice *achei_destino;
    struct vertice *achei_origem;
    struct vertice *i;
    struct no *j;
    
    //Verifica se os Vertices existem;
    achei_destino = buscar_vertice(grafo, destino);
    achei_origem = buscar_vertice(grafo, origem);
    
    //Faz o retorno se não existirem;
    if(achei_origem == NULL){
        printf("Vertice de Origem nao Existe!\n");
        return 0;
    }
    
    if(achei_destino == NULL){
        printf("Vertice de Destino nao Existe!\n");
        return 0;
    }
    //Varre o Grafo na procura da incidencia de Vertice pra Outro;
    for(i = grafo; i != NULL ; i = i->prox_vertice){
        //Compara o numero do usuário com o Vertice Atual;
        if(i->num == achei_origem->num){
            for(j = i->prox_aresta; j != NULL; j = j->prox){
                //Compara o numero do usuário com destino da Aresta Atual;
                if(j->destino == achei_destino->num){
                    printf("Vertices Adjacentes!\nEsta(s) Aresta que Ligam eles:\n");
                    printf("%d{r:%d|p:%d}\n",j->destino,j->rotulo,j->peso);
                    
                }
            }
        }
    }
   	printf("\n");
    
    return 14;
}

struct ordenador{
    int peso;
    int origem;
    int destino;
};

int gerar_minima(struct vertice *grafo, int orig, int nv_vertice, int nv_arestas){
    
    int l=0,p, na = nv_arestas;
    struct vertice *i;
    struct no *j;
    struct ordenador *pp[na], *aux;
    struct ordenador *v1[na];
    
    i = grafo;
    for(l=0;l<na;l++){
        pp[l] = (struct ordenador*)malloc(sizeof(struct ordenador));
        v1[l] = (struct ordenador*)malloc(sizeof(struct ordenador));
    }
    //Preenche uma estrutura com os valores de todos os Vertices/Arestas;
    l=0;
    for(i = grafo; i != NULL ; i = i->prox_vertice){
        for(j = i->prox_aresta; j != NULL; j = j->prox,l++){
            
            pp[l]->peso = j->peso;
            pp[l]->destino = j->destino;
            pp[l]->origem = i->num;
            
        }
    }
    //Ordena de acordo com o menor peso;
    for(l=na-1; l>=1; l--){
        for(p=0 ; p<l ; p++){
            if(pp[p]->peso > pp[p+1]->peso){
                aux = pp[p];
                pp[p] = pp[p+1];
                pp[p+1]= aux;
            }
            
        }
    }
    //Imprime a Ordenação;
    for(l=0; l<na; l++){
        printf("Peso->%d Origem->%d Destino->%d\n", pp[l]->peso,pp[l]->origem,pp[l]->destino);
    }
    return 14;
    
}


int gerar_maxima(struct vertice *grafo, int orig, int nv_vertice, int nv_arestas){
    
    int l=0,p, na = nv_arestas;
    struct vertice *i;
    struct no *j;
    struct ordenador *pp[na], *aux;
    struct ordenador *v1[na];
    
    i = grafo;
    for(l=0;l<na;l++){
        pp[l] = (struct ordenador*)malloc(sizeof(struct ordenador));
        v1[l] = (struct ordenador*)malloc(sizeof(struct ordenador));
    }
    //Preenche uma estrutura com os valores de todos os Vertices/Arestas;
    l=0;
    for(i = grafo; i != NULL ; i = i->prox_vertice){
        for(j = i->prox_aresta; j != NULL; j = j->prox,l++){
            
            pp[l]->peso = j->peso;
            pp[l]->destino = j->destino;
            pp[l]->origem = i->num;
            
        }
    }
    //Ordena de acordo com o maior peso;
    for(l=na-1; l>=1; l--){
        for(p=0 ; p<l ; p++){
            if(pp[p]->peso < pp[p+1]->peso){
                aux = pp[p];
                pp[p] = pp[p+1];
                pp[p+1]= aux;
            }
            
        }
    }
    //Imprime a Ordenação;
    for(l=0; l<na; l++){
        printf("Peso->%d Origem->%d Destino->%d\n", pp[l]->peso,pp[l]->origem,pp[l]->destino);
    }
    return 14;
    
}

struct bolsa{
    int peso;
    int num_atual;
};


int caminho_minimo(struct vertice *grafo, int comecar, int tam){
    struct vertice *i,*i_aux,*inicio,*caminho;
    struct no *j;
    struct bolsa *bolsa_02;
    
    int x=0;
    
    caminho = (struct vertice*)malloc(sizeof(struct vertice));
    bolsa_02 = (struct bolsa*)malloc(sizeof(struct bolsa));
    
    inicio = buscar_vertice(grafo, comecar);
    
    if(inicio == NULL){
        printf("Numero inexistente\n");
        return 0;
    }
    
    caminho = grafo;
    
    bolsa_02->num_atual = 1;
    bolsa_02->peso = 0;
    
    while(x<tam){
        for(i = caminho; i != NULL ; i = i->prox_vertice){
            if(i->estimativa == inf){
                i->estimativa = 0;
            }
            else if(i->estimativa > bolsa_02->peso ){
                i->estimativa = i->estimativa + bolsa_02->peso;
            }
            
            for(j = i->prox_aresta; j != NULL; j = j->prox){
                for(i_aux = grafo; i_aux != NULL; i_aux = i_aux->prox_vertice){
                    if(j->destino == i_aux->num){
                        if(i_aux->estimativa > j->peso + i->estimativa){
                            i_aux->estimativa = j->peso + i->estimativa;
                        }
                        if(bolsa_02->peso > j->peso){
                            bolsa_02->peso = j->peso;
                            bolsa_02->num_atual = j->destino;
                        }
                        
                    }
                }
                
            }
            
            i->aberto = 1;
        }
        x++;
    }
    
    // Imprimir ordenação;
    printf("Vertices:");
    for(i = grafo; i != NULL ; i = i->prox_vertice){
        printf("\n%d | e:[%d] a/f:[%d]->", i->num,i->estimativa,i->aberto);
        for(j = i->prox_aresta; j != NULL; j = j->prox){
            printf("%d{r:%d|p:%d}->",j->destino,j->rotulo,j->peso);
        }
    }
    
    printf("\n");
    
    return 14;
}

int main(){
    
    setlocale(LC_ALL,"Portuguese");
    
    int x,cont_aresta = 0,cont_vertice = 0, num = 0,origem,destino,peso,rotulo,comecar;
    struct vertice *grafo;
    grafo = NULL;
    
    do{
        printf("Digite:\n1 - Inserir Vertice\n2 - Inserir Aresta\n3 - Remover Vertice\n4 - Remover Aresta\n5 - Buscar Vertice\n6 - Buscar Grau Incidencia do Vertice\n7 - Buscar incidencia de Dois Vertices\n8 - Gerar Arvore Geradora Minima\n9 - Gerar Arvore Geradora Maxima\n10 - Gerar Caminho Minimo\n11 - Utilizar Grafo Pre-Pronto\n0 - Sair\n");
        scanf("%d",&x);
        
        switch(x){
            case 1:{
                printf("Digite o Vertice\n");
                scanf("%d",&num);
                grafo = inserir_vertice(grafo,num);
                cont_vertice++;
                
                imprimir(grafo);
                break;
            }
            case 2:{
                printf("Em qual Vertice deseja inserir?\n");
                scanf("%d",&origem);
                printf("Para qual vertice deseja ligar?\n");
                scanf("%d",&destino);
                printf("Qual o valor da aresta?\n");
                scanf("%d",&rotulo);
                printf("Qual o Peso?\n");
                scanf("%d",&peso);
                grafo = inserir_aresta(grafo, origem, destino, rotulo,peso);
                
                if(origem != destino){
                    grafo = inserir_aresta(grafo, destino, origem, rotulo,peso);
                    cont_aresta++;
                }
                
                cont_aresta++;
                
                imprimir(grafo);
                
                break;
            }
            case 3:{
                printf("Qual Vertice deseja remover?\n");
                scanf("%d",&num);
                grafo = remover_vertice(grafo,num);
                imprimir(grafo);
                break;
            }
            case 4:{
                printf("Qual o rotulo da Aresta deseja remover?\n");
                scanf("%d",&num);
                grafo = remover_aresta(grafo,num);
                imprimir(grafo);
                break;
            }
            case 5:{
                printf("Qual vertice deseja Buscar?\n");
                scanf("%d",&num);
                imprimir_busca(grafo,num);
                break;
            }
            case 6:{
                printf("Qual vertice deseja saber a Incidencia?\n");
                scanf("%d",&num);
                imprimir_adjacentes(grafo,num);
                break;
            }
            case 7:{
                printf("Qual o Primeiro Vertice?\n");
                scanf("%d",&origem);
                printf("Qual o Segundo Vertice?\n");
                scanf("%d",&destino);
                verificar(grafo,destino,origem);
                break;
            }
            case 8:{
                gerar_minima(grafo,num,cont_vertice,cont_aresta);
                break;
            }
            case 9:{
                gerar_maxima(grafo,num,cont_vertice,cont_aresta);
                break;
            }
            case 10:{
                if(grafo == NULL){
                    printf("Grafo Vazio\n");
                    return 14;
                }
                comecar = grafo->num;
                caminho_minimo(grafo,comecar,cont_vertice);
                break;
            }case 11:{
                int opcao;
                printf("Digite:\nGrafo 01 - 5 Vertices\nGrafo 02 - 7 Vertices\n");
                scanf("%d",&opcao);
                if(opcao == 1){
                    grafo = inserir_vertice(grafo, 0);
                    grafo = inserir_vertice(grafo, 1);
                    grafo = inserir_vertice(grafo, 2);
                    grafo = inserir_vertice(grafo, 3);
                    grafo = inserir_vertice(grafo, 4);
                    cont_vertice = 5;
                    
                    grafo = inserir_aresta(grafo, 0, 1, 0,2);
                    grafo = inserir_aresta(grafo, 1, 0, 0,2);
                    
                    grafo = inserir_aresta(grafo, 0, 2, 0,6);
                    grafo = inserir_aresta(grafo, 2, 0, 0,6);
                    
                    grafo = inserir_aresta(grafo, 0, 3, 0,7);
                    grafo = inserir_aresta(grafo, 3, 0, 0,7);
                    
                    grafo = inserir_aresta(grafo, 1, 3, 1,3);
                    grafo = inserir_aresta(grafo, 3, 1, 1,3);
                    
                    grafo = inserir_aresta(grafo, 1, 4, 1,6);
                    grafo = inserir_aresta(grafo, 4, 1, 1,6);
                    
                    grafo = inserir_aresta(grafo, 2, 4, 2,1);
                    grafo = inserir_aresta(grafo, 4, 2, 2,1);
                    
                    grafo = inserir_aresta(grafo, 3, 4, 3,7);
                    grafo = inserir_aresta(grafo, 4, 3, 3,7);
                    cont_aresta = 14;
                    comecar = 0;
                    imprimir(grafo);
                    
                }
                if(opcao == 2){
                    grafo = inserir_vertice(grafo, 1);
                    grafo = inserir_vertice(grafo, 2);
                    grafo = inserir_vertice(grafo, 3);
                    grafo = inserir_vertice(grafo, 4);
                    grafo = inserir_vertice(grafo, 5);
                    grafo = inserir_vertice(grafo, 6);
                    cont_vertice = 6;
                    
                    // A - B
                    grafo = inserir_aresta(grafo, 1, 2, 1,4);
                    grafo = inserir_aresta(grafo, 2, 1, 1,4);
                    
                    // A - C;
                    grafo = inserir_aresta(grafo, 1, 3, 1,2);
                    grafo = inserir_aresta(grafo, 3, 1, 1,2);
                    
                    // B - C;
                    grafo = inserir_aresta(grafo, 2, 3, 2,1);
                    grafo = inserir_aresta(grafo, 3, 2, 2,1);
                    
                    // B - D;
                    grafo = inserir_aresta(grafo, 2, 4, 2,5);
                    grafo = inserir_aresta(grafo, 4, 2, 2,5);
                    
                    // C - D;
                    grafo = inserir_aresta(grafo, 3, 4, 3,8);
                    grafo = inserir_aresta(grafo, 4, 3, 3,8);
                    
                    
                    // C - E;
                    grafo = inserir_aresta(grafo, 3, 5, 3,10);
                    grafo = inserir_aresta(grafo, 5, 3, 3,10);
                    
                    // D - E;
                    grafo = inserir_aresta(grafo, 4, 5, 4,2);
                    grafo = inserir_aresta(grafo, 5, 4, 4,2);
                    
                    // D - F;
                    grafo = inserir_aresta(grafo, 4, 6, 4,6);
                    grafo = inserir_aresta(grafo, 6, 4, 4,6);
                    
                    // E - F;
                    grafo = inserir_aresta(grafo, 5, 6, 5,2);
                    grafo = inserir_aresta(grafo, 6, 5, 5,2);
                    
                    cont_aresta = 18;
                    comecar = 1;
                    imprimir(grafo);
                    
                }
                if(opcao > 2 || opcao < 0){
                    printf("Opcao Invalida\n");
                    break;
                }
                
                break;
            }
            case 0:{
                printf("Obrigado!\n");
                return 0;
                break;
            }
                
        }
    }while(x>0);
}

