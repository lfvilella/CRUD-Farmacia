# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// Variavel global
FILE *file;

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
void remover_dados();
void data_copy(FILE *file1, FILE *file2); // Copia o 1 para o 2
void verifica_file(FILE *file);

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
        printf("6 - Backup\n");
        printf("7 - Delete All\n");
        printf("0 - Exit\n");

        printf("Escolha uma das opções: ");
        scanf("%d", &opcao);
        printf("\n");
        switch (opcao){
            case 1:
                le_dados();
                break;
            case 2:
                consultar();
                break;
            case 4:
                remover_dados();
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
    file = fopen("txt/data_base_pharma.txt", "a");
    verifica_file(file);

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
    file = fopen("txt/data_base_pharma.txt", "r");
    verifica_file(file);
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

void consultar(){
    int code_to_search;
    printf("Insira o codigo para busca: "); scanf("%d", &code_to_search);

    file = fopen("txt/data_base_pharma.txt", "rb");
    verifica_file(file);

    Farmacia pharma;

    bool find_out;
    while (fread(&pharma, sizeof(Farmacia), 1, file)){
        if (pharma.codigo == code_to_search){
            printf("Codigo: %d\n", pharma.codigo);
            printf("Nome do Remedio: %s", pharma.nome);
            printf("Preco: %.2f\n", pharma.preco);
            printf("Quantidade em Estoque: %d\n", pharma.quantidade);
            printf("Generico: %c\n", pharma.generico);
            printf("Categoria: %s", pharma.categoria);
            printf("Fabricante: %s\n", pharma.fabricante);
            
            find_out = true;
            break;
        }
    }
    if (!find_out){
        printf("Codigo não encontrado ! \n\n");
    }

    take_a_break();
    fclose(file);
}

void remover_dados(){
    printf("\nPara auxiliar na vizualiação, vamos listar os remedios! \n");
    exibir_dados();

    int code_to_remove;
    printf("Insira o código do remedio a ser removido: "); scanf("%d", &code_to_remove);

    file = fopen("txt/data_base_pharma.txt", "rb");
    FILE *file_aux = fopen("txt/data_base_pharma_aux.txt", "wb");
    
    verifica_file(file);
    verifica_file(file_aux);

    Farmacia pharma;

    char c;
    // Não posso jogar no data_copy() por causa do if
    while((c = getc(file)) != EOF){
        if (pharma.codigo == code_to_remove){
            printf("Removendo...");
        }
        else{
            fprintf(file_aux, "%c", c);
        }
    }
    fclose(file);
    fclose(file_aux);
    // ------------- //

    // VOLTANDO DADOS PARA O ARQUIVO PRINCIPAL:
    file = fopen("txt/data_base_pharma.txt", "wb");
    file_aux = fopen("txt/data_base_pharma_aux.txt", "rb");
    verifica_file(file);
    verifica_file(file_aux);

    data_copy(file_aux, file);

    take_a_break();

    fclose(file);
    fclose(file_aux);
}

void data_copy(FILE *file1, FILE *file2){
    char c;

    while((c = getc(file1)) != EOF){
        fprintf(file2, "%c", c);
    }
}

void verifica_file(FILE *file){
    if (!file){
        printf("Erro ao abrir arquivo.\n");
        take_a_break();
        return;
    }
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