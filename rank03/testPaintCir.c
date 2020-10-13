#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_background{
	int f;
	int c;
	int **zone;
	char ch;
} t_background;

typedef struct cir{
	float x;
	float y;
	char c;
	float radius;
	char type;
} 	t_cir;

int generateBackground(int x, int y, char c, t_background *b){

	b->zone = (int **)malloc(x*sizeof(int*));
	for(int n = 0; n < y; n++)
		b->zone[n] = (int*)malloc(y*sizeof(int));
	for(int i = 0; i < y; i++)
		for(int j = 0; j < x; j++)
			b->zone[i][j] = c;
	return 0;
}

int in_circle(float x, float y, t_cir c){
	float distance;

	distance = sqrtf(powf(x - c.x, 2) + powf(y - c.y, 2));
	if(distance <= c.radius){
		if((c.radius - distance) < 1.00000000)
			return 2;
		return 1;
	}
	return 0;
}

int paint(char type, float x, float y, float radius, char c, t_background *b,
				t_cir cir){

	int check = 0;
	for(int i = y; i < b->f; i++)
  		for(int j = x; j < b->c; j++){
  			check = in_circle((float)j, (float)i, cir);
  			if((check == 2 && type == 'c') || (type == 'C' && check))
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
	t_cir *c = (t_cir *)malloc(sizeof(t_cir));
	int ret;
	FILE *f;
	f = fopen("2", "r");

	ret = fscanf(f, "%d %d %c\n", &b->c, &b->f, &b->ch);
	generateBackground(b->c,b->f,b->ch, b);
	while ((ret = fscanf(f, "%c %f %f %f %c\n", &c->type, &c->x, 
						&c->y, &c->radius, &c->c))== 5){
		paint(c->type, c->x, c->y, c->radius, c->c, b, *c);
	}
	print(b->c,b->f, *b);
	free(b);
	fclose(f);
	return 0;
}
