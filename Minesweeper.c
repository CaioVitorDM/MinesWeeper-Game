 #include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* precisamos criar uma struct que define como será a célula do nosso campo minado, onde
-se for bomba: 0 ou 1;
-se está aberta: 0 ou 1;
-quais são os seus vizinhos(dicas): 0 a 4;
*/

typedef struct{
int bomba;
int aberta;
int vizinhos;
}Celula;

//iremos criar uma função para

// precisamos criar agora as variáveis globais do nosso jogo.

Celula campo[10][20]; //cria a matriz do campo minado.
int tam1 = 10;
int tam2 = 20;
int l, c;


//é necessário inicializar a matriz do jogo, porque é como se todas posições estivessem vazias, então precisamos preenchê-las com dicas, bombas ou espaços vazios, mas antes temos que inicializá-la.

void inicia_jogo(){
  for(l = 0; l < tam1; l++){
    for(c = 0; c < tam2; c++){
      campo[l][c].bomba = 0;
      campo[l][c].aberta = 0;
      campo[l][c].vizinhos = 0;
      
    }
  }
}

//após a matriz ser inicializada, precisamos sortear as 40 bombas na matriz.

void sorteio_bomba(int q_bombas){
  int i;
  srand(time(NULL)); //passa uma semente NULL como paramêtro.
  for(i = 1; i <= q_bombas; i++){
    l = rand() % tam1; 
    c = rand() % tam2;
    if(campo[l][c].bomba == 0){
      campo[l][c].bomba = 1;
    }
    else{
      i--;
    }
  }
}

//ao serem colocadas as bombas, agora precisamos verificar os espaços vizinhos a elas e preenchê-los com dicas e contar as bombas restantes.

// Para facilitar nossa vida, vamos criar uma função que retorne a quantidade de bombas na vizinha de [l][c](linhas e colunas), onde n representa a quantidade de bombas.

/* Precisamos agora dessa função que retorna se o índice de coordenadas é válido ou não.
se retornar 1 - é válido
se retornar 0 - não é válido
*/

//função que retorna se o índice é válido ou não
int validacao_indice(int l, int c){
  if(l >= 0 && l < tam1 && c >= 0 && c < tam2){
    return 1;
  }
  else{
    return 0;
  }
}


//Função que retorna a quantidade de bombas na vizinhança dos indíces.
int quant_vizinhos_bombasticos(int l, int c){
  /* as posições que temos que verificar são
    l - 1 e c; posicao acima
    l + 1 e c; posicao abaixo
    l e c + 1; posicao a direita
    l e c - 1; posicao a esquerda
    l - 1 e c - 1; diagonal a esquerda de cima
    l - 1 e c + 1; diagonal a direita de cima
    l + 1 e c - 1; diagonal a esquerda de baixo
    l + 1 e c + 1  diagonal a direita de baixo

  porém precisamos saber se esses índices da função são válidos ou não, para isso precisamos de outra função.
  */
  int quantidade = 0;
  if(validacao_indice(l - 1, c) && campo[l-1][c].bomba){
    quantidade++;
  }
  if(validacao_indice(l + 1, c) && campo[l+1][c].bomba){
    quantidade++;
  }
  if(validacao_indice(l, c + 1) && campo[l][c+1].bomba){
    quantidade++;
  }
  if(validacao_indice(l, c - 1) && campo[l][c-1].bomba){
    quantidade++;
  }
  if(validacao_indice(l - 1, c - 1) && campo[l-1][c-1].bomba){
    quantidade++;
  }
  if(validacao_indice(l - 1, c + 1) && campo[l-1][c+1].bomba){
    quantidade++;
  }
  if(validacao_indice(l + 1, c - 1) && campo[l+1][c-1].bomba){
    quantidade++;
  }
  if(validacao_indice(l + 1, c + 1) && campo[l+1][c+1].bomba){
    quantidade++;
  }
return quantidade;
}

// função para contagem das bombas nos vizinhos.
void contagem_bombas(){
  for(l = 0; l < tam1; l++){
    for(c = 0; c < tam2; c++){
      campo[l][c].vizinhos = quant_vizinhos_bombasticos(l, c);
      
    }
  }
} 

//Precisamos agora imprimir o campo do jogo para o usuário poder jogá-lo.

//função de impressão da malha do campo.
void imprime_campo(){
  printf("\n\n\t");
  for(l = 0; l < tam2; l++){
    printf("\t%d", l); //impressão dos indices das colunas.
  }
  printf("\n\t------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  for(l = 0; l < tam1; l++){
    printf("\t%d|", l); //impressão dos indices das linhas.
    for(c = 0; c < tam2; c++){
      if(campo[l][c].aberta){
          if(campo[l][c].bomba){
            printf("*");
          }
          else{
            printf("%d", campo[l][c].vizinhos);
          }
      }
      else{
        printf(" ");
      }
      printf("\t |");
    }
    printf("\n\t------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
  }
}

//precisamos agora de uma função que faz o jogo funcionar, que é o de leitura das coordenadas

//após isso precisamos também de uma função que sirva para abrir a célula das coordenadas especificadas pelo usuário.

//função para abrir a célula.
void desbloquear_celula(int l, int c){
  if(validacao_indice(l, c) == 1 && campo[l][c].aberta == 0)//caso base da recursão, que checa se a coordenada é válida e se ela está fechada.
  {
    campo[l][c].aberta = 1;
    if(campo[l][c].vizinhos == 0){
      /*
      l - 1 e c; posicao acima
      l + 1 e c; posicao abaixo
      l e c + 1; posicao a direita
      l e c - 1; posicao a esquerda
      l - 1 e c - 1; diagonal a esquerda de cima
      l - 1 e c + 1; diagonal a direita de cima
      l + 1 e c - 1; diagonal a esquerda de baixo
      l + 1 e c + 1  diagonal a direita de baixo
      */

    //chamada recursiva da função para abrir as celulas, nas 8 posições ao redor da coordenada dita pelo usuário.
      desbloquear_celula(l-1, c);
      desbloquear_celula(l+1, c);
      desbloquear_celula(l, c+1);
      desbloquear_celula(l, c-1);
      desbloquear_celula(l-1, c-1);
      desbloquear_celula(l-1, c+1);
      desbloquear_celula(l+1, c-1);
      desbloquear_celula(l+1, c+1);
    }
  }
}

/*
  Criaremos também uma função para verificar se houve vitória, ou seja, se todas as células que não continham bombas foram abertas.
  1 - houve a vitória.
  0 - Ainda não houve vitória.
*/

//função que verifica vitória, percorrendo a matriz e fazendo a checagem.
int vitoria(){
  int quantidade = 0;
  for(l = 0; l < tam1; l++){
    for(c = 0; c < tam2; c++){
      if(campo[l][c].aberta == 0 && campo[l][c].bomba == 0)//checa se a posição está fechada e se não tinha bomba.
      {
        quantidade++;
      }
    }
  }
  return quantidade;
}


//Função de ajuda para o jogador.
void ajuda(){
  for(l = 0; l < tam1; l++){
    for(c = 0; c < tam2; c++){
      if(campo[l][c].bomba == 0 && campo[l][c].aberta == 0){ //a função percorre a matriz e checa se a coordenada está aberta e se ela não possui bomba, se cumprir os requisitos, ela a abre.
        desbloquear_celula(l, c);
        break;
      }
    }
  }
}

//Função para sortear uma coordenada, caso o jogador deseje.
void sortear(){
  srand(time(NULL));
  l = rand() % tam1; 
  c = rand() % tam2;
  if(campo[l][c].bomba == 0 && campo[l][c].aberta == 0){ 
    desbloquear_celula(l, c);
  }
}


//função de leitura de coordenadas.
void play(){
  float tempo, tempo_auxiliar, tempinho; //variável que vai receber a diferença entre tempo inicial e tempo final.
  time_t tempo_inicial, tempo_final, tempo_aux; //declaração das variáveis utilizando a biblioteca <time.h>
  tempo_inicial = time(NULL); //atribuição do valor do tempo inicial a variável.
  int linha, coluna;
  char menu;
  do{
    imprime_campo();
    printf("\nDigite C para coordenada, T para tempo, A para ajuda e S para sortear uma coordenada: ");
    scanf("%c", &menu);
    if(menu == 'C'){
      do{
          printf("\nDigite as coordenadas de linha e coluna: ");
          scanf("%d%d", &linha, &coluna);
          if(validacao_indice(linha, coluna) == 0 || campo[linha][coluna].aberta == 1){
            printf("\nCoordenada inválida ou já aberta!\n");
          }
      }while(validacao_indice(linha, coluna) == 0 || campo[linha][coluna].aberta == 1);
    
      desbloquear_celula(linha, coluna);
    }
    if(menu == 'T'){
      tempo_aux = time(NULL);
      tempo_auxiliar = difftime(tempo_aux, tempo_inicial);
      printf("\n\tO tempo de jogo decorrido é de %.2f segundos.\n", tempo_auxiliar);
    }
    if(menu == 'A'){
      ajuda();
    }
    if(menu == 'S'){
      sortear();
    }
  }while(vitoria() != 0 && campo[linha][coluna].bomba == 0);

  
  
  if(campo[linha][coluna].bomba == 1){
    printf("\n\tVocê perdeu, mais sorte da próxima vez!\n");
    tempo_final = time(NULL); //atribuição do tempo final a variável
    tempo = difftime(tempo_final, tempo_inicial); //cálculo da diferença entre tempo final e inicial para saber o tempo decorrido utilizando a função difftime da biblioteca.
    if(tempo < 60){
      printf("\n\tO tempo de jogo foi de %.2f segundos.", tempo);
      }
    else{
      tempinho = tempo / 60;
      printf("\n\tO tempo de jogo foi de %.2f minutos.", tempinho);
    }
  }
  else{
    printf("\n\tMEUS PARABÉNS, VOCÊ VENCEU. OBRIGADO POR TER JOGADO NOSSO JOGO!\n");
    tempo_final = time(NULL);
    tempo = difftime(tempo_final, tempo_inicial);
    if(tempo < 60){
      printf("\n\tO tempo de jogo foi de %.2f segundos.", tempo);
      }
    else{
      tempinho = tempo / 60;
      printf("\n\tO tempo de jogo foi de %.2f minutos.", tempinho);
    }
  }
  imprime_campo();
}


int main(void) {
  int opcao;
  do{
    inicia_jogo();
    sorteio_bomba(40);
    contagem_bombas();
    printf("\n\n\t\t\t\t\t\t\t\t\t***CAMPO MINADO***\n\n");
    play();

    printf("\nDigite 1 para jogar novamente e 0 para parar: ");
    scanf("%d", &opcao);
    if(opcao == 0){
      printf("\n\tJogo Encerrado!");
      break;
    }
  }while(opcao == 1);
}