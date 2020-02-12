#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 64

int ft_strlen_until(char *s, char c)
{
	int l = 0;
	if (!s)
	{
		return (-1);
	}
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
		new[l] = s1[l];
		l++;
	}
	while(s2[q] != '\0')
	{
		new[l + q] = s2[q];
		q++;
	}
	new[l + q] = '\0';
	return (new);
}

char *ft_substr(char *s, int start, int len)
{
	char *new;
	int l = 0;
	new = malloc(sizeof(char) * len + 1);
	while (s[start] && len > 0)
	{
		new[l] = s[start];
		l++;
		start++;
		len--;
	}
	new[l] = '\0';
	return(new);
}

char *ft_strdup(char *s1)
{
	int len;
	char *s2;

	len = 0;
	while (s1[len])
	{
		len++;
	}
	s2 = malloc(sizeof(char) * len + 1);
	len = 0;
	while (s1[len])
	{
		s2[len] = s1[len];
		len++;
	}
	s2[len] = '\0';
	return (s2);	
}

int new_line(char **line, char **str)
{
	char *tmp;
	int len;

	len = ft_strlen_until(*str, '\n');
	if ((*str)[len] == '\n')
	{
	*line = ft_substr(*str, 0, len);
	tmp = ft_strdup(&((*str)[len + 1]));
	free(*str);
	*str = tmp;
	}
	else
	{
		*line = ft_strdup(*str);
		free(*str);
		*str = NULL;
		return(0);
	}
	return(1);
}

int get_next_line(char **line)
{
	static char *str;
	int br;
	char buff[BUFFER_SIZE + 1];
	char *aux;
	
	if (!line)
		return (-1);
	while (ft_strlen_until(str, '\n') < 0)
	{
		br = read(0, buff, BUFFER_SIZE);
		if (br < 0)
			return (-1);
		if (br == 0)
			break;
		buff[br] = '\0';
		if (!str)
			str = ft_strdup(buff);
		else
		{
			aux = ft_strjoin(str, buff);
			free(str);
			str = aux;
		}
	}
	if (br == 0 && !str)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (new_line(line, &str));
}