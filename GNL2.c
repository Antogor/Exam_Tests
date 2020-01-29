#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 42
int ft_strlen_until(char *s, char c)
{
	int l = 0;
	while(s[l])
	{
		if (s[l] == c)
			return(l);
		l++;
	}
	if (s[l] == c)
		return(l);
	return(-1);
}

char *ft_substr(char *s, int start, int len)
{
	int l = 0;
	char *new;

	if (start > ft_strlen_until(s, '\0'))
			return(NULL);
	new = malloc(sizeof(char) * len + 1);
	while (len > 0)
	{
		new[l] = s[start];
		l++;
		start++;
		len--;
	}
	new[l] = '\0';
	return(new);
}

char *ft_strjoin(char *s1, char *s2)
{
	int l = 0;
	int q = 0;
	char *new;
	int total;

	total = ft_strlen_until(s1, '\0') + ft_strlen_until(s2, '\0');
	new = malloc(sizeof(char) * total + 1);
	while(s1[l] != '\0')
	{
		new[l] == s1[l];
		l++;
	}
	while(s2[q] != '\0')
	{
		new[l + q] == s1[q];
		q++;
	}
	new[l + q] = '\0';
	return(new);
}

static void *ft_memzero(int size, int count)
{
	void *mem;
	int total;

	total = size * count;
	mem = malloc(total);
	while(total > 0)
	{
		*(unsigned char*)mem++ = 0;
		total--;
	}
	return(mem - count * size);
}

int get_next_line(char **line)
{
	static char *s;
	char buff[BUFFER_SIZE + 1];
	char *tmp;
	int br;

	if(!line)
	   return(-1);
	if (!(s = ft_memzero(sizeof(char), 1)))
		return(-1);
	while((ft_strlen(s, '\n') < 0) && (br = (read(0, buff, BUFFER_SIZE))) > 0)
	{
		buff[br] = '\0';
		s = ft_strjoin(s, buff);
	}
	*line = ft_substr(s, 0, ft_strlen_until(s,'\n'));
	if (ft_strlen_until(s, '\n') < 0)
	{
		free(s);
		s = NULL;
		return(0);
	}
	tmp = s;
	s = ft_substr(s, ft_strlen(s, '\n') + 1, ft_strlen(s, '\0'));
	free(tmp);
	tmp = NULL;
	return(1);
}

