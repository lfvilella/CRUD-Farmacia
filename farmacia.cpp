# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void limpa_tela();
void menu();
void le_dados();
void cadastro(int codigo, char *remedio, float preco, int quantidade, char generico, char *categoria, char *fabricante);
void exibir_dados();
void consulta_dados();

int main(){
    menu();
    return 0;
}

void menu(){
    int opcao = 1;  
    while (opcao != 0){
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
                consulta_dados();
                break;
            case 5:
                exibir_dados();
                break;
        }
    }
}

void le_dados(){
    int codigo_remedio;
    char nome_do_remedio[255];
    float preco;
    int quantidade;
    char generico; // S ou N
    char categoria[255];
    char fabricante[255];

    int quantia_produtos_cadastrado;
    printf("Quantidade a ser cadastrada: "); scanf("%d", &quantia_produtos_cadastrado);

    for (int idx = 0; idx < quantia_produtos_cadastrado; idx++){
        printf("\n*** Produto %d ***\n", idx+1);
        printf("Codigo: "); 
        scanf("%d", &codigo_remedio);

        printf("Nome do remédio: "); 
        getchar();
        fgets(nome_do_remedio, 255, stdin);

        printf("Preço: "); 
        scanf("%f", &preco);

        printf("Quantidade: "); 
        scanf("%d", &quantidade);

        printf("Genério (S/N): "); 
        getchar();
        scanf("%c", &generico);

        printf("Categoria: "); 
        getchar();
        fgets(categoria, 255, stdin);

        printf("Fabricante: "); 
        getchar();
        fgets(fabricante, 255, stdin);

        cadastro(codigo_remedio, nome_do_remedio, preco, quantidade, generico, categoria, fabricante);
    }
}

void cadastro(int codigo, char *remedio, float preco, int quantidade, char generico, char *categoria, char *fabricante){
    FILE *file = fopen("txt/data_base_pharma.txt", "a");
    if (!file){
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    // It will be saved like this: codigo|remedio|preco|quantidade|generico|categoria|fabricante
    fprintf(file, "%d\n%s%.2f\n%d\n%c\n%s%s\n", codigo, remedio, preco, quantidade, generico, categoria, fabricante);
    fclose(file);
}

void exibir_dados(){
    FILE *file = fopen("txt/data_base_pharma.txt", "r");
    if (!file){
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    char c;
    while ((c = fgetc(file)) != EOF){
        printf("%c", c);
    }

    int take_break = 0;
    printf("\nPress any key to back to menu: ");
    scanf("%d", &take_break);
}

void consulta_dados(){
    printf("Need build this functions.\n");
}

void limpa_tela(){
    system("clear");
    // Or system("CLS"); for windows
}