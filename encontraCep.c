#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco{

	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];

};

int main(int argc, char**argv){
  
	FILE *f;
	Endereco e;
    long MAX;
	int c, encontrado;
    long pos, meio, inicio, final;
  
	if(argc != 2){
    
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
    
	}
  
    inicio = 0;
    encontrado = 0;
	c = 0;
  
	printf("Numero de Bits sendo ocupados: %ld\n\n", sizeof(Endereco));

	f = fopen("cep.dat","rb");

    fseek(f,0,SEEK_END);
    pos = ftell(f);
	MAX = pos/sizeof(Endereco);
    final = MAX - 1;
  
	while(inicio <= final && encontrado <= 0){
    
	    c++;
    
        meio = (inicio + final)/2;
        fseek(f, meio * sizeof(Endereco), SEEK_SET);
        MAX = fread(&e, sizeof(Endereco), 1, f);
    
		    if(strncmp(argv[1],e.cep,8)==0){
                printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
      
			    encontrado++;
      
		}else if(strcmp(argv[1],e.cep) < 0){
      
      final = meio - 1;
      
    }else{

        inicio = meio + 1;
      
    }
    
	    MAX = fread(&e,sizeof(Endereco),1,f);
    
	}if(encontrado<0){
    
    printf("O CEP %s não foi encontrado",argv[1]);
    
    }
  
	printf("Total Lido: %d\n", c);
	fclose(f);
  
    return 0;
}