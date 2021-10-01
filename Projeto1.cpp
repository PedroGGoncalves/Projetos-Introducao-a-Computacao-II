#include <stdio.h>
#include <stdlib.h>

void matriz_limiar(FILE *fp2,int temp) //a) Limiarização
{
	int num;
	if (temp>150)
      	num=255;
	else
		num=0;
	fprintf(fp2, "%d ", num);
}
void matriz_negativa(FILE *fp3,int temp) //b)Negativo
{
	int num;
	num=255-temp;
	fprintf(fp3, "%d ", num);
}
void histograma (FILE *fp4,int temp,int i,int j,int vet[], int cor,int l,int c) //c)Histograma
{
	int k;
		
	k=temp;
	vet[k]=vet[k]+1;
	
	if(i== l-1 && j==c-1)
	{
		for(k = 0; k <= cor; k++)
		{
		    fprintf(fp4, "%d:%d\n",k, vet[k]);
		}
	}
}

void matriz_carregar(FILE *fp,FILE *fp2,FILE *fp3,FILE *fp4) //Carregar Matriz
{
	
	int i,j,k,l=0,c=0,cor,temp;
	char tipo[2];
	fscanf(fp,"%c%c ", &tipo[0],&tipo[1]);
	fprintf(fp2, "%c%c\n", tipo[0],tipo[1]);
	fprintf(fp3, "%c%c\n", tipo[0],tipo[1]);

	fscanf(fp,"%d ", &l); //Linha
	fprintf(fp2, "%d ", l);
	fprintf(fp3, "%d ", l);

	fscanf(fp,"%d ", &c); //Coluna
	fprintf(fp2, "%d\n", c);
	fprintf(fp3, "%d ", c);

	fscanf(fp,"%d ", &cor); //Tons de Cinza
	fprintf(fp2, "%d\n", cor);
	fprintf(fp3, "%d\n", cor);
	int vet[cor];
	
		for(k = 0; k <=cor; k++)
	    	vet[k] = 0;
	
	for (i=0;i<l;i++)		//Operações
	{
		for (j=0;j<c;j++)
			{	
				fscanf(fp,"%d ", &temp);
				matriz_limiar(fp2,temp);
				matriz_negativa(fp3,temp);
				histograma(fp4,temp,i,j,vet,cor,l,c);
				
	        }
	        fprintf(fp2, "\n");
	        fprintf(fp3, "\n");    
	}	
	fclose(fp);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
}

void abrir_arquivo(FILE *fp, FILE *fp2,FILE *fp3,FILE *fp4) //Abrir Arquivos
{
	
	fp =fopen ("exemplo.pgm","r");
	if(fp  == NULL)
	{
		printf("Impossivel de abrir o arquivo ou Arquivo nao encontrado.\n");
		return ;
	}
	fp2 =fopen ("exemplo_limiar.pgm","w");
	fp3 =fopen ("exemplo_negativa.pgm","w");
	fp4 =fopen ("exemplo_histograma.txt","w");
	matriz_carregar(fp,fp2,fp3,fp4);
}

int main ()
{
	FILE *fp;
	FILE *fp2;
	FILE *fp3;
	FILE *fp4; 
	
	abrir_arquivo(fp,fp2,fp3,fp4);
	
	return 0;
}
