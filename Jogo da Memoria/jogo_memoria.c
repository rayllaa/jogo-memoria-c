#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "time.h"
#include "string.h"
#include "windows.h"
#include "conio.h"

void startGame();
void choosePair();
void gameChoice();
void endGame();
void newGame();

void numRand();
void hideGame();
void showHiddenGame();
int shuffleArray(int length, int p[length]);
void header();
void gotoxy(int x, int y);//coluna, linha

int p[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int n[16], i, j, num_pair = 0, hit = 0, miss = 0;
char hiddenGame[4][4], game[4][4], coord1[2], coord2[2], dateStr[9], timeStr[9], d[5], m[5], y[5];

void main(){
    setlocale(LC_ALL, "Portuguese");
    system("color 1F");
    startGame();
}

//Inicia jogo
void startGame(){
    int x = 0, row = 8, col = 34;
    hit = 0;
    miss = 0;

    numRand();

    header();
    gotoxy(17,5);printf("Você terá 5 segundos para memorizar os pares!\n");
    gotoxy(34,6);printf("Boa sorte!\n\n");
    Sleep(5000);

    for(i = 0;i < 4;i++){
      for(j = 0;j < 4;j++){
        game[i][j] = n[x]+'0';
        gotoxy(col,row);
        printf("%c ",game[i][j]);
        x++;
        col += 3;
      }
      printf("\n");
      col = 34;
      row += 2;
    }
    Sleep(5000);
    hideGame();//mapeia matriz com asteriscos, "esconde o jogo"

    choosePair();//escolha dos pares
}
//método que tratará as escolhas dos pares e as exceções envolvidas
void choosePair(){
    int i1, i2, j1, j2, r, row = 8, col = 34, coord1 = 0, coord2 = 0, choice1 = 0, choice2 = 0;

    do{
        header();
        showHiddenGame();//exibe matriz com * > jogo escondido

        //gotoxy(2,16);printf("PLACAR ");
        gotoxy(4,17);printf("Acertos: %d",hit);
        gotoxy(4,18);printf("Erros: %d",miss);

        do{
            gotoxy(2,20);printf("Informe as coordenadas do 1º número: [   ]");
            gotoxy(40,20);scanf("%d",&i1);
            gotoxy(40,21);scanf("%d",&j1);

            if((i1 < 0 || i1 > 3) || (j1 < 0 || j1 > 3)){//testa se não é uma coordenada válida
                gotoxy(20,5);printf("                                                   ");//"limpa" o texto
                gotoxy(25,5);printf("Digite uma coordenada válida!");
                coord1 = 0;//falso
            }else{ //se for uma coordenada válida
                coord1 = 1;//verdadeiro
                if(hiddenGame[i1][j1] != '*'){ //testa se o índice já foi escolhido
                    gotoxy(20,5);printf("                                                   ");//"limpa" o texto
                    gotoxy(20,5);printf("Índice já escolhido! Escolha outra coordenada!");
                    choice1 = 0;
                }else{
                    choice1 = 1; //recebe verdadeiro se o índice não foi escolhido
                }
            }
        }while(coord1 == 0 || choice1 == 0);
        gotoxy(20,5);printf("                                                   ");//"limpa" o texto

        num_pair++;//1
        gameChoice(i1, j1);//add valores dos pares na matriz hiddenGame()(jogo escondido ***) e contabiliza erros e acertos

        do{
            gotoxy(2,23);printf("Informe as coordenadas do 2º número: [   ]\n\n");
            gotoxy(40,23);scanf("%d",&i2);
            gotoxy(40,23);scanf("%d",&j2);

            if((i2 < 0 || i2 > 3) || (j2 < 0 || j2 > 3)){//testa se não é uma coordenada válida
                gotoxy(20,5);printf("                                                   ");//"limpa" o texto
                gotoxy(25,5);printf("Digite uma coordenada válida!");
                coord2 = 0;//falso
            }else{ //se for uma coordenada válida
                coord2 = 1;//verdadeiro
                if(hiddenGame[i2][j2] != '*'){ //testa se o índice já foi escolhido
                    gotoxy(20,5);printf("                                                   ");//"limpa" o texto
                    gotoxy(20,5);printf("Índice já escolhido! Escolha outra coordenada!");
                    choice2 = 0;
                }else{
                    choice2 = 1; //recebe verdadeiro se o índice não foi escolhido
                }
            }
        }while(coord2 == 0 || choice2 == 0);
        gotoxy(20,5);printf("                                                   ");//"limpa" o texto

        num_pair++;//2
        gameChoice(i2, j2);

        num_pair = 0;
    }while(hit < 8 && miss <= 10);

    endGame();//metodo de final de jogo
}

//método que add os valores dos pares escolhidos na matriz hiddenGame()(jogo escondido ***) e contabiliza erros ou acertos
void gameChoice(int i, int j){

    if(num_pair == 1){//se for o 1º número do par
        coord1[0] = i;
        coord1[1] = j;
        hiddenGame[coord1[0]][coord1[1]] = game[i][j]; //número escolhido é exibido na matriz com *
        showHiddenGame();
    }
    if(num_pair == 2){ //se for o 2º número do par
        coord2[0] = i;
        coord2[1] = j;
        hiddenGame[coord2[0]][coord2[1]] = game[coord2[0]][coord2[1]];
        showHiddenGame();

        if(hiddenGame[coord1[0]][coord1[1]] == hiddenGame[coord2[0]][coord2[1]]){//testa se os números escolhidos são iguais
            gotoxy(25,5);printf("Parabéns! Você acertou o par!");
            hit++;//incrementa os acertos
            gotoxy(4,17);printf("Acertos: %d",hit);
        }else{
            gotoxy(34,5);printf("Você errou!");
            hiddenGame[coord1[0]][coord1[1]] = '*';
            hiddenGame[coord2[0]][coord2[1]] = '*';
            miss++;//incrementa os erros
            gotoxy(4,18);printf("Erros: %d",miss);
        }
        Sleep(3000);
    }
}

//Dá resultado do jogo ganhou/perdeu, salva pontuação no arquivo e chama newGame()
void endGame(){
    char op[2], name[255];
    FILE *arquivo;

    header();
    if(hit == 8){
        gotoxy(27,5);printf(" P  A  R  A  B  É  N  S ! ");
        gotoxy(30,7);printf("VOCÊ GANHOU O JOGO!");
        gotoxy(29,9);printf("Acertos: %d ",hit);
        gotoxy(41,9);printf("Erros: %d",miss);
    } else{
        gotoxy(29,5);printf(" G A M E    O V E R ! ");
        gotoxy(30,7);printf("VOCÊ PERDEU O JOGO!");
        gotoxy(29,9);printf("Acertos: %d",hit);
        gotoxy(41,9);printf("Erros: %d",miss);
    }

    gotoxy(5,11);printf("_____________________________________________________________________");
    gotoxy(25,14);printf("Deseja salvar a pontuação do jogo?");
    gotoxy(25,15);printf("S - Sim");
    gotoxy(25,16);printf("N - Não");
    gotoxy(60,14);fflush(stdin);gets(op);

    _strdate(dateStr);
	_strtime(timeStr);
	char d[5]={dateStr[3],dateStr[4]};
	char m[5]={dateStr[0],dateStr[1]};
	char y[5]={dateStr[6],dateStr[7]};

    if(strcmp(strupr(op),"S") == 0){
        gotoxy(25,18);printf("Insira o nome do jogador: ");
        gotoxy(51,18);fflush(stdin);gets(name);

            arquivo = fopen("C:/jogomem.txt","a");//cria arquivo
            fprintf(arquivo,"Jogador: %s\nAcertos: %i\nErros: %i\nData e Hora: %s/%s/%s %s\n\n-----------------------\n\n",name,hit,miss,d,m,y,timeStr);
            fclose(arquivo);
            gotoxy(25,22);printf("Pontuação salva com sucesso!!");
            Sleep(4000);
        }
    newGame();
}

void newGame(){
    char op[2];

    header();
    gotoxy(28,5);printf("Deseja jogar novamente? ");
    gotoxy(28,6);printf("S - Sim");
    gotoxy(28,7);printf("N - Não");
    gotoxy(52,5);scanf("%s",&op);

     if(strcmp(strupr(op),"S") == 0){
        system("cls");
        startGame();
     }
     else{
        gotoxy(30,11);printf("Finalizando jogo...");
        Sleep(3000);
        //gotoxy(1,13);system("pause");
     }
}

//Mapeia vetor com todos os valores possíveis e depois embaralha e add em um vetor de 16 índices
void numRand(){
    srand(time(NULL));
    int j = 0;

    p[10] = shuffleArray(10, p); //embaralha vetor

    //mapeia vetor auxiliar que irá compor a matriz
    for(i = 0;i < 16;i++){
      n[i] = p[j];
      if(i == 7){
        j = 0;
      }else{
        j++;
      }
    }
    n[16] = shuffleArray(16, n); //embaralha vetor auxiliar que irá compor a matriz
}

//mapeia matriz com asteriscos
void hideGame(){
    for(i = 0;i < 4;i++){
        for(j = 0;j < 4;j++){
            hiddenGame[i][j] = '*';
        }
    }
}

//exibe matriz com asteriscos
void showHiddenGame(){
    int row = 8, col = 34;

    for(i = 0;i < 4;i++){
        for(j = 0;j < 4;j++){
            gotoxy(col,row);
            printf("%c",hiddenGame[i][j]);
            col += 3;
        }
        printf("\n");
        col = 34;
        row += 2;
    }
}

//embaralha vetor
int shuffleArray(int length, int p[length]){
    for(i = 0;i < length;i++){
      int x = rand()%length;//gera índice aleatório no vetor ex: length 10 16
      if(x != i){
        int aux = p[i];
        p[i] = p[x];
        p[x] = aux;
      }
    }
    return (int)p;
}

void header(){
    system("cls");
    gotoxy(32,2);printf("JOGO DA MEMÓRIA");
    gotoxy(5,3);printf("_____________________________________________________________________");
}

void gotoxy(int x, int y){
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



