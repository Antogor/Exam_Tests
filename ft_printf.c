#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_strlen(char *s)
{
	int l;
	l = 0;
	while (s[l] != '\0')
		l++;
	return(l);
}

void ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

int ft_putstr_master(char *s, int spaces, int precision)
{
	int total = 0;
	int total2 = 0;
	int l = 0;
	int q = 0;
	int len;

	len = ft_strlen(s);
	if (precision > len)
		precision = 0;
	total = precision;
	if (precision > 0)
	{
		if (spaces > precision)
			total2 = spaces - precision;
	}
	else
	{
		if (spaces > len)
			total2 = spaces - len;
	}
	while (total2 > 0)
	{
		write(1, " ", 1);
		l++;
		total2--;
	}
	if (total > 0)
	{
		while (total > 0)
		{

			write(1, &s[q], 1);
			l++;
			q++;
			total--;
		}
	}
	else
	{
		ft_putstr(s);
		l += len;
	}
	return(l);
}

void ft_putnbr(int n)
{
	int a;

	while (n > 10)
	{
		a = n / 10 + 48;
		write(1, &a, 1);
		n = n / 10;
	}
	a = n / 10 + 48;
	write(1, &a, 1);
}

int ft_putnbr_master(int d, int spaces, int precision)
{
	int total = 0;
	int total2 = 0;
	int neg = 0;
	int cifras = 0;
	int a;
	int count = 0;
	int l = 0;
	
	if (d < 0)
	{
		neg = '-';
		d *= -1;
		count++;
		l++;
	}
	a = d;
	while(a != 0)
	{
		a = a / 10;
		count++;
		l++;
	}
	if (precision > count)
	{
		total = precision - count;
	}
	if (total > 0)
	{
		if (spaces > count + total)
			total2 = spaces - (count + total);
	}
	else
	{
		if (spaces > count)
			total2 = spaces - count;
	}
	while (total2 > 0)
	{
		write(1, " ", 1);
		l++;
		total2--;
	}
	if (neg == '-')
		write(1, "-", 1);
	if (neg == '-' && total > 0)
	{
		write(1, "0", 1);
		l++;
	}
	while (total > 0)
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
	char *hexa;
	int count;
	unsigned int a;
	a = x;
	count = 0;
	while (a != 0)
	{
		a = a / 16;
		count++;
	}
	hexa = malloc(sizeof(char) * count);
	hexa[count--] = '\0';
	while(x != 0)
	{
		a = x % 16;
		if (a < 10)
			hexa[count--] = a + '0';
		else
			hexa[count--] = a + 'W';
		x = x / 16;
	}
	return(hexa);
}

int ft_puthexa_master(unsigned int x, int spaces, int precision)
{
	int total = 0;
	int total2 = 0;
	int l = 0;
	char *hexa;

	hexa = ft_puthexa(x);
	l = ft_strlen(hexa);
	if (precision > l)
	{
		total = precision - l;
	}
	if (total > 0)
	{
		if (spaces > l + total)
			total2 = spaces - (l + total);
	}
	else
	{
		if (spaces > l)
			total2 = spaces - l;
	}
	while (total2 > 0)
	{
		write(1, " ", 1);
		l++;
		total2--;
	}
	while (total > 0)
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
	int spaces = 0;
	int precision = 0;
	va_list args;
	int len = 0;
	int br = 0;
	
	va_start(args, s);
	while(s[len] != '\0')
	{
		if (s[len] != '%')
		{
			write(1, &s[len], 1);
			len++;
			br++;
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
			else if (s[len] == 's')
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

int main ()
{
	int l;
	int q;

	l = ft_printf("%.d\n", 20);
	q = printf("%.d\n", 20);
	printf("MIO: %d ORIGINAL: %d\n", l, q);
}
