#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

typedef struct s_background{
	int f;
	int c;
	int **zone;
	char ch;
} t_background;

typedef struct ret{
	float x;
	float y;
	char c;
	float w;
	float h;
	char type;
	struct ret *next;
} t_ret;

int generateBackground(int x, int y, char c, t_background *b){

	b->zone = (int **)malloc(x*sizeof(int*));
	for(int n = 0; n < y; n++)
		b->zone[n] = (int*)malloc(y*sizeof(int));
	for(int i = 0; i < y; i++)
		for(int j = 0; j < x; j++)
			b->zone[i][j] = c;
	return 0;
}

int in_rectangle(float x, float y, t_ret t){
	if(((x < t.x || (t.x + t.w < x))
		|| (y < t.y)) || (t.y + t.h < y))
		return 0;
	if(((x - t.x < 1.00000000) || ((t.x + t.w) - x < 1.00000000)) ||
		((y - t.y < 1.00000000 || ((t.y + t.h) - y < 1.00000000))))
			return 2;
	return 1;
}

int paint(char type, float x, float y, float w, float h, char c, t_background *b,
				t_ret t){

	int check = 0;
	for(int i = y; i < b->f; i++)
  		for(int j = x; j < b->c; j++){
  			check = in_rectangle(j, i, t);
  			if((check == 2 && type == 'r') || (type == 'R' && check))
  				b->zone[i][j] = c;
		}
	return 0;
}

int print(int x, int y, t_background b){
	
	for(int i = 0; i < y; i++){
		for(int j = 0; j < x; j++)
			write(1, &b.zone[i][j], 1);
		write(1, "\n", 1);
	}
	
	return 0;
}


int main(void)
{
	t_background *b = (t_background *)malloc(sizeof(t_background));
	t_ret *t = (t_ret *)malloc(sizeof(t_ret));
	int ret;
	FILE *f;
	f = fopen("1", "r");

	ret = fscanf(f, "%d %d %c\n", &b->c, &b->f, &b->ch);
	generateBackground(b->c,b->f,b->ch, b);
	while ((ret = fscanf(f, "%c %f %f %f %f %c\n", &t->type, &t->x, 
						&t->y, &t->w, &t->h, &t->c))== 6){
		paint(t->type, t->x, t->y, t->w, t->h, t->c, b, *t);
	}
	print(b->c,b->f, *b);
	free(b);
	fclose(f);
	return 0;
}
