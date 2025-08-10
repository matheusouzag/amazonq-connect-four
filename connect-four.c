#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINHAS 6
#define COLUNAS 7

char tabuleiro[LINHAS][COLUNAS];
char jogador1[50], jogador2[50];

void inicializarTabuleiro() {
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

void mostrarTabuleiro() {
    system("cls");
    printf("\n=== LIGUE 4 ===\n\n");
    
    for(int i = 0; i < LINHAS; i++) {
        printf("|");
        for(int j = 0; j < COLUNAS; j++) {
            printf(" %c |", tabuleiro[i][j]);
        }
        printf("\n");
        for(int j = 0; j < COLUNAS; j++) {
            printf("----");
        }
        printf("-\n");
    }
    
    printf(" ");
    for(int j = 1; j <= COLUNAS; j++) {
        printf(" %d  ", j);
    }
    printf("\n\n");
}

int adicionarPeca(int coluna, char simbolo) {
    coluna--;
    if(coluna < 0 || coluna >= COLUNAS) return 0;
    
    for(int i = LINHAS-1; i >= 0; i--) {
        if(tabuleiro[i][coluna] == ' ') {
            tabuleiro[i][coluna] = simbolo;
            return 1;
        }
    }
    return 0;
}

int verificarVitoria(char simbolo) {
    // Horizontal
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS-3; j++) {
            if(tabuleiro[i][j] == simbolo && tabuleiro[i][j+1] == simbolo && 
               tabuleiro[i][j+2] == simbolo && tabuleiro[i][j+3] == simbolo) {
                return 1;
            }
        }
    }
    
    // Vertical
    for(int i = 0; i < LINHAS-3; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            if(tabuleiro[i][j] == simbolo && tabuleiro[i+1][j] == simbolo && 
               tabuleiro[i+2][j] == simbolo && tabuleiro[i+3][j] == simbolo) {
                return 1;
            }
        }
    }
    
    // Diagonal (esquerda para direita)
    for(int i = 0; i < LINHAS-3; i++) {
        for(int j = 0; j < COLUNAS-3; j++) {
            if(tabuleiro[i][j] == simbolo && tabuleiro[i+1][j+1] == simbolo && 
               tabuleiro[i+2][j+2] == simbolo && tabuleiro[i+3][j+3] == simbolo) {
                return 1;
            }
        }
    }
    
    // Diagonal (direita para esquerda)
    for(int i = 0; i < LINHAS-3; i++) {
        for(int j = 3; j < COLUNAS; j++) {
            if(tabuleiro[i][j] == simbolo && tabuleiro[i+1][j-1] == simbolo && 
               tabuleiro[i+2][j-2] == simbolo && tabuleiro[i+3][j-3] == simbolo) {
                return 1;
            }
        }
    }
    
    return 0;
}

int tabuleiroCheio() {
    for(int j = 0; j < COLUNAS; j++) {
        if(tabuleiro[0][j] == ' ') return 0;
    }
    return 1;
}

void jogar() {
    inicializarTabuleiro();
    int jogadorAtual = 1;
    int coluna;
    char simbolo;
    
    printf("Digite o nome do Jogador 1 (O): ");
    fgets(jogador1, sizeof(jogador1), stdin);
    jogador1[strcspn(jogador1, "\n")] = 0;
    
    printf("Digite o nome do Jogador 2 (X): ");
    fgets(jogador2, sizeof(jogador2), stdin);
    jogador2[strcspn(jogador2, "\n")] = 0;
    
    while(1) {
        mostrarTabuleiro();
        
        if(jogadorAtual == 1) {
            printf("%s (O), escolha uma coluna (1-7): ", jogador1);
            simbolo = 'O';
        } else {
            printf("%s (X), escolha uma coluna (1-7): ", jogador2);
            simbolo = 'X';
        }
        
        scanf("%d", &coluna);
        
        if(!adicionarPeca(coluna, simbolo)) {
            printf("Coluna invalida ou cheia! Tente novamente.\n");
            system("pause");
            continue;
        }
        
        if(verificarVitoria(simbolo)) {
            mostrarTabuleiro();
            if(jogadorAtual == 1) {
                printf("Parabens %s! Voce ganhou!\n", jogador1);
            } else {
                printf("Parabens %s! Voce ganhou!\n", jogador2);
            }
            break;
        }
        
        if(tabuleiroCheio()) {
            mostrarTabuleiro();
            printf("Empate! O tabuleiro esta cheio.\n");
            break;
        }
        
        jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
    }
}

int main() {
    int opcao;
    
    while(1) {
        system("cls");
        printf("=== LIGUE 4 ===\n\n");
        printf("1. Iniciar Jogo\n");
        printf("2. Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer
        
        switch(opcao) {
            case 1:
                jogar();
                printf("\n1. Jogar Novamente\n");
                printf("2. Sair\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
                getchar();
                if(opcao == 2) return 0;
                break;
            case 2:
                printf("Obrigado por jogar!\n");
                return 0;
            default:
                printf("Opcao invalida!\n");
                system("pause");
        }
    }
    
    return 0;
}