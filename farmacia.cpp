# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// STRUCT //
typedef struct Pharma_Products{
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
    char generico; // S ou N
    char categoria[50];
    char fabricante[50];
}Farmacia;

// FUNCTIONS //
void limpa_tela();
void take_a_break();
void menu();
void le_dados();
void cadastro(Farmacia pharma);
void exibir_dados();
void consultar();

int main(){
    menu();
    return 0;
}

void menu(){
    int opcao = 1;
    do {
        limpa_tela();

        printf("1 - Cadastrar\n");
        printf("2 - Consultar\n");
        printf("3 - Alterar\n");
        printf("4 - Remover\n");
        printf("5 - Exibir\n");
        printf("0 - Exit\n");

        printf("Escolha uma das opções: ");
        scanf("%d", &opcao);
        switch (opcao){
            case 1:
                le_dados();
                break;
            case 2:
                consultar();
                break;
            case 5:
                exibir_dados();
                break;
            case 0:
                return;
                break;
        }
    }while (opcao >= 0 || opcao <= 5);
}

void le_dados(){
    Farmacia pharma;

    int quantia_produtos_cadastrado;
    printf("Quantidade a ser cadastrada: "); scanf("%d", &quantia_produtos_cadastrado);

    for (int idx = 0; idx < quantia_produtos_cadastrado; idx++){
        printf("\n*** Produto %d ***\n", idx+1);
        printf("Codigo: "); 
        scanf("%d", &pharma.codigo);

        printf("Nome do remédio: "); 
        getchar();
        fgets(pharma.nome, 50, stdin);

        printf("Preço: "); 
        scanf("%f", &pharma.preco);

        printf("Quantidade: "); 
        scanf("%d", &pharma.quantidade);

        printf("Genério (S/N): "); 
        getchar();
        scanf("%c", &pharma.generico);

        printf("Categoria: "); 
        getchar();
        fgets(pharma.categoria, 50, stdin);

        printf("Fabricante: "); 
        getchar();
        fgets(pharma.fabricante, 50, stdin);

        cadastro(pharma);
    }
}

void cadastro(Farmacia pharma){
    FILE *file = fopen("txt/data_base_pharma.txt", "a");
    if (!file){
        printf("Erro ao abrir arquivo.\n");
        take_a_break();
        return;
    }
    int resultado;
    resultado = fwrite(&pharma, sizeof(Farmacia), 1, file);
    if (resultado){
        printf("Item cadastrado com sucesso!.\n");
        take_a_break();
    }
    else{
        printf("Item não cadastrado, infelizmente.\n");
        take_a_break();
    }
    fclose(file);
}

void exibir_dados(){
    FILE *file = fopen("txt/data_base_pharma.txt", "r");
    if (!file){
        printf("Erro ao abrir arquivo.\n");
        take_a_break();
        return;
    }
    Farmacia pharma;

    printf("\n*** Remédios no DataBase ***\n");
    while (fread(&pharma, sizeof(Farmacia), 1, file)){
        printf("Codigo: %d\n", pharma.codigo);
        printf("Nome do Remedio: %s", pharma.nome);
        printf("Preco: %.2f\n", pharma.preco);
        printf("Quantidade em Estoque: %d\n", pharma.quantidade);
        printf("Generico: %c\n", pharma.generico);
        printf("Categoria: %s", pharma.categoria);
        printf("Fabricante: %s\n", pharma.fabricante);
    }

    take_a_break();
    fclose(file);
}

void consultar(int codigo){

}

void limpa_tela(){
    system("clear");
    // Or system("CLS"); for windows
}

void take_a_break(){
    getchar();
    char take_break;
    printf("Type any key to continue: ");
    scanf("%c", &take_break);
}