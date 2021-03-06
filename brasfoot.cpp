#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

int rodadas[45] = {1,2,3,4,5,6,7,8,9,12,13,14,15,16,17,18,19,23,24,25,26,27,28,29,34,35,36,37,38,39,45,46,47,48,49,56,57,58,59,67,68,69,78,79,89};
int roacon[45];
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
void roda(){
    int c=0;
    int roabin=0;
    for(int m=0;m<5;m++)
    {
       rodatual[m]=0;
    }
    for(int d=0;((d<45) && (c<5));d++){
       int roabin=0;
       for(int h=0;h<45;h++){
           if(rodadas[d]==roacon[h]){
               roabin=1;
           }
       }

       if(roabin==0){
           int n1,n2,n3,n4;
           if(rodadas[d] < 10){  n1=0; }else { n1=rodadas[d]/10; n2=rodadas[d]-n1*10; }
           if(n1==0){
                for(int j=0;j<5;j++){
                   if((rodatual[j]<10)&&(rodatual[j] >= 1)){
                        n1=1;
                    }
                }
                if(n1==0){
                    rodatual[c]=rodadas[d];
                    roacon[d]=rodadas[d];
                    c++;
                 }
             }else{
                  int u=0;
                  for(int k=0;k<5;k++){
                      if(rodatual[k] > 10){ n3=rodatual[k]/10; n4=rodatual[k]-n3*10; }
                      else{ n3=0; n4=rodatual[k]; }
                      if(!(((n1==n3) || (n1==n4))  || ((n2==n3) || (n2==n4)))){
                          u+=1;
                      }
                  }
                  if(u==5){
                      rodatual[c]=rodadas[d];
                      roacon[d]=rodadas[d];
                      c++;
                  }

             }
       }
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
   for(int t = 0;t<45;t++){
       roacon[t]=0;
   }
   int timeuser;
/*===================================*/

   for(int ro=0;ro<10;ro++)
   {
      roda();


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

              int ataque1 = time[t1]->ataque+(time[0]->numaleatorio(0,7));
              int ataque2 = time[t2]->ataque+(time[0]->numaleatorio(0,7));
              int defesa1 = time[t1]->defesa+(time[0]->numaleatorio(0,7));
              int defesa2 = time[t2]->defesa+(time[0]->numaleatorio(0,7));

              if(ataque1 > defesa2){ gols[x][0] = ataque1-defesa2; }else if((ataque1==defesa2) || (ataque1 < defesa2)){ gols[x][0]=0;}

              if(ataque2 > defesa1){ gols[x][1] = ataque2-defesa1; }else if((ataque2==defesa1) || (ataque2 < defesa1)){ gols[x][1]=0;}

              time[t1]->golmarcados = gols[x][0];
              time[t1]->golsofridos = gols[x][1];
              time[t2]->golmarcados = gols[x][1];
              time[t2]->golsofridos = gols[x][0];

              if(gols[1]>gols[2]){
                  time[t1]->pontos += 3;

              }else if(gols[2] > gols[1]){
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
