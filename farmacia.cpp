# include <stdio.h>
# include <string.h>

void limpa_tela();
void menu();
void le_dados();

int main(){
    menu();
    return 0;
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
    }
}

void menu(){
    int opcao = 1;  
    printf("1 - Cadastrar\n");
    printf("2 - Consultar\n");
    printf("3 - Alterar\n");
    printf("4 - Remover\n");
    printf("5 - Exibir\n");
    printf("0 - Exit\n");

    scanf("%d", &opcao);
    while (opcao != 0){
        switch (opcao){
            case 1:
                le_dados();
                // cadastrar();
                break;
        }
        limpa_tela();
        printf("Escolha uma das opções: ");
        scanf("%d", &opcao);
    }
}

// int cadastro(char *remedio, int tipo_do_mercado, int codigo, float preco){
//     FILE *file;
//     switch (tipo_do_mercado){
//         case 1:
//             file = fopen("txt/mercado1.txt", "a");
//             if (!file){
//                 printf("Erro ao abrir arquivo.\n");
//                 return 0;
//             }
//             fprintf(file, "%d|%.2f|%s", codigo, preco, remedio);
//             break;
//         case 2:
//             file = fopen("txt/mercado2.txt", "a");
//             if (!file){
//                 printf("Erro ao abrir arquivo.\n");
//                 return 0;
//             }
//             fprintf(file, "%d|%.2f|%s", codigo, preco, remedio);
//             break;
//         case 3:
//             file = fopen("txt/mercado3.txt", "a");
//             if (!file){
//                 printf("Erro ao abrir arquivo.\n");
//                 return 0;
//             }
//             fprintf(file, "%d|%.2f|%s", codigo, preco, remedio);
//             break;
    
//         default:
//             break;
//     }
//     fclose(file);
// }

void limpa_tela(){
    clsc();
}