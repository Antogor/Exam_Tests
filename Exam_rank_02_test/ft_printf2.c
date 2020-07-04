#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int ft_strlen (char *s)
{
	int l = 0;
	while(s[l] != '\0')
		l++;
	return(l);
}

void ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

int ft_putstr_master(char *s, int spaces, int precision)
{
	int len = 0;
	int total;
	int total2;
	int l = 0;
	int q = 0;

	len += ft_strlen(s);
	if (precision > len)
	{
		precision = 0;
	}
	total = precision;
	if (total > 0)
	{
		if (spaces > total)
			total2 = spaces - total;
	}
	else if (spaces > len)
		total2 = spaces - len;
	while(total2 > 0)
	{
		write(1, " ", 1);
		l++;
		total2--;
	}
	if(total > 0)
	{
		while (total > 0)
		{
			write(1, &s[q], 1);
			l++;
			total--;
			q++;
		}
	}
	else
	{
		l += len;
		ft_putstr(s);
	}
	return(l);
}

void ft_putnbr(int d)
{
	int a;

	a = d;
	while (d > 10)
	{
		a = d / 10 + 48;
		write(1, &a, 1);
		d = d / 10;
	}
	a = d / 10 + 48;
	write(1, &a, 1);
}

int ft_putnbr_master(int d, int spaces, int precision)
{
	int cifras = 0;
	int total;
	int total2;
	int l = 0;
	int a;
	int neg = 0;
	if (d < 0)
	{
		d *= -1;
		neg = '-';
		l++;
	}
	a = d;
	while (a != 0)
	{
		a = a / 10;
		cifras++;
	}
	l += cifras;
	if (precision > cifras)
	{
		total = precision - cifras;
		
		if (spaces > (total + cifras))
			total2 = spaces - (total + cifras);
			if (neg == '-')
				total2 -= 1;
	}
	else
	{
		if(spaces > cifras)
			total2 = spaces - cifras;
	}
	while(total2 > 0)
	{
		write(1, " ", 1);
		l++;
		total2--;
	}
	if (neg == '-')
		write(1, "-", 1);
	while(total > 0)
	{
		write(1, "0", 1);
		l++;
		total--;
	}
	ft_putnbr(d);
	return(l);
}

char *ft_puthexa(unsigned int x)
{
	unsigned int a;
	int l = 0;
	char *hexa;

	a = x;
	while (a != 0)
	{
		a = a / 16;
		l++;
	}
	hexa = malloc(sizeof(char) * l);
	hexa[l--] = '\0';
	while(x != 0)
	{
		a = x % 16;
		if (a < 10)
			hexa[l--] = a + 48;
		else
			hexa[l--] = a + 'W';
		x = x / 16;
	}
	return(hexa);
}

int ft_puthexa_master(unsigned int x, int spaces, int precision)
{
	int len = 0;
	int total;
	int total2;
	int l = 0;
	char *hexa;

	hexa = ft_puthexa(x);
	len += ft_strlen(hexa);
	l += len;
	if (precision > len)
	{
		total = precision - len;
		if (spaces > total + len)
			total2 = spaces - (total + len);
	}
	else
	{
		if (spaces > len)
			total2 = spaces - len;
	}
	while(total2 > 0)
	{
		write(1, " ", 1);
		l++;
		total2--;
	}
	while(total > 0)
	{
		write(1, "0", 1);
		l++;
		total--;
	}
	ft_putstr(hexa);
	free(hexa);
	hexa = NULL;
	return(l);
}

int ft_printf(const char *s, ...)
{
	int d = 0;
	unsigned int x = 0;
	char *str;
	int br= 0;
	int spaces = 0;
	int precision = 0;
	va_list args;
	int len = 0;

	va_start(args, s);
	while(s[len] != '\0')
	{
		if (s[len] != '%')
		{
			write(1, &s[len], 1);
			br++;
			len++;
		}
		else
		{
			len++;
			if	(s[len] >= '0' && s[len] <= '9')
			{
				while (s[len] >= '0' && s[len] <= '9')
				{
					spaces = spaces * 10 + (s[len] - 48);
					len++;
				}
			}
			if (s[len] == '.')
			{
				len++;
				if	(s[len] >= '0' && s[len] <= '9')
				{
					while (s[len] >= '0' && s[len] <= '9')
					{
						precision = precision * 10 + (s[len] - 48);
						len++;
					}
				}	
			}
			if (s[len] == 'd')
			{
				len++;
				d = va_arg(args, int);
				br += ft_putnbr_master(d, spaces, precision);
			}
			else if (s[len] == 'x')
			{
				len++;
				x = va_arg(args, unsigned int);
				br += ft_puthexa_master(x, spaces, precision);
			}
			else if(s[len] == 's')
			{
				len++;
				str = va_arg(args, char *);
				br += ft_putstr_master(str, spaces, precision);
			}
		}
		spaces = 0;
		precision = 0;
	}
	va_end(args);
	return(br);
}

int main()
{
	int l;
	int q;
	l = ft_printf("%20.15s\n", "hola");
	q = printf("%20.15s\n", "hola");
	printf("MIO: %d ORIGINAL: %d\n", l, q);
}

