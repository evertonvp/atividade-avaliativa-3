#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Produto
{
    int quantidade;
    int id;
    char nome[50];
    int valor;
    struct Produto *procx;
} Produto;

Produto *criarNovoProduto()
{
    Produto *novoProduto = (Produto *)malloc(sizeof(Produto));
    if (novoProduto == NULL)
    {
        printf("Erro de memoria");
        exit(EXIT_FAILURE);
    }
    novoProduto->procx = NULL;
    return novoProduto;
}

Produto *listavazia()
{
    return NULL;
}


Produto *cadastrar(Produto *lista1)
{
    srand(time(NULL));
    Produto *novoProduto = criarNovoProduto();
    novoProduto->id = rand() % 200;
    printf("Digite o nome do produto: ");
    fflush(stdin);
    fgets(novoProduto->nome, sizeof(novoProduto->nome), stdin);
    printf("Digite a quantidade: ");
    scanf("%d", &novoProduto->quantidade);
    printf("Digite o valor:");
    scanf("%d", &novoProduto->valor);

    if (lista1 == NULL)
    {
        return novoProduto;
    }
    else
    {
        Produto *atual = lista1;
        while (atual->procx != NULL)
        {
            atual = atual->procx;
        }
        atual->procx = novoProduto;
        return lista1;
    }
}

void mostrarlista1(Produto *lista1)
{
    Produto *atual = lista1;
    if (lista1 == NULL)
    {
        printf("\nlista1 nula\n");
        return;
    }
    else
    {
        while (atual != NULL)
        {
            printf("\nNome: %s", atual->nome);
            printf("quantidade: %d", atual->quantidade);
            printf("\nID: %d", atual->id);
            printf("\nValor do produto: %d", atual->valor);
            printf("\n");
            atual = atual->procx;
        }
    }
}

Produto *buscarProduto(Produto *lista1, int buscaID)
{
    Produto *atual = lista1;
    while (atual != NULL)
    {
        if (atual->id == buscaID)
        {
            printf("\nNome: %s", atual->nome);
            printf("quantidade: %d", atual->quantidade);
            printf("\nID: %d", atual->id);
            return atual;
        }
        atual = atual->procx;
    }
    printf("Produto nao encontrado: ");
    return NULL;
}

void alterar(Produto *Produto)
{
    printf("Digite um novo nome");
    fflush(stdin);
    fgets(Produto->nome, sizeof(Produto->nome), stdin);
    fflush(stdin);
    printf("Digite uma nova quantidade por favor");
    fflush(stdin);
    scanf("%d", &Produto->quantidade);
}

Produto *excluir(Produto *lista1, int buscaID)
{
    Produto *atual = lista1;
    Produto *precedente = NULL;

    while (atual != NULL && atual->id != buscaID)
    {
        precedente = atual;
        atual = atual->procx;
    }

    if (atual != NULL)
    {
        if (precedente != NULL)
        {
            precedente->procx = atual->procx;
        }
        else
        {
            lista1 = atual->procx;
        }
        free(atual);
        printf("Removido com sucesso");
    }
    else
    {
        printf("Produto nao encontrado");
    }
    return lista1;
}

void liberarlista1(Produto *lista1)
{
    Produto *atual = lista1;
    Produto *procx;
    while (atual != NULL)
    {
        procx = atual->procx;
        free(atual);
        atual = procx;
    }
}

int main()
{
    int opcao;
    int buscaID;
    Produto *encontrado;
    Produto *lista1 = listavazia();

    do
    {
        printf("\nDigite 1 para cadastrar");
        printf("\nDigite 2 para buscar");
        printf("\nDigite 3 para mostrar");
        printf("\nDigite 4 para alterar");
        printf("\nDigite 5 para excluir");
        printf("\nDigite 0 para sair");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            lista1 = cadastrar(lista1);
            break;

        case 2:
            printf("Digite o id para busca");
            scanf("%d", &buscaID);
            encontrado = buscarProduto(lista1, buscaID);
            break;
        case 3:
            mostrarlista1(lista1);
            break;
        case 4:
            printf("\nDigite o id para alteracao");
            scanf("%d", &buscaID);
            encontrado = buscarProduto(lista1, buscaID);
            if (encontrado != NULL)
            {
                alterar(encontrado);
            }
            break;
        case 5:
            printf("\nDigite o id para exclusao");
            scanf("%d", &buscaID);
            lista1 = excluir(lista1, buscaID);
            break;
        }
    } while (opcao != 0);

    liberarlista1(lista1);

    return 0;
}