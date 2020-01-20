#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int ft_puthexa(unsigned int n)
{
	unsigned int a;
	int l;
	char *hexam;
	a = n;
	l = 0;
	while (a != 0)
	{
		a = a / 16;
		l++;
	}
	hexam = malloc(sizeof(char) * l + 1);
	hexam[l--] = '\0';
	while (n != 0)
	{
		a = n % 16;
		if (a < 10)
			hexam[l--] = a += '0';
		else
			hexam[l--] = a += 'W';
		n = n / 16;
	}
	l = 0;
	while (hexam[l] != '\0')
	{
		write(1, &hexam[l], 1);
		l++;
	}
	free(hexam);
	hexam= NULL;
}

int ft_putnbr(int n)
{
	int a;

	a = n;
	if (n < 0)
	{
		n *= -1;
		write(1, "-", 1);
	}
	while (a >= 10)
	{
		a = n / 10 + 48;
		write(1, &a, 1);
		a = a % 10;
	}
	a = a + 48;
	write(1, &a, 1);
}

int ft_printf(const char *s, ...)
{
	int x;
	int d;
	int len;
	va_list args;

	va_start(args, s);
	while(s[len] != '\0')
	{
		if (s[len] != '%')
		{
			write(1, &s[len], 1);
			len++;
		}
		else
		{
			len++;
			if(s[len] == 'x')
			{
				len++;
				x = va_arg(args, unsigned int);
				ft_puthexa(x);
			}
			else if (s[len] == 'd')
			{
				len++;
				d = va_arg(args, int);
				ft_putnbr(d);
			}
		}
	}
	va_end(args);
}
int main ()
{
	int x;

	x = 42;

	ft_printf("HEXA: %x, DEC: %d\n", 42, 42);
	printf("HEXA: %x, DEC: %d\n", 42, 42);
}