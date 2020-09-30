#include <stdlib.h>
#include <unistd.h>

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
	for(int i = 0; i < x; i++)
		for(int j = 0; j < y; j++)
			b->zone[i][j] = c;
	return 0;
}

int in_rectangle(float x, float y, t_ret t){
	if(((x < t.x || (t.x + t.w < x))
		|| (y < t.y)) || (t.y + t.h < y))
		return 0;
	if(((x - t.x < 1.00000000) || ((t.x + t.w) - x < 1.00000000)) ||
		((x - t.y < 1.00000000 || ((t.y + t.h) - x < 1.00000000))))
			return 2;
	return 1;
}

int paint(char type, float x, float y, float w, float h, char c, t_background *b,
				t_ret t){

	int check = 0;
	if(type == 'R'){
		for(int i = y; i < (int)(y+h) && i < b->f; i++)
			for(int j = x; j < (int)(x+w) && j < b->c; j++){
				check = in_rectangle(j, i, t);
				if(check)
					b->zone[i][j] = c;
			}
	}
	else if(type == 'r'){
		for(int i = x; i < x+w && i < b->f; i++)
			for(int j = y; j < y+h && j < b->c; j++){
				check = in_rectangle(i,j, t);
					if (check){
						if(i == x || j == y || i ==(int)(x+w) -1 || j == (int)(x+w) -1)
							b->zone[i][j] = c;
						else
							b->zone[i][j] = b->ch;
					}
			}
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
	t_ret *t = (t_ret *)malloc(sizeof(t_ret));
	b->f = 50;
	b->c = 50;
	b->ch = '.';

	t->type = 'R';
	t->x = 15.604567;
	t->y = 16.363456;
	t->w = 4.545632;
	t->h = 4.734567;

	t->next = (t_ret *)malloc(sizeof(t_ret));
	t->next->type = 'R';
	t->next->x = 15.435678;
	t->next->y = 4.564267;
	t->next->w = 8;
	t->next->h = 4.546782;
	generateBackground(b->f,b->c,b->ch, b);
	paint(t->type, t->x, t->y, t->w, t->h, '#', b, *t);
	paint(t->next->type, t->next->x, t->next->y, t->next->w, t->next->h, '1', b, *t->next);
	print(b->f,b->c, *b);
	free(b);
	return 0;
}
