#include <stdio.h>
#include <stdlib.h>
//struct do aluno
typedef struct aluno{
	char nome[50];
	int codigo;
	int cpf;
	int disciplinas[20];
	struct aluno* prox;
}aluno;
//struct da disciplina
typedef struct disciplina{
	int cod;
	char nome[20];
	char professor[50];
	int creditos;
	struct disciplina* prox;
}disciplina;
//funçao para adicionar alunos
aluno* addAlu(aluno* primAlu, FILE* file){
	aluno* alu;
	alu = (aluno*)malloc(sizeof(aluno));
	printf("Digite o nome do aluno:\n");
	scanf("%s", alu->nome);
	fprintf("%s\n", alu->nome);
	printf("Digite o CPF do aluno:\n");
	scanf("%d", &alu->cpf);
	fprintf("%d", alu->cpf);
	alu->prox = primAlu;
	return alu;
}

int main(){
	FILE* file;
	aluno* primAlu = NULL;
	disciplina* primDis = NULL;
	int addAluno = 1;
	
	file = fopen("salvar.txt", "w");

	while(addAluno){
		primAlu = addAlu(primAlu, file);
		printf("Deseja continuar adicionando?\n 0-N 1-S\n");
		scanf("%d", &addAluno);
	}
}

