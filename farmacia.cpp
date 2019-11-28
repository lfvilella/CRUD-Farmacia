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
    char deletado; // deletado = '*' / nao deletado = ' '
}Farmacia;

// FUNCTIONS //
void limpa_tela();
void take_a_break();
void menu();
void le_dados();
int verifica_codigo(int code_to_search);
void cadastro(Farmacia pharma);
void exibir_dados();
void consultar();
void alterar_dados();
void remover_dados();
void sales();
void data_copy(FILE *file1, FILE *file2); // Copia o 1 para o 2
void verifica_file(FILE *file);
void backup();
void delete_all();

int main(){
    menu();
    return 0;
}

void menu(){
    int opcao = 1;
    do {
        fflush(stdin); // Limpa o buffer para evitar algum erro.
        limpa_tela();

        printf("********************\n");
        printf("* 1 - Cadastrar    *\n");
        printf("* 2 - Consultar    *\n");
        printf("* 3 - Alterar      *\n");
        printf("* 4 - Remover      *\n");
        printf("* 5 - Exibir       *\n");
        printf("* 6 - Backup       *\n");
        printf("* 7 - Deletar Tudo *\n");
        printf("* 8 - Vendas       *\n");
        printf("* 0 - Sair         *\n");
        printf("********************\n");

        printf("\nEscolha uma das opções: ");
        scanf("%d", &opcao);
        printf("\n");
        switch (opcao){
            case 1:
                le_dados();
                break;
            case 2:
                consultar();
                break;
            case 3:
                alterar_dados();
                break;
            case 4:
                remover_dados();
                break;
            case 5:
                exibir_dados();
                break;
            case 6:
                backup();
                break;
            case 7:
                backup();
                delete_all();
                break;
            case 8:
                sales();
                break;
            case 0:
                return;
                break;
        }
    }while (opcao >= 0 || opcao <= 8);
}

void le_dados(){
    Farmacia pharma;

    int quantia_produtos_cadastrado;
    printf("Quantidade a ser cadastrada: "); scanf("%d", &quantia_produtos_cadastrado);

    for (int idx = 0; idx < quantia_produtos_cadastrado; idx++){
        printf("\n*** Produto %d ***\n", idx+1);
        printf("Codigo: "); 
        scanf("%d", &pharma.codigo);
        while (verifica_codigo(pharma.codigo) == 0){
            printf("Codigo: "); 
            scanf("%d", &pharma.codigo);
        }

        printf("Nome do remédio: "); 
        fflush(stdin);
        fgets(pharma.nome, 50, stdin);

        printf("Preço: "); 
        scanf("%f", &pharma.preco);

        printf("Quantidade: "); 
        scanf("%d", &pharma.quantidade);

        printf("Genério (S/N): "); 
        fflush(stdin);
        scanf("%c", &pharma.generico);

        printf("Categoria: "); 
        fflush(stdin);
        fgets(pharma.categoria, 50, stdin);

        printf("Fabricante: "); 
        fflush(stdin);
        fgets(pharma.fabricante, 50, stdin);

        cadastro(pharma);
        printf("Codigo já existente.\n");
    }
}

int verifica_codigo(int code_to_search){
    file = fopen("txt/data_base_pharma.txt", "rb");
    verifica_file(file);

    Farmacia pharma;

    while (fread(&pharma, sizeof(Farmacia), 1, file)){
        if ((pharma.codigo == code_to_search) && (pharma.deletado != '*')){
            printf("Codigo ja existente! \n");
            take_a_break();
            return 0;
        }
    }
    fclose(file);
    return 1;
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
    file = fopen("txt/data_base_pharma.txt", "r+b");
    verifica_file(file);
    Farmacia pharma;

    printf("\n********************************\n");
    printf("** Remédios no Banco de Dados **\n");
    printf("********************************\n\n");
    while (fread(&pharma, sizeof(Farmacia), 1, file)){
        if (pharma.deletado != '*'){ // So mostra os nao deletados
            printf("Codigo: %d\n", pharma.codigo);
            printf("Nome do Remedio: %s", pharma.nome);
            printf("Preco: %.2f\n", pharma.preco);
            printf("Quantidade em Estoque: %d\n", pharma.quantidade);
            printf("Generico: %c\n", pharma.generico);
            printf("Categoria: %s", pharma.categoria);
            printf("Fabricante: %s\n", pharma.fabricante);
            // printf("Ativo: %c\n\n", pharma.deletado);
        }
    }
    printf("********************************\n");
    printf("********************************\n\n");

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
        if ((pharma.codigo == code_to_search) && (pharma.deletado != '*')){
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

void alterar_dados(){
    file = fopen("txt/data_base_pharma.txt", "r+b");  
    verifica_file(file);

    Farmacia pharma;

    int code_to_change;
    printf("Insira o código do remedio para alterar: "); scanf("%d", &code_to_change);

    bool find_out;
    while (fread(&pharma, sizeof(pharma), 1, file)){
        if (code_to_change == pharma.codigo && pharma.deletado != '*'){
            printf("Codigo: %d\n", pharma.codigo);
            printf("Produto: %s", pharma.nome);
            printf("Quantidade: %d\n", pharma.quantidade);
            printf("Valor: %.2f\n", pharma.preco);
            find_out = true;

            fseek(file, sizeof(Farmacia)*-1, SEEK_CUR);
            printf("\nDigite as novas alterações: \n");
            printf("Codigo: "); 
            scanf("%d", &pharma.codigo);

            printf("Nome do remédio: "); 
            fflush(stdin);
            fgets(pharma.nome, 50, stdin);

            printf("Preço: "); 
            scanf("%f", &pharma.preco);

            printf("Quantidade: "); 
            scanf("%d", &pharma.quantidade);

            printf("Genério (S/N): "); 
            fflush(stdin);
            scanf("%c", &pharma.generico);

            printf("Categoria: "); 
            fflush(stdin);
            fgets(pharma.categoria, 50, stdin);

            printf("Fabricante: "); 
            fflush(stdin);
            fgets(pharma.fabricante, 50, stdin);

            fwrite(&pharma, sizeof(pharma), 1, file);
            fseek(file, sizeof(pharma)* 0, SEEK_END);
            return;
        }
    }

    if (!find_out){
        printf ("\nCodigo nao cadastrado!!\n");
        take_a_break();
    }

    fclose(file);
}

void remover_dados(){
    Farmacia pharma;

    printf("\nPara auxiliar na vizualiação, vamos listar os remedios! \n");
    exibir_dados();

    file = fopen("txt/data_base_pharma.txt", "r+b");  
    verifica_file(file);

    int code_to_remove;
    printf("Insira o código do remedio a ser removido: "); scanf("%d", &code_to_remove);

    char sure;
    bool find_out;
    while (fread(&pharma, sizeof(pharma), 1, file)){
        if (code_to_remove == pharma.codigo){
            printf("*** PRODUTO ***\n");
            printf("Codigo: %d\n", pharma.codigo);
            printf("Produto: %s", pharma.nome);
            printf("Quantidade: %d\n", pharma.quantidade);
            printf("Valor: %.2f\n", pharma.preco);
            find_out = true;

            printf("Você tem certeza? (v/f): "); 
            fflush(stdin);
            scanf("%c", &sure);
            if (sure == 'v'){
                pharma.deletado = '*';
                printf("\n\nProduto excluido com Sucesso! \n\n");
                fseek(file, sizeof(Farmacia)*-1, SEEK_CUR);
                fwrite(&pharma, sizeof(pharma), 1, file);
                fseek(file, sizeof(pharma)* 0, SEEK_END);
                return;
            }
            else if (sure == 'f'){
                return;
            }
        }
    }

    if(!find_out){
        printf("\nCodigo não cadastrado.\n");
        take_a_break();
    }
    
    fclose(file);
}

void backup(){
    file = fopen("txt/data_base_pharma.txt", "rb");
    FILE *file_backup = fopen("txt/data_base_backup", "ab");
    verifica_file(file);
    verifica_file(file_backup);

    data_copy(file, file_backup);

    printf("Backup foi realizdo com sucesso!\n");
    take_a_break();

    fclose(file);
    fclose(file_backup);
}

void delete_all(){
    file = fopen("txt/data_base_pharma.txt", "rb");
    if (file){
        remove("txt/data_base_pharma.txt");
        printf("O banco de dados foi deletado com sucesso!\n");
        take_a_break();
        fclose(file);
    }
    else{
        printf("Arquivo inexistente.\n");
        take_a_break();
    }
}

void sales(){
    file = fopen("txt/data_base_pharma.txt", "r+b");  
    verifica_file(file);

    Farmacia pharma;

    int code_to_sale;
    printf("Insira o código do remedio para realizar a venda: "); scanf("%d", &code_to_sale);

    bool find_out;
    while (fread(&pharma, sizeof(pharma), 1, file)){
        if (code_to_sale == pharma.codigo && pharma.deletado != '*'){
            printf("Codigo: %d\n", pharma.codigo);
            printf("Produto: %s", pharma.nome);
            printf("Quantidade: %d\n", pharma.quantidade);
            printf("Valor: %.2f\n", pharma.preco);
            find_out = true;

            fseek(file, sizeof(Farmacia)*-1, SEEK_CUR);
            printf("Insira a quantidade à vender: : ");
            int quantidade_venda;
            scanf("%d", &quantidade_venda);
            if (pharma.quantidade > quantidade_venda){
                pharma.quantidade = (pharma.quantidade)-quantidade_venda;
            }
            else{
                printf("Estoque indisponivel!\n");
                take_a_break();
            }

            fwrite(&pharma, sizeof(pharma), 1, file);
            fseek(file, sizeof(pharma)* 0, SEEK_END);
            return;
        }
    }

    if (!find_out){
        printf ("\nCodigo nao cadastrado!!\n");
        take_a_break();
    }

    fclose(file);
}

// *************************** SUB FUCTIONS *************************** //
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
    printf("Pressione qualquer tecla para continuar: ");
    scanf("%c", &take_break);
}