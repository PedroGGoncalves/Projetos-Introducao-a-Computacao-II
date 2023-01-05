#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#define MAX_REG 100

typedef struct {
   int dia;
   int mes;
   int ano;
} data;
typedef enum e_tipo_sanguineo_r {O=1, A, AB, B} t_e_tipo_sanguineo_r;
typedef enum e_fator_rh_r {POSITIVO=1, NEGATIVO} t_fator_rh_r;
typedef enum e_estado_civil_r {CASADO=1,SOLTEIRO} t_e_estado_civil_r;

typedef struct {
   int RA; 
   char nome[30];
   t_e_tipo_sanguineo_r tipo;
   t_fator_rh_r fator;
   t_e_estado_civil_r estado;
   char email[30];
   char curso[30];
   char telefone[30];
   data data;
} alunos;

typedef struct {
   int codigo;
   char nome[30];
   int carga;
   char sigla[30];
} disciplina;
typedef struct {
   int RA;
   int codigo;
   int semestre;
   int ano;
   double media;
   double freq;
} historico;

char menu() {
	int op;
	do {
		printf("\nMenu\n");
		printf("Alunos\n");
		printf(" 1.Inserir\n"); printf(" 2.Alterar\n"); printf(" 3.Excluir\n");	printf(" 4.Consultar\n");
		printf("Disciplinas\n");
		printf(" 5.Inserir\n");	printf(" 6.Alterar\n");	printf(" 7.Excluir\n");	printf(" 8.Consultar\n");
		printf("Historico\n");
		printf(" 9.Inserir\n");	printf(" 10.Alterar\n"); printf(" 11.Excluir\n"); printf(" 12.Listar\n");
		printf("13.Sair\n");
		printf("Opcao: ");
		scanf("%d", &op);
	} while (!13);
	return toupper(op);
}
//**********ALUNOS***************//
void posiciona_aluno(FILE *fp, int id) {
	fseek(fp, (id-1)*sizeof(alunos), SEEK_SET);
}
void inicializa_aluno(FILE *fp) {
	alunos a;
	
	strcpy(a.curso, "");
	strcpy(a.email, "");
	strcpy(a.nome, "");
	strcpy(a.telefone, "");
	a.RA=-1;
	
	for (int i = 1; i <= MAX_REG; i++) {	
	   posiciona_aluno(fp, i);
	   fwrite(&a, sizeof(alunos), 1, fp);
    }
}
bool verificaSeAlunoExiste(FILE *fp, int id) {
   alunos a;
   posiciona_aluno(fp, id);
   
   fread(&a, sizeof(alunos), 1, fp);
   if  (a.RA == -1)
      return false;   
   return true;
}
void inserir_aluno(FILE *fp) {
   alunos a;

   do {
      printf("RA: ");
      scanf("%d", &a.RA);
   } while(a.RA< 1 || a.RA > 100);
   
   if (verificaSeAlunoExiste(fp, a.RA)) {
   	 printf("Aluno ja inserido. Caso queira alterar, escolha a opcao correspondente!"); return;
   }
   
   fflush(stdin);
   printf("Nome: "); fgets(a.nome,30,stdin);
   printf("Tipo (O=1, A=2, AB=3, B=4): "); scanf("%d", &a.tipo);
   printf("Fator (POSITIVO=1, NEGATIVO=2): "); scanf("%d", &a.fator);
   printf("Estado Civil (CASADO=1,SOLTEIRO=2): "); scanf("%d", &a.estado); fflush(stdin);
   printf("e-mail: "); fgets(a.email,30,stdin); fflush(stdin);
   printf("Curso: "); fgets(a.curso,30,stdin);
   printf("DtNasc:\n");
   printf("Dia: "); scanf("%d", &a.data.dia);
   printf("Mes: "); scanf("%d", &a.data.mes);
   printf("Ano: "); scanf("%d", &a.data.ano); fflush(stdin);
   printf("Telefone: "); fgets(a.telefone,30,stdin);
   
   posiciona_aluno(fp, a.RA);
   if (fwrite(&a, sizeof(alunos), 1, fp))
      printf("Aluno cadastrado com sucesso!\n");
}
void alterar_aluno(FILE *fp) {
   alunos a;
 
   do {
      printf("RA: ");
      scanf("%d", &a.RA);
   } while(a.RA < 1 || a.RA > 100);
   
   if (!verificaSeAlunoExiste(fp, a.RA)) {
   	 printf("Aluno nao existe. Para inseri-lo, escolha a opcao correspondente no menu!"); return;
   }
   
   fflush(stdin);
   printf("Nome: "); fgets(a.nome,30,stdin);
   printf("Tipo (O=1, A=2, AB=3, B=4): "); scanf("%d", &a.tipo);
   printf("Fator (POSITIVO=1, NEGATIVO=2): "); scanf("%d", &a.fator);
   printf("Estado Civil (CASADO=1,SOLTEIRO=2): "); scanf("%d", &a.estado); fflush(stdin);
   printf("e-mail: "); fgets(a.email,30,stdin); fflush(stdin);
   printf("Curso: "); fgets(a.curso,30,stdin);
   printf("DtNasc:\n");
   printf("Dia: "); scanf("%d", &a.data.dia);
   printf("Mes: "); scanf("%d", &a.data.mes);
   printf("Ano: "); scanf("%d", &a.data.ano); fflush(stdin); 
   printf("Telefone: "); fgets(a.telefone,30,stdin);
   
   posiciona_aluno(fp, a.RA);
   if (fwrite(&a, sizeof(alunos), 1, fp))
      printf("Aluno alterado com sucesso!\n");
   fflush(fp);
}
void remover_historicoEaluno(int tempp,FILE *fp3) {
   historico h;
   int pos,cont=0;
   fseek(fp3, 0, SEEK_SET);

	  while (!feof(fp3)) {
	 
	  		pos=ftell(fp3);
			if(h.RA==tempp)
		   		{		   				
		   			    h.RA=0;
					    h.codigo=0;
					    h.freq=0;
					    h.media=0;
					    h.ano=0;
					    h.semestre=0;
						fseek(fp3, pos-32, SEEK_SET);
  					    fwrite(&h, sizeof(historico), 1, fp3);
      					printf("Historico excluido com sucesso!\n");
						fseek(fp3, pos, SEEK_SET);
						cont=1;
				   }
		   fread(&h, sizeof(historico), 1, fp3);    
	   }
	   if(cont==0)
	 	printf("Historico nao existe\n");    	   
}
void remover_aluno(FILE *fp, FILE *fp3) {
   alunos a;
   char op;
  
   do {
      printf("RA: ");
      scanf("%d", &a.RA);
   } while(a.RA < 1 || a.RA > 100);
   
   if (!verificaSeAlunoExiste(fp, a.RA)) {
   	 	printf("Aluno nao existe!"); return;
   }
   
   fflush(stdin);
   printf("Deseja remover o aluno (s/n)?: "); scanf("%c", &op);
   
   if (tolower(op) == 's') {
   	remover_historicoEaluno(a.RA,fp3);
   	  posiciona_aluno(fp, a.RA);
   	  	a.RA = -1;
	 	strcpy(a.curso, "");
		strcpy(a.email, "");
		strcpy(a.nome, "");
		strcpy(a.telefone, "");
	  
	  if (fwrite(&a, sizeof(alunos), 1, fp))
         printf("Aluno removido com sucesso!\n");
   }  
}
void consultar_aluno(FILE *fp) {
	alunos a;
	
	do {
      printf("RA: ");
      scanf("%d", &a.RA);
    } while(a.RA < 1 || a.RA > 100);
	
	if (!verificaSeAlunoExiste(fp, a.RA)) {
   	 	printf("Aluno nao existe!"); return;
    }
   	
   	posiciona_aluno(fp, a.RA);
	fread(&a, sizeof(alunos), 1, fp);
   	printf("RA: %d\n", a.RA);
   	printf("Nome: %s\n", a.nome);	  
   	switch(a.tipo)
	  		 {
	  		 	case O: {   printf("Tipo Sanguineo: O"); break;}
	  		 	case A: {	printf("Tipo Sanguineo: A"); break;}
	  		 	case AB:{	printf("Tipo Sanguineo: AB"); break;}
	  		 	case B: {   printf("Tipo Sanguineo: B"); break;}		 		
	  	 	 }
	  	  switch(a.fator)
		  	 {
		  	 	case POSITIVO: { printf("+\n"); break;}
		  	 	case NEGATIVO: { printf("-\n"); break;}
			 }
		  switch(a.estado)
		  	 {
		  	 	case CASADO: {	 printf("Estado Civil:Casado\n"); break; }
		  	 	case SOLTEIRO: { printf("Estado Civil:Solteiro\n"); break; }
			 }	  
   	printf("Email: %s\n", a.email);
   	printf("Curso: %s\n", a.curso);
   	printf("DtNasc: %02d/%02d/%02d\n", a.data.dia,a.data.mes,a.data.ano);
   	printf("Telefone: %s\n", a.telefone);	  	   	  
}
//**********DISCIPLINA***************//
void posiciona_disciplina(FILE *fp2, int id) {
	fseek(fp2, (id-1)*sizeof(disciplina), SEEK_SET);
}
void inicializa_disciplina(FILE *fp2) {
	disciplina d;
	
	d.codigo=-1;
	strcpy(d.nome, "");
	strcpy(d.sigla, "");
	d.carga=0;
	
	for (int i = 1; i <= MAX_REG; i++) {	
	   posiciona_disciplina(fp2, i);
	   fwrite(&d, sizeof(disciplina), 1, fp2);
    }
}
bool verificaSeDisciplinaExiste(FILE *fp2, int id) {
   disciplina d;
   posiciona_disciplina(fp2, id);
   
   fread(&d, sizeof(disciplina), 1, fp2);
   if  (d.codigo == -1)
      return false;
   return true;
}
void inserir_disciplina(FILE *fp2) {
   disciplina d;

   do {
      printf("Codigo: ");
      scanf("%d", &d.codigo);
   } while(d.codigo< 1 || d.codigo > 100);
   
   if (verificaSeDisciplinaExiste(fp2, d.codigo)) {
   	 printf("Disciplina ja inserida. Caso queira alterar, escolha a opcao correspondente!"); return;
   }
   
   fflush(stdin);
   printf("Nome: "); fgets(d.nome,30,stdin);
   printf("Carga Horaria: "); scanf("%d", &d.carga); fflush(stdin);
   printf("Sigla do Departamento: ");fgets(d.sigla,30,stdin);
   
   posiciona_disciplina(fp2, d.codigo);
   if (fwrite(&d, sizeof(disciplina), 1, fp2))
      printf("Disciplina cadastrada com sucesso!\n");
}
void alterar_disciplina(FILE *fp2) {
   disciplina d;
 
   do {
      printf("Codigo: ");
      scanf("%d", &d.codigo);
   } while(d.codigo< 1 || d.codigo > 100);
   
   if (!verificaSeDisciplinaExiste(fp2, d.codigo)) {
   	 printf("Disciplina nao existe. Para inseri-la, escolha a opcao correspondente no menu!"); return;
   }
   
   fflush(stdin);
   printf("Nome: "); fgets(d.nome,30,stdin);
   printf("Carga Horaria: "); scanf("%d", &d.carga); fflush(stdin);
   printf("Sigla do Departamento: "); fgets(d.sigla,30,stdin);
   
   posiciona_disciplina(fp2, d.codigo);
   if (fwrite(&d, sizeof(disciplina), 1, fp2))
      printf("Disciplina alterada com sucesso!\n");  
   fflush(fp2);
}
void remover_historicoEdisciplina(int tempp,FILE *fp3) {
   historico h;
   int pos,cont=0;
   fseek(fp3, 0, SEEK_SET);

	  while (!feof(fp3)) {

	  		pos=ftell(fp3);
			if(h.codigo==tempp)
		   		{		   				
					    h.RA=0;
					    h.codigo=0;
					    h.freq=0;
					    h.media=0;
					    h.ano=0;
					    h.semestre=0;
						fseek(fp3, pos-32, SEEK_SET);
  					    fwrite(&h, sizeof(historico), 1, fp3);
      					printf("Historico excluido com sucesso!\n");
						fseek(fp3, pos, SEEK_SET);
						cont=1;
				   }
		   fread(&h, sizeof(historico), 1, fp3);    
	   }
	   if(cont==0)
	 	printf("Historico nao existe\n");    	   
}
void remover_disciplina(FILE *fp2, FILE *fp3) {
   disciplina d;
   char op;
  
   do {
      printf("Codigo: ");
      scanf("%d", &d.codigo);
   } while(d.codigo < 1 || d.codigo > 100);
   
   if (!verificaSeDisciplinaExiste(fp2, d.codigo)) {
   	 printf("Disciplina nao existe!"); return;
   }
   
   fflush(stdin); printf("Deseja remover a disciplina(s/n)?: "); scanf("%c", &op);
   
   if (tolower(op) == 's') {
   		remover_historicoEdisciplina(d.codigo,fp3);
   	    posiciona_disciplina(fp2, d.codigo);
   	  	d.codigo = -1;
	 	strcpy(d.nome, "");
		strcpy(d.sigla, "");
		d.carga=0;
	  
	  if (fwrite(&d, sizeof(disciplina), 1, fp2))
         printf("Disciplina removida com sucesso!\n");
   }  
}
void consultar_disciplina(FILE *fp2) {
	disciplina d;
	
	do {
      printf("Codigo: ");
      scanf("%d", &d.codigo);
   	} while(d.codigo < 1 || d.codigo > 100);
   
   if (!verificaSeDisciplinaExiste(fp2, d.codigo)) {
   	 printf("Disciplina nao existe!"); return;
   	}
   	posiciona_disciplina(fp2,d.codigo);
	fread(&d, sizeof(disciplina), 1, fp2);
	   
	printf("Codigo: %d\n", d.codigo);
   	printf("Nome: %s\n",d.nome);
   	printf("Carga Horaria: %d\n", d.carga);	
   	printf("Sigla do Departamento: %s\n", d.sigla);
}
//*************HISTORICO*********//////////////////////////////
bool verificaSeAlunoExiste2(FILE *fp, int id) { 
	alunos a;
	posiciona_aluno(fp, id);
	fread(&a, sizeof(alunos), 1, fp);
   if  (a.RA  == -1)
      return false;
    printf ("Nome:%s\n",a.nome);
    printf  ("Curso:%s\n",a.curso);
   return true;
}
bool verificaSeDisciplinaExiste2(FILE *fp2, int id) {
	disciplina d;
	posiciona_disciplina(fp2, id);
	fread(&d, sizeof(disciplina), 1, fp2);
   if  (d.codigo  == -1)
      return false;
    printf("Codigo:%d\n",d.codigo);
	printf ("Nome:%s\n",d.nome);
    printf  ("Carga Horaria:%d\n",d.carga);
   return true;
}
void inserir_historico(FILE *fp3,FILE *fp,FILE *fp2) {
   historico h;
   char op;
   
    printf("Semestre: "); scanf("%d", &h.semestre);
    printf("Ano: "); scanf("%d", &h.ano);
    printf("RA: "); scanf("%d", &h.RA);
    
    if (!verificaSeAlunoExiste2(fp, h.RA)) {
   	 printf("Aluno nao existe. Para inseri-la, escolha a opcao correspondente no menu!"); return;
   } 
   do
   {
   	printf("Disciplina: ");
    scanf("%d", &h.codigo);
    
    if (!verificaSeDisciplinaExiste2(fp2, h.codigo)) {
   	 printf("Disciplina nao existe. Para inseri-la, escolha a opcao correspondente no menu!"); break;//att return
   } 
    printf ("Media Final:"); scanf("%lf", &h.media);
    printf ("Frequencia:"); scanf("%lf", &h.freq);
   
   	fseek(fp3,0,SEEK_END);
	if (fwrite(&h, sizeof(historico), 1, fp3))
      printf("Historico cadastrado com sucesso!\n");
      
	fflush(stdin); printf ("Continuar?");
    fflush(stdin); scanf ("%c",&op);
	}while (tolower(op)!='n');	
}
void alterar_historico(FILE *fp3) { 
   historico h;
 	int temp,temp1,pos;
   do { printf("RA: "); scanf("%d", &temp); } while(temp< 1 || temp > 100);
   do { printf("Cod: "); scanf("%d", &temp1);} while(temp1< 1 || temp1 > 100);
   fseek(fp3, 0, SEEK_SET);
	  while (!feof(fp3)) {
	  	
	  		pos=ftell(fp3);
			if(h.RA==temp)
		   		{	
		   			if(h.codigo==temp1)
		   			{		   				
		   				printf ("Media Final:"); scanf("%lf", &h.media);
					    printf ("Frequencia:"); scanf("%lf", &h.freq);
					    fseek(fp3, pos-32, SEEK_SET);
  					    fwrite(&h, sizeof(historico), 1, fp3);
      					printf("Historico alterado com sucesso!\n");
						break;
					}
				   }
		   fread(&h, sizeof(historico), 1, fp3);    
	   } 	 
}
void remover_historico(FILE *fp3) { 
   historico h;
   int temp,temp1,pos,cont=0;
   fseek(fp3, 0, SEEK_SET);
   do { printf("RA: "); scanf("%d", &temp);} while(temp< 1 || temp > 100);
   do { printf("Cod: "); scanf("%d", &temp1);} while(temp1< 1 || temp1 > 100);

	  while (!feof(fp3)) {
	  		pos=ftell(fp3);
			if(h.RA==temp)
		   		{
		   			if(h.codigo==temp1)
		   			{		   				
		   				h.RA=0;
					    h.codigo=0;
					    h.freq=0;
					    h.media=0;
					    h.ano=0;
					    h.semestre=0;
					    fseek(fp3, pos-32, SEEK_SET);
  					    fwrite(&h, sizeof(historico), 1, fp3);
      					printf("Historico excluido com sucesso!\n");
						cont=1;
						break;
					}
				   }
		   fread(&h, sizeof(historico), 1, fp3);    
	   }
	 if(cont==0)
	 	printf("Historico nao existe\n");    
}
void listar_historico(FILE *fp3) {
	historico h;
	int temp,temp1,temp2,cont=0;
	
	do { printf("RA: "); scanf("%d", &temp);} while(temp< 1 || temp > 100);
    printf("Semestre: "); scanf("%d", &temp1);
	printf("Ano: "); scanf("%d", &temp2);
	fseek(fp3, 0, SEEK_SET);
	fread(&h, sizeof(historico), 1, fp3); 
	while (!feof(fp3)) {
       if(temp==h.RA)
	   {if(temp1==h.semestre)
		{if(temp2==h.ano)
			{
				printf("Aluno: %d\n", h.RA);
				cont=1;
			   	printf("Disciplina: %d\n", h.codigo);
			   	printf("Nota: %.2lf\n", h.media);
			   	printf("Freq: %.2lf\n", h.freq);
			   	printf("Ano: %d\n", h.ano);
			   	printf("Semestre: %d\n", h.semestre);
			}
		}
	   }
	   fread(&h, sizeof(historico), 1, fp3);    
   }
   	if(cont==0)
	 	printf("Historico nao existe\n");    	
}
//**********RELATORIO1***************//
int verificaSeDisciplinaExiste5(FILE *fp2, int id) {
   disciplina d;
   posiciona_disciplina(fp2, id);
   
   fread(&d, sizeof(disciplina), 1, fp2);
   if  (d.codigo == -1)
      return 0;
   return d.carga;
}
void relatorio(FILE *fp, FILE *fp4)
{
	alunos a;
	int ano,mes,dia,maior=0,cont,vet[8],vet2[2];
	
	for(int i=0;i<8;i++)
			vet[i]=0;
	for(int i=0;i<2;i++)
			vet2[i]=0;	
			
	for (int i = 1; i <= MAX_REG; i++) {	
	   posiciona_aluno(fp, i);
	   fread(&a, sizeof(alunos), 1, fp);
	   if(i==1)
	   {
	   	ano=a.data.ano; mes=a.data.mes; dia=a.data.dia;
	   	maior=a.RA;
	   	cont=i;
	   }
	   if (a.RA != -1) {
	    if(a.data.ano<ano)
		{
			ano=a.data.ano; mes=a.data.mes; dia=a.data.dia;
	   		maior=a.RA; cont=i;
		}
		else if(a.data.ano==ano)
		{
		 	if(a.data.mes<mes)
		 	{
		 		mes=a.data.mes; dia=a.data.dia;
	   			maior=a.RA; cont=i;
			 }
			 else if(a.data.mes==mes)
			 {
			 	if(a.data.dia<dia)
		 		{
		   			dia=a.data.dia;
		   			maior=a.RA;	cont=i;
			 	}
			 }
		} 					   
   		switch(a.tipo)
	  		 {
	  		 	case O:{ switch(a.fator){
				  	 	case POSITIVO:{	vet[0]=vet[0]+1; break;	}
				  	 	case NEGATIVO:{	vet[1]=vet[1]+1; break;	}	
						}	break;
		               }
	  		 	case A:
	  		 		{   switch(a.fator){
				  	 	case POSITIVO:	{	vet[2]=vet[2]+1; break;	}
				  	 	case NEGATIVO:  {	vet[3]=vet[3]+1; break;	}
						}	break;
					}
	  		 	case AB:
	  		 		{	switch(a.fator){
				  	 	case POSITIVO:	{	vet[4]=vet[4]+1; break;	}
				  	 	case NEGATIVO:	{	vet[5]=vet[5]+1; break;	}
						}	break;
					}
	  		 	case B:
	  		 		{	switch(a.fator)
		  	 			{
				  	 	case POSITIVO:	{		vet[6]=vet[6]+1; break;	}
				  	 	case NEGATIVO:	{		vet[7]=vet[7]+1; break;	}
						}		break;
					}
	   }
	   switch(a.estado) {
	   	case CASADO:	{	vet2[0]=vet2[0]+1; break;	}
		case SOLTEIRO:	{	vet2[1]=vet2[1]+1; break;	}
		break; }
    }   
}
	fputs("-------------------------\n", fp4);
	fputs("Tipos Sanguineos\n", fp4);
	fprintf(fp4, "O+ tem %d alunos\nO- tem %d alunos\nA+ tem %d alunos\nA- tem %d alunos\nAB+ tem %d alunos\nAB- tem %d alunos\nB+ tem %d alunos\nB- tem %d alunos\n",vet[0],vet[1],vet[2],vet[3],vet[4],vet[5],vet[6],vet[7]);
	fputs("-------------------------\n", fp4);
	fputs("Estados Civis\n", fp4);
	fprintf(fp4,"Alunos Casados: %d\nAlunos Solteiros: %d\n",vet2[0],vet2[1]);
	fputs("-------------------------\n", fp4);
	fputs("Aluno Mais Velho\n", fp4);
		
	posiciona_aluno(fp, cont);
	fread(&a, sizeof(alunos), 1, fp);
	fprintf(fp4,"RA: %d\n", a.RA);
   	fprintf(fp4,"Nome: %s\n", a.nome);
   		  switch(a.tipo){
	  		 	case O:	{	fputs("Tipo Sanguineo: O",fp4);	break;	}
	  		 	case A:	{	fputs("Tipo Sanguineo: A",fp4);	break;	}
	  		 	case AB:{	fputs("Tipo Sanguineo: AB",fp4); break;	}
	  		 	case B:	{	fputs("Tipo Sanguineo: B",fp4); break;	} 		
	  	 	 }
	  	  switch(a.fator){
		  	 	case POSITIVO:	{	fputs("+\n",fp4); break;		}
		  	 	case NEGATIVO:	{	fputs("-\n",fp4); break;		}
			 }
		  switch(a.estado){
		  	 	case CASADO:	{	fputs("Estado Civil:Casado\n",fp4); break;	}
		  	 	case SOLTEIRO:	{	fputs("Estado Civil:Solteiro\n",fp4); break;}
			 }
   	fprintf(fp4,"Email: %s\n", a.email);
   	fprintf(fp4,"Curso: %s\n", a.curso);
   	fprintf(fp4,"DtNasc: %02d/%02d/%02d\n", a.data.dia,a.data.mes,a.data.ano);
   	fprintf(fp4,"Telefone: %s\n", a.telefone);   
   	fputs("-------------------------\n", fp4);
   	fflush(fp4);
}
void relatorio2(FILE *fp3, FILE *fp2, FILE *fp5)
{
	historico h;
	disciplina d;
	int temp,temp1,cont=0,contt=0;
	double media_geral=0;
	
	do {
      printf("RA para o RELATORIO 2: "); scanf("%d", &temp);
   } while(temp< 1 || temp > 100);
   
    fputs("-------------------------\n", fp5);    
	fseek(fp3, 0, SEEK_SET);
	fread(&h, sizeof(historico), 1, fp3); 
	while (!feof(fp3)) {
       if(temp==h.RA)
	   {
	   	if(cont==0)
	   	{
	   		fprintf(fp5,"RA: %d\n", h.RA);
			cont=1;
		}
		fprintf(fp5,"Ano: %d\n", h.ano);
		fprintf(fp5,"Semestre: %d\n", h.semestre);
		fprintf(fp5,"Cod Disciplina: %d\n", h.codigo);
		fprintf(fp5,"Nota: %.2lf\n", h.media);
	   	fprintf(fp5,"Freq: %.2lf\n", h.freq);	
	   
	  	if(h.media>=5 && h.freq >= 0.7*verificaSeDisciplinaExiste5(fp2, h.codigo))
	   		fputs("Aprovado!\n", fp5);
	   	else
	   		fputs("Reprovado!\n", fp5);
		media_geral=media_geral+h.media;
		contt++;		
	   }
	   fread(&h, sizeof(historico), 1, fp3);    
   }
   media_geral=media_geral/contt;
   fprintf(fp5,"Media Geral: %.2lf\n", media_geral); 
   fputs("-------------------------\n", fp5);
   fflush(fp5);
   printf("Encerrando...");
}
void relatorio3(FILE *fp3, FILE *fp2, FILE *fp6)
{
	historico h;
	disciplina d;
	int cont=0,contt=0,apr=0, porcentagem=0;
	double media_geral=0;

    fputs("-------------------------\n", fp6);    
	fseek(fp3, 0, SEEK_SET);
	fread(&h, sizeof(historico), 1, fp3); 
	
	for (int i = 1; i <= MAX_REG; i++) {	
	   posiciona_disciplina(fp2, i);
	   fread(&d, sizeof(disciplina), 1, fp2);
	   cont=0;
	   
	   if (d.codigo != -1) {
	   	fseek(fp3, 0, SEEK_SET);
	   	fread(&h, sizeof(historico), 1, fp3); 
   		  while (!feof(fp3)) {

		if(d.codigo==h.codigo)
		{
			cont=1;
			media_geral=media_geral+h.media;
		 if(h.media>=5 && h.freq >= 0.7*verificaSeDisciplinaExiste5(fp2, h.codigo))
	   		apr++;
	    contt++;
		}
			fread(&h, sizeof(historico), 1, fp3); 		    
    }
    }
	   if(cont==0 && d.codigo!=-1)
   	    fprintf(fp6,"%d sem matriculados\n",d.codigo);
		else if (cont==1 && d.codigo!=-1)
		{
			media_geral=media_geral/contt;
			fprintf(fp6,"Disciplina: %d\n",d.codigo);
			fprintf(fp6,"Media Geral: %.2lf\n",media_geral);
			media_geral=0;
			porcentagem=apr/contt;
			fprintf(fp6,"Aprovados: %d%%\n",porcentagem*100);
			apr=0;
			contt=0;
		}
    }	
}
//
int main(int argc, char *argv[]) {
	FILE *fp,*fp2,*fp3;
	int op;
	bool novo = false;
	//ALUNO
	if( access("alunos.dat", F_OK ) == 0 ) 
		fp = fopen("alunos.dat", "r+b");
	else {  fp = fopen("alunos.dat", "w+b"); novo = true;}
	if (fp == NULL) {
		printf("Nao foi possivel abrir o arquivo!"); getchar();	return 1;	}
	if (novo) { 	inicializa_aluno(fp);}
	novo=false;
	//DISCIPLINA
	if( access("disciplinas.dat", F_OK ) == 0 ) 
		fp2 = fopen("disciplinas.dat", "r+b");
	else {  	fp2 = fopen("disciplinas.dat", "w+b");	novo = true;}
	if (fp2 == NULL) {
		printf("Nao foi possivel abrir o arquivo!"); getchar();	return 1;}
	if (novo) {	inicializa_disciplina(fp2);	}
	//HISTORICO
	if( access("historico.dat", F_OK ) == 0 ) 
		fp3 = fopen("historico.dat", "r+b");
	else {  fp3 = fopen("historico.dat", "w+b"); novo = true;}
	if (fp3 == NULL) {
		printf("Nao foi possivel abrir o arquivo!"); getchar();	return 1;
	}
	//RELATORIOS
	FILE *fp4,*fp5,*fp6;
	if( access("relatorio1.txt", F_OK ) == 0 ) 
		fp4 = fopen("relatorio1.txt", "r+");
	else {  fp4 = fopen("relatorio1.txt", "w+");	novo = true;}
	if( access("relatorio2.txt", F_OK ) == 0 ) 
		fp5 = fopen("relatorio2.txt", "a+");
	else {  fp5 = fopen("relatorio2.txt", "a+");   novo = true;}
	if( access("relatorio3.txt", F_OK ) == 0 ) 
		fp6 = fopen("relatorio3.txt", "a+");
	else {  fp6 = fopen("relatorio3.txt", "a+");	novo = true;}
	//
	for (;;) {
	   op = menu();
	   switch(op) {
	      case 1: inserir_aluno(fp); break;
	      case 2: alterar_aluno(fp); break;
	      case 3: remover_aluno(fp,fp3); break;
	      case 4: consultar_aluno(fp); break;
	      case 5: inserir_disciplina(fp2); break;
	      case 6: alterar_disciplina(fp2); break;
	      case 7: remover_disciplina(fp2,fp3); break;
	      case 8: consultar_disciplina(fp2);; break;
	      case 9: inserir_historico(fp3,fp,fp2); break;
	      case 10: alterar_historico(fp3); break;
	      case 11: remover_historico(fp3); break;
	      case 12: listar_historico(fp3);; break;
	      case 13: relatorio(fp,fp4); relatorio2(fp3,fp2,fp5);relatorio3(fp3,fp2,fp6);
		  		   fclose(fp); fclose(fp2);	fclose(fp3); fclose(fp4); fclose(fp5); fclose(fp6);
				   return 0;  break;
	   }
	}	
	getchar();	return 0;
}
