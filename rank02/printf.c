#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct s_print
{
	int spaces;
	int precision;
	int len;
	
} t_print;

int	ft_strlen(char *s)
{
	int l;

	l = 0;
	while(s[l] != '\0')
		l++;
	return(l);
}

char *atoi_base(int bas, unsigned int nb, int *l)
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
			*l += 1;
		}
		if (nb == 0)
		{
			digits = 1;
			*l += 1;
		}
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
			*l += 1;
		}
		if (nb == 0)
		{
			digits = 1;
			*l += 1;
		}
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

int put_nb(int nb, int *l, int spaces, int precision)
{
	char *s;
	int total = 0;
	int total2 = 0;
	int n = 0;
	int len = 0;
	
	if (nb < 0)
	{
		nb *= -1;
		n = '-';
		*l += 1;
	}
	s = atoi_base(10, nb, l);
	len += ft_strlen(s);
	if (precision > len)
	{
		if (n == '-')
		{
			total = precision - len;
			if (spaces > (total + len))
				total2 = spaces - (total + len) - 1;
		}
		else
		{
			total = precision - len;
			if (spaces > (total + len))
				total2 = spaces - (total + len);
		}
	}
	else
		total2 = spaces - len;
	while (total2 > 0)
	{
		write (1, " ", 1);
		*l += 1;
		total2--;
	} 
	if (n == '-')
		write(1, "-", 1);
	while (total > 0)
	{
		write (1, "0", 1);
		*l += 1;
		total--;
	}
	write(1, s, ft_strlen(s));
	free(s);
	return (0);
}

int put_hex(unsigned int nb, int *l, int spaces, int precision)
{
	char *s;
	int total = 0;
	int total2 = 0;
	
	s = atoi_base(16, nb, l);
	int len = ft_strlen(s);
	if (precision > len)
	{
		total = precision - len;
		if (spaces > (total + len))
			total2 = spaces - (total + len);
	}
	else
		total2 = spaces - len;
	while (total2 > 0)
	{
		write (1, " ", 1);
		*l += 1;
		total2--;
	} 
	while (total > 0)
	{
		write (1, "0", 1);
		*l += 1;
		total--;
	} 
	write(1, s, ft_strlen(s));
	free(s);
	return (0);
}

int	ft_printf(char *s, ...)
{
	va_list args;
	char *s1;
	int nb;
	t_print p;
	int l = 0;
	
	p.len = 0;
	p.spaces = 0;
	p.precision = 0;
	va_start(args, s);
	while(s[l] != '\0')
	{
		if (s[l] != '%')
		{
			write(1, &s[l], 1);
			p.len++;
			l++;
		}
		else
		{
			l++;
			while(s[l] >= '0' && s[l] <= '9')
			{
				p.spaces = p.spaces * 10 + (s[l] - 48);
				l++;
			}
			if (s[l] == '.')
			{
				l++;
				while(s[l] >= '0' && s[l] <= '9')
				{
					p.precision = p.precision * 10 + (s[l] - 48);
					l++;
				}
			}
			if (s[l] == 'd')
			{
				l++;
				put_nb(va_arg(args, int), &p.len, p.spaces, p.precision);
			}
			else if (s[l] == 'x')
			{
				l++;
				put_hex(va_arg(args, unsigned int), &p.len, p.spaces, p.precision);
			}
			else if (s[l] == 's')
			{
				l++;
				//put_nb(va_arg(args, int), &p.len);
			}
			p.spaces = 0;
			p.precision = 0;
		}
	}
	va_end(args);
	return(p.len);
}

int main (void)
{
	int nb;
	int m;
	int o;

	nb = -4231334;
	m = ft_printf("DEC_ORI: %25.16d HEX_MIO: %25.16x\n", nb, nb);
	o = printf("DEC_ORI: %25.16d HEX_ORI: %25.16x\n", nb, nb);
//	m = ft_printf("%5.2d\n", nb);
//	o = printf("%5.2d\n", nb);
	printf("MIO: %d ORI: %d\n", m, o);
	return (0);
}
