#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_print
{
	int spaces;
	int precision;
	int len;
	
} t_print;


char *atoi_base(int bas, unsigned int nb)
{
	char *s;
	unsigned int tmp;
	int digits;
	char hexa[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	char dec[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	digits = 0;
	if (bas == 10)
	{
		tmp = nb;
		while(tmp != 0)
		{
			tmp = tmp / 10;
			digits++;
		}
		if (nb == 0)
			digits = 1;
		s = (char *)malloc(sizeof(char) * digits + 1);
		s[digits--] = '\0';
		if (nb == 0)
			s[digits] = dec[0];
		while(nb != 0)
		{
			tmp = nb % 10;
			s[digits--] = dec[tmp];
			nb = nb / 10;
		}
	}
	if (bas == 16)
	{
		tmp = nb;
		while (tmp != 0)
		{
			tmp = tmp / 16;
			digits++;
		}
		if (nb == 0)
			digits = 1;
		s = (char *)malloc(sizeof(char) * digits + 1);
		s[digits--] = '\0';
		if (nb == 0)
			s[digits] = hexa[0];
		while(nb != 0)
		{
			tmp = nb % 16;
			s[digits--] = hexa[tmp];
			nb = nb / 16;
		}
	}
	return (s);
}

int put_nb(int nb)
{
	char *s;

	if (nb < 0)
	{
		nb *= -1;
		write(1, "-", 1);
	}
	s = atoi_base(10, nb);
	write(1, s, strlen(s));
	free(s);
	return (0);
}

int put_hex(unsigned int nb)
{
	char *s;

	s = atoi_base(16, nb);
	write(1, s, strlen(s));
	free(s);
	return (0);
}

int main (void)
{
	char *s1;
	int nb;

	nb = 423442;
	put_nb(nb);
	printf("\n");
	put_hex(nb);
	printf("\n");
	printf("DEC_ORI: %d\n", nb);
	printf("HEXA_ORI: %x\n", nb);
	return (0);
}
