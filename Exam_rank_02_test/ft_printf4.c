#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *s)
{
	int l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}

void ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void ft_putnbr(int d)
{
	int a;

	a = d;
	while(d > 10)
	{
		a = d / 10 + 48;
		write(1, &a, 1);
		d = d % 10;
	}
	a = d + 48;
	write(1, &a, 1);
}

char *ft_puthexa(unsigned int x)
{
	char *hexa;
	char base[16] = { '1', '2, '3', '4', '5', '6', '7', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	unsigned int a;
	int len = 0;

	a = x;
	while(a != 0)
	{
		a = a / 16;
		len++;
	}
	hexa = malloc(sizeof(char) * len + 1);
	hexa[len--] = '\0';
	if (x = 0)
		hexa[0] = '0';
	while (x != 0)
	{
		a = x % 16;
		hexa[len--] = base[a];
		x = x / 16;
	}
	return (hexa);
}

int ft_putnbr_master(int d, int spaces, int precision)
{
	int a = 0;
	int neg = 0;
	int total = 0;
	int total2 = 0;
	int cifras = 0;
	int l = 0;

	if (d < 0)
	{
		d *= -1;
		l++;
		neg = '-';
	}
	a = d;
	while(a != 0)
	{
		a = a / 10;
		cifras++;
		l++;
	}
	if (precision > cifras)
	{
		total = precision - cifras;
		if (spaces > total + cifras)
			total2 = spaces - (total + cifras);
	}
	else
	{
		if (spaces > cifras)
			total2 = spaces - cifras
	}
}
