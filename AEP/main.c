#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

// Estrutura para armazenar os cadastros
typedef struct {
    char nome[20];
    int idade;
    float salario;
    char sexo;
} reg_cadastro;

// Variáveis globais
int i = 0;
int totalCadastros = 0; // Nova variável para contar o total de cadastros realizados
reg_cadastro log_cadastro[10];

// Funções para controle do cursor no console
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void construirTela() {
    system("cls");
    for (int i = 1; i < 90; i++) {
        gotoxy(i, 1); printf("=");
        gotoxy(i, 3); printf("=");
        gotoxy(i, 23); printf("=");
        gotoxy(i, 25); printf("=");
    }
    for (int i = 1; i < 26; i++) {
        gotoxy(1, i); printf("|");
        gotoxy(90, i); printf("|");
    }
    gotoxy(1, 1); printf("+");
    gotoxy(90, 1); printf("+");
    gotoxy(1, 3); printf("+");
    gotoxy(90, 3); printf("+");
    gotoxy(1, 23); printf("+");
    gotoxy(1, 25); printf("+");
    gotoxy(90, 23); printf("+");
    gotoxy(90, 25); printf("+");
    gotoxy(2, 24); printf("SAIDA:");
}

void posicaoConsoleSaida() {
    gotoxy(10, 24);
    printf("                                                                           ");
    gotoxy(10, 24);
}

void posicaoConsoleTitulo() {
    gotoxy(3, 2);
    printf("                                                                           ");
    gotoxy(3, 2);
}

// Função de cadastro de usuario
int cadastroCliente() {
    int continuarCadastro;
    while (1) {
        construirTela();
        posicaoConsoleTitulo();
        printf("CADASTRO DE PESSOA");

        if (i >= 10) { // Limite de cadastros atingido
            posicaoConsoleSaida();
            printf("Limite de cadastros atingido!");
            getch();
            break;
        }

        // Campos de cadastro
        gotoxy(3, 5);
        printf("Digite o nome......:");
        gotoxy(3, 7);
        printf("Digite a idade.....:");
        gotoxy(3, 9);
        printf("Digite o salario...:");
        gotoxy(3, 11);
        printf("Digite o sexo M/F..:");

        // Lendo o nome
        gotoxy(24, 5);
        fflush(stdin);
        fgets(log_cadastro[i].nome, 20, stdin);
        log_cadastro[i].nome[strcspn(log_cadastro[i].nome, "\n")] = 0;

        // Lendo a idade
        while (1) {
            gotoxy(24, 7);
            printf("                         ");
            gotoxy(24, 7);
            scanf("%d", &log_cadastro[i].idade);
            if (log_cadastro[i].idade < 18 || log_cadastro[i].idade > 65) {
                posicaoConsoleSaida();
                printf("Digite uma idade valida!");
                getch();
                posicaoConsoleSaida();
            } else {
                break;
            }
        }

        // Lendo o salario
        while (1) {
            gotoxy(24, 9);
            printf("                         ");
            gotoxy(24, 9);
            scanf("%f", &log_cadastro[i].salario);
            if (log_cadastro[i].salario < 0) {
                posicaoConsoleSaida();
                printf("Digite um salario maior que 0!");
                getch();
                posicaoConsoleSaida();
            } else {
                break;
            }
        }

        // Lendo o sexo
        while (1) {
            gotoxy(24, 11);
            printf("                         ");
            gotoxy(24, 11);
            scanf(" %c", &log_cadastro[i].sexo);
            if (log_cadastro[i].sexo == 'F' || log_cadastro[i].sexo == 'f' || log_cadastro[i].sexo == 'M' || log_cadastro[i].sexo == 'm') {
                break;
            } else {
                posicaoConsoleSaida();
                printf("Digite um sexo valido: F (feminino) ou M (masculino)");
                getch();
                posicaoConsoleSaida();
            }
        }

        i++; // Incrementa o índice de cadastro
        totalCadastros = i; // Atualiza o total de cadastros

        // Verificando se deseja cadastrar um próximo usuario
        while (1) {
            posicaoConsoleSaida();
            printf("Cadastrar novo usuario (1. Sim | 2. Nao): ");
            scanf("%d", &continuarCadastro);
            if (continuarCadastro == 1 || continuarCadastro == 2) {
                break;
            } else {
                posicaoConsoleSaida();
                printf("Digite uma opcao valida!");
                getch();
                posicaoConsoleSaida();
            }
        }
        if (continuarCadastro == 2) {
            break;
        }
    }
    return 0;
}

// Função para exibir cadastros
int exibirCadastros() {
    construirTela();
    posicaoConsoleTitulo();
    printf("EXIBICAO DE CADASTROS");

    // Cabeçalho da tabela
    gotoxy(3, 5);
    printf("%-30s%-10s%-15s%-5s", "Nome", "Idade", "Salario", "Sexo");

    // Exibindo todos os cadastros realizados
    for (int j = 0; j < totalCadastros; j++) {
        gotoxy(3, j + 7);
        printf("%-30s%-10d%-15.2f%-5c", log_cadastro[j].nome, log_cadastro[j].idade, log_cadastro[j].salario, log_cadastro[j].sexo);
    }

    posicaoConsoleSaida();
    printf("Digite qualquer tecla para voltar. ");
    getch();

    return 0;
}

// Função principal
int main() {
    int escolha;

    // Repetição que permitirá com que  entre e cadastre usuários mais de uma vez
    while (1) {
        construirTela();
        posicaoConsoleTitulo();
        printf("TELA INICIAL");

        // Exibindo opções de ações do sistema na tela principal
        gotoxy(3, 5);
        printf("1. Cadastrar um usuario");
        gotoxy(3, 7);
        printf("2. Lista de cadastros");
        gotoxy(3, 9);
        printf("3. Fechar o sistema");

        posicaoConsoleSaida();
        printf("Digite uma opcao para continuar: ");
        scanf("%d", &escolha);

        // Verificando a escolha do usuário
        switch (escolha) {
            case 1:
                cadastroCliente();
                break;
            case 2:
                exibirCadastros();
                break;
            case 3:
                return 0;
            default:
                posicaoConsoleSaida();
                printf("Digite uma opcao valida!");
                getch();
        }
    }

    return 0;
}
