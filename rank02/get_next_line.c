#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#define BUFFER_SIZE 42

int ft_strlen_until(char *s, char c)
{
	int l;

	l = 0;
	if(!s)
		return (-1);
	while (s[l] != '\0') 
	{
		if (s[l] == c)
			return (l);
		l++;
	}
	if (s[l] == c)
		return (l);
	return (-1);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *new;
	int l = 0;
	int q = 0;
	int total = ft_strlen_until(s1, '\0') + ft_strlen_until(s2, '\0');

	new = (char *)malloc(sizeof(char) * total + 1);
	while(s1[l])
	{
		new[l] = s1[l];
		l++;
	}
	while(s2[q])
	{
		new[l + q] = s2[q];
		q++;
	}
	new[l + q] = '\0';
	return (new);

}

char *ft_strdup(char *s1)
{
	char *new;
	int l = 0;
	int total = ft_strlen_until(s1, '\0');

	new = (char *)malloc(sizeof(char) * total + 1);
	while (s1[l] != '\0') 
	{
		new[l] = s1[l];
		l++;
	}
	new[l] = '\0';
	return (new);
}

char *ft_substr(char *s1, int start, int len)
{
	char *new;
	int l = 0;
	if (start > ft_strlen_until(s1, '\0'))
		return (NULL);
	new = (char *)malloc(sizeof(char) * len + 1);
	while (len > 0 && s1[start] != '\0') 
	{
		new[l] = s1[start];
		l++;
		start++;
		len--;
	}
	new[l] = '\0';
	return (new);
}

int new_line(char **line, char **s)
{
	char *tmp;
	int l = ft_strlen_until((*s), '\n');
	if ((*s)[l] == '\n')
	{
		*line = ft_substr(*s, 0, l);
		tmp = ft_strdup(&(*s)[l + 1]);
		free(*s);
		*s = tmp;
	}
	else
	{
		*line = ft_strdup(*s);
		free(*s);
		*s = NULL;
		return (0);
	}
	return (1);
}

int get_next_line(char **line)
{
	char buffer[BUFFER_SIZE + 1];
	static char *str;
	int br;
	char *tmp;

	if (!line)
		return (-1);
	while (ft_strlen_until(str, '\n') < 0)
	{
		br = read(0, buffer, BUFFER_SIZE);
		if (br < 0)
			return (-1);
		if (br == 0)
			break ;
		buffer[br] = '\0';
		if (!str)
			str = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(str, buffer);
			free(str);
			str = tmp;
		}
	}
	if (br == 0 && !str)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return(new_line(line, &str));
}
