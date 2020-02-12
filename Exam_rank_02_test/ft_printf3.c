#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>


int ft_strlen(char *s)
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

void ft_putnbr(int d)
{
	int a = 0;

	while(d > 10)
	{
		a = d / 10 + 48;
		write (1, &a, 1);
		d = d / 10;
	}
	a = d / 10 + 48;
	write(1, &a, 1);
}

char *ft_puthexa(unsigned int x)
{
	int a = 0;
	char *hexa;
	int l = 0;
	a = x;
	while (a != 0)
	{
		a = x / 16;
	}
	l = a;
	hexa = malloc(sizeof(char) * l);
	hexa[l--] = '\0';
	while (x != 0)
	{
		a = x;
		if (x > 10)
			hexa[l--] = a % 16 + 'W';
		else
			hexa[l--] = a % 16 + 48;
		x = x / 16;
	}
	return(hexa);
}

int ft_putnbr_master(int d, int spaces, int precision)
{
	int cifras = 0;
	int total = 0;
	int total2 = 0;
	int a = 0;
	int l = 0;
	int neg = 0;
	if (d < 0)
	{
		neg = '-';
		l++;
		d *= -1;
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
		total = precision -  cifras;
		if (spaces < total + cifras)
			total2 = spaces - (total + cifras);
	}
	else
		total2 = spaces - cifras;
	while (total2 > 0)
	{
		write (1, " ", 1);
		l++;
		total2--;
	}
	if (neg == '-')
		write(1, "-", 1);
	while (total > 0)
	{
		write(1, "0", 1);
		l++;
		total--;
	}
	ft_putnbr(d);
	return(l);
}

int ft_putnbr_hexa(unsigned int x, int spaces, int precision)
{
	int total = 0;
	int total2 = 0;
	int a = 0;
	int l = 0;
	int len = 0;
	char *hexa;
	hexa = ft_puthexa(x);
	len = ft_strlen(hexa);
	l += len;
	if (precision > len)
	{
		total = precision -  len;
		if (spaces < total + len)
			total2 = spaces - (total + len);
	}
	else
		total2 = spaces - len;
	while (total2 > 0)
	{
		write (1, " ", 1);
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
	return(l);
}

int ft_putstr_master(char *s, int spaces, int precision)
{
	int total = 0;
	int total2 = 0;
	int l = 0;
	int len = 0;
	char *hexa;
	len = ft_strlen(s);
	if (precision > len)
		precision = 0;
	total = precision;
	if (total > 0)
	{
		if (spaces < total)
			total2 = spaces - total;
	}
	else
		total2 = spaces - len;
	while (total2 > 0)
	{
		write (1, " ", 1);
		l++;
		total2--;
	}
	if  (total > 0)
	{
		write(1, s, total);
		l++;
	}
	else
	{
		ft_putstr(s);
		l += len;
	}
	return(l);
}

int ft_printf(const char *s, ...)
{
	va_list args;
	int d = 0;
	unsigned int x = 0;
	char *str;
	int br = 0;
	int l = 0;
	int spaces = 0;
	int precision = 0;

	va_start(args, s);
	while(s[l] != '\0')
	{
		if (s[l] != '%')
		{
			write(1, &s[l], 1);
			br++;
			l++;
		}
		else
		{
			l++;
			while(s[l] >= '0' && s[l] <= '9')
			{
				spaces = spaces * 10 + (s[l] - 48);
				l++;
			}
			if (s[l] == '.')
				l++;
			while(s[l] >= '0' && s[l] <= '9')
			{
				precision = precision * 10 + (s[l] - 48);
				l++;
			}
			if (s[l] == 'd')
			{
				l++;
				d = va_arg(args, int);
				br += ft_putnbr_master(d, spaces, precision);
			}
			else if (s[l] == 'x')
			{
				l++;
				x = va_arg(args, unsigned int);
				br += ft_putnbr_hexa(x, spaces, precision);
			}
			else if (s[l] == 's')
			{
				l++;
				str = va_arg(args, char *);
				br += ft_putstr_master(str, spaces, precision);
			}
			spaces = 0;
			precision = 0;
		}

	}
	va_end(args);
	return(br);
}

int main()
{
	int l;
	l = ft_printf("%.50d", -20);
	return (0);
}
