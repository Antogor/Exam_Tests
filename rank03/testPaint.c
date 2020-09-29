#include <stdlib.h>
#include <unistd.h>

typedef struct s_background{
	int f;
	int c;
	int **zone;
} t_background;

int generateBackground(int x, int y, char c, t_background *b){

	b->zone = (int **)malloc(x*sizeof(int*));
	for(int n = 0; n < y; n++)
		b->zone[n] = (int*)malloc(y*sizeof(int));
	for(int i = 0; i < x; i++)
		for(int j = 0; j < y; j++)
			b->zone[i][j] = c;
	return 0;
}

int paint(char type, int x, int y, int w, int h, char c, t_background *b){

	if(type == 'R'){
		for(int i = x; i < x+w && i < b->f; i++)
			for(int j = y; j < y+h && j < b->c; j++)
				b->zone[i][j] = c;
	}
	else if(type == 'r'){

	}
	else
		return 1;
	return 0;
}

int print(int x, int y, t_background b){
	
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++)
			write(1, &b.zone[i][j], 1);
		write(1, "\n", 1);
	}
	
	return 0;
}

int main(void)
{
	t_background *b = (t_background *)malloc(sizeof(t_background));
	b->f = 50;
	b->c = 50;
	generateBackground(b->f,b->c,'.', b);
	paint('R', 15, 15, 5, 5, '1', b);
	paint('R', 35, 35, 8, 8, '#', b);
	paint('R', 8, 8, 1, 1, 'T', b);
	print(b->f,b->c, *b);
	free(b);
	return 0;
}
