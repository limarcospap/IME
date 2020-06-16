#include <bits/stdc++.h>

using namespace std;

class jogador
{
	private:
		string nome;
		int ataque, passe, defesa;
	public:
		jogador(string n, int a, int p, int d)
		{
			nome = n;
			ataque = a;
			passe = p;
			defesa = d;
		};

		virtual int calculaHabilidade()
		{
			return (ataque + passe + defesa);
		};
		
		string getNome()
		{
			return nome;
		}
};

class levantador : public jogador
{
	int melhorjogador;
	public:
		levantador(string n, int melhor) : jogador(n, 1,6,3){
			melhorjogador = melhor;
		};

		int calulaHabilidade()
		{
			return (jogador::calculaHabilidade() + melhorjogador*10);
		};

};

class libero : public jogador\
{
	int qualidadepasse; 
	public:
		libero(string n, int qp) : jogador(n, 0, 5, 5)
		{
			qualidadepasse = qp;	
		};
		int calculaHabilidade()
		{
			int habilidade;
			habilidade = jogador::calculaHabilidade();
			if((qualidadepasse/10) == 0)
			{ 
				return habilidade;
			}
			else
			{
			for(int i = 0; i<(qualidadepasse/10); i++)
			{
				habilidade = habilidade*2;
			}
			return habilidade;
			}
		};

};

class meia : public jogador
{
	int naobloqueio;
	public:
		meia(string n, int nb) : jogador(n, 4, 1, 3){
			naobloqueio = nb;
		};
		int calculaHabilidade()
		{
			return (jogador::calculaHabilidade()-naobloqueio);
		}
};


class ponta : public jogador
{
	public:
		ponta(string n) : jogador(n, 4, 3, 3){};
};


class oposto : public jogador
{
	int maispontos;
	public:
		oposto(string n, int mp) : jogador(n, 6, 1, 3)
		{
			maispontos = mp;
		};
		int calculaHabilidade()
		{
			return (jogador::calculaHabilidade()+20*maispontos);
		}
};

class Time
{
	private:
		const string nome_do_time;
		jogador ** array;
		int contador, cponta, coposto, clibero, clevantador, cmeia;
	public:
		Time(string nome): contador(0), coposto(0), cponta(0), clibero(0), clevantador(0), cmeia(0), nome_do_time(nome)
		{	
			array = new jogador*[7]; 
		}

		void add_jogador(oposto & jog)
		{
			if(contador<7 && coposto <1){
			array[contador] = &jog;
			contador++;
			coposto++;
			}
			else
			{
				cout << "O time ja possui 7 jogadores ou ja possui um oposto!"<< endl;
			}
		}
		void add_jogador(ponta & jog)
		{
			if(contador<7 && cponta<2){
			array[contador] = &jog;
			contador++;
			cponta++;
			}
			else
			{
				cout << "O time ja possui 7 jogadores ou ja possui 2 pontas!"<< endl;
			}
		}
		void add_jogador(libero & jog)
		{
			if(contador<7 && clibero < 1){
			array[contador] = &jog;
			clibero++;
			contador++;
			}
			else
			{
				cout << "O time ja possui 7 jogadores ou ja possui um libero!"<< endl;
			}
		}
		void add_jogador(meia & jog)
		{
			if(contador<7 && cmeia < 2){
			array[contador] = &jog;
			cmeia++;
			contador++;
			}
			else
			{
				cout << "O time ja possui 7 jogadores ou ja possui dois meias!"<< endl;
			}
		}
		void add_jogador(levantador & jog)
		{
			if(contador<7 && clevantador < 1){
			array[contador] = &jog;
			clevantador++;
			contador++;
			}
			else
			{
				cout << "O time ja possui 7 jogadores ou ja possui um levantador!"<< endl;
			}
		}
		~Time()
		{
			delete[] array;
		}
		string get_nome_do_time() const { return nome_do_time; };
		float pegarHabilidadeTotal()
		{
			int habilidade;
			if(contador<7) return -1;
			else
			{
				habilidade = 0;
				for(int i = 0; i<7; i++)
				{
					habilidade = habilidade + array[i]->calculaHabilidade();
				}
				return habilidade;
			}
		}
};

class Partida
{
	private:
		int set, partida, setstatus;
	public:
		Partida(): set(1), partida(1), setstatus(1) { }; //Construtor
		
		//Funcao que realiza cada jogada
		int jogada(int saque, int h0,int h1)
		{
			int sorteio;
			float p;
			srand( (unsigned)time(NULL) );
			sorteio = rand()%100;
			
			if( saque == 0)
			{
				p = (h0*1.25)/(h0*1.25+h1);
				
				if(sorteio < p*100)
				{
					return 0;
				}
				else
				{
					return 1;
				}
			}
			else
			{
				p = (h1*1.25)/(h1*1.25+h0);

				if(sorteio < p*100)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}	
		}
		//Funcao que realiza a partida em si
		int realizar(Time & t0, Time & t1)
		{
			int h0, h1, pontos0 = 0, pontos1 = 0, set0 = 0, set1 = 0, saque = 0;
			h0 = t0.pegarHabilidadeTotal();
			h1 = t1.pegarHabilidadeTotal();
			
			while(partida)
			{
				while(setstatus)
				{
					if(jogada(saque,h0,h1) == 0)
					{
						pontos0++;
						//cout << t0.get_nome_do_time() << endl;

					}
					else
					{
						pontos1++;
						//cout << t1.get_nome_do_time() << endl;
					}

					saque = (saque+1)%2;
				
					if((pontos0 >= 25) && (pontos0 >= pontos1+2))
					{
						set0++;
						set++;
						setstatus = 0;	
					}
					else if((pontos1 >= 25) && (pontos1 >= pontos0+2))
					{
						set1++;
						set++;
						setstatus = 0;
					}
					else if(pontos0 == 15 && set == 5)
					{
						set0++;
						set++;
						setstatus = 0;
											}
					else if(pontos1 == 15 && set == 5)
					{
						set1++;
						set++;
						setstatus = 0;
					}
				}
				
				if(set == 6) partida = 0;
				setstatus = 1;
				pontos0 = 0;
				pontos1 = 0;
			}
			if(set0 >= 3) cout << "O time vencedor foi o "<< t0.get_nome_do_time() << endl;
			else cout <<" O time vencedor foi o " << t1.get_nome_do_time() << endl;
		}

};

int main()
{
	Time barca("Barcelona");
	levantador j1("j1", 2);
	barca.add_jogador(j1);
	ponta j2("j2");
	barca.add_jogador(j2);
	ponta j3("j3");
	barca.add_jogador(j3);
	oposto j4("j4", 1);
	barca.add_jogador(j4);
	meia j5("j5", 5);
	barca.add_jogador(j5);
	meia j6("j6", 1);
	barca.add_jogador(j6);
	libero j7("j7", 30);
	barca.add_jogador(j7);
	
	Time real("Real");
	levantador j01("j1", 20);
	real.add_jogador(j01);
	ponta j02("j2");
	real.add_jogador(j02);
	ponta j03("j3");
	real.add_jogador(j03);
	oposto j04("j4", 5);
	real.add_jogador(j04);
	meia j05("j5", 20);
	real.add_jogador(j05);
	meia j06("j6", 1);
	real.add_jogador(j06);
	libero j07("j7", 10);
	real.add_jogador(j07);
	
	Partida elclassico;

	elclassico.realizar(barca,real);
}
