#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

int rodatual[5]={0,0,0,0,0};


class Times{
public:
     string nome;
     int ataque;
     int defesa;
     int meio;
     int pontos;
     int golmarcados;
     int golsofridos;
     int formacao;  /* 1 para defensivo 2 para equilibrado e 3 para ofensivo*/
     int numaleatorio(int maior,int menor);
     void ini(string nome);

private:
};
int Times::numaleatorio(int maior,int menor)
{
     srand((unsigned)time(0)); //para gerar números aleatórios reais.
     int aleatorio = rand()%(maior-menor+1) + menor;
     return aleatorio;
}
void Times::ini(string nome){
      this->nome = nome;
      this->ataque = (this->numaleatorio(15,0))+50;
      this->defesa = (this->numaleatorio(15,0))+50;
      this->pontos = 0;
      this->golmarcados = 0;
      this->golsofridos = 0;
      this->formacao =this->numaleatorio(3,1);
}

/*=======================================================================================================================*/
void roda(int rodada){

    short int time[9][5] = {{1,23,45,67,89},
        	               {2,13,46,58,79},
                	       {3,12,47,59,68},
          	       	       {4,15,26,37,89},
                               {5,16,24,38,78},
                               {6,17,25,39,75},
                               {7,18,26,34,76},
                               {8,19,27,35,84},
                               {9,14,28,36,64}};

    for(int c=0;c < 5;c++){
         rodatual[c]=time[rodada][c]; 
    }

}
/*==================================================================================================================================================================*/


int main(){

   string nomes[10] = {"Toledo","Maringa","Cianorte","Coritiba","Londrina","Operario","Parana","Atletico","Rio branco","Cascavel"};
   Times *time[10];
   for(int c=0;c<10;c++){
       time[c] = new Times();
       time[c]->ini(nomes[c]);
       usleep((c*2000+c*500+1000000));
   }
   int timeuser;
/*===================================*/

   for(int ro=0;ro < 9;ro++)
   {
      roda(ro);


      if(ro==0){
         cout << "ESCOLHA SEU TIME"  << endl;
         for(int t=0;t<10;t++){
             cout << time[t]->nome << " [" << t << "]" << endl;
          }
          cin >> timeuser;

          cout << "\n===========CAMPEONATO PARANAENSE=============\n" << endl;
       }




   jogo:
   cout << "RODADA:" << ro << endl;
   cout << "[1]jogar ,[2]classificacao, [3]sair: \n";
   int opcao=0;
   cin >> opcao;
   switch(opcao) {
      case 1:
          int gols[5][2],t1,t2;

          for(int x=0;x<5;x++){

              if(rodatual[x] < 10){ t1=0;  t2 = rodatual[x];  }else{ t1 = rodatual[x]/10;  t2 = rodatual[x]-t1*10; }

              int ataque1 = (time[t1]->ataque) + (time[0]->numaleatorio(0,7));
              int ataque2 = (time[t2]->ataque) + (time[0]->numaleatorio(0,7));
              int defesa1 = (time[t1]->defesa) + (time[0]->numaleatorio(0,7));
              int defesa2 = (time[t2]->defesa) + (time[0]->numaleatorio(0,7));

              if(ataque1 > defesa2){ gols[x][0] = ataque1-defesa2; }else if((ataque1==defesa2) || (ataque1 < defesa2)){ gols[x][0]=0;}

              if(ataque2 > defesa1){ gols[x][1] = ataque2-defesa1; }else if((ataque2==defesa1) || (ataque2 < defesa1)){ gols[x][1]=0;}

              time[t1]->golmarcados += gols[x][0];
              time[t1]->golsofridos += gols[x][1];
              time[t2]->golmarcados += gols[x][1];
              time[t2]->golsofridos += gols[x][0];

              if(gols[x][0] > gols[x][1]){
                  time[t1]->pontos += 3;

              }else if(gols[x][1] > gols[x][0]){
                    time[t2]->pontos += 3;

              }else{
                    time[t1]->pontos += 1;
                    time[t2]->pontos +=1;
              }
          }
          for(int y=0;y<5;y++){
              if(rodatual[y] < 10){ t1=0;  t2 = rodatual[y];  }else{ t1 = rodatual[y]/10;  t2 = rodatual[y]-t1*10; }
              cout << time[t1]->nome << " " << gols[y][0] << " " << "x" <<  " " << gols[y][1] << " " << time[t2]->nome << endl;
              cout << "roda:" << rodatual[y] << endl;
          }



          break;
      case 2:
          cout << "PONTUAÇAO | GOLs | GOL SOFRIDOS | NOME |\n";
          for(int tt=0;tt<10;tt++){
               cout << time[tt]->pontos << "          " << time[tt]->golmarcados  << "           "<< time[tt]->golsofridos << "         " << time[tt]->nome << endl;
          }
          goto jogo;
          break;
      case 3:
          ro=20;
          break;
      default:
          cout << "digitou errado";
     }




}

/*=================*/
    for(int c=0;c<10;c++){
         cout << time[c]->nome << "  f:" << time[c]->formacao << " ataque:" << time[c]->ataque <<" meio:" <<  time[c]->meio << " defesa:" << time[c]->defesa << endl;
    }
   return 0;
}
