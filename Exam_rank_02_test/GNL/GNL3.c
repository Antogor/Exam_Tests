#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 42

int	ft_strlen_until(char *s, char c)
{
	int l;

	l = 0;
	if (!s)
		return (-1);
	while (s[l])
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
	new = malloc(sizeof(char) * total + 1);
	while (s1[l] != '\0')
	{
		new[l] = s1[l];
		l++;
	}
	while (s2[q] != '\0')
	{
		new[l + q] = s2[q];
		q++;
	}
	new[l + q] = '\0';
	return (new);
}

char *ft_strdup(char *s)
{
	char *new;
	int l = 0;

	new = malloc(sizeof(char) * ft_strlen_until(s, '\0') + 1);
	while (s[l])
	{
		new[l] = s[l];
		l++;
	}
	new[l] = '\0';
	return (new);
}

char *ft_substr(char *s, int start, int len)
{
	char *new;
	int l = 0;
	if (start > ft_strlen_until(s, '\0'))
		return (NULL);
	new = malloc(sizeof(char) * len + 1);
	while (len > 0 && s[start] != '\0')
	{
		new[l] = s[start];
		l++;
		len--;
		start++;
	}
	new[l] = '\0';
	return (new);
}

int new_line(char **line, char **str)
{
	char *tmp;
	int l = ft_strlen_until((*str), '\n');

	if ((*str)[l] == '\n')
	{
		*line = ft_substr(*str, 0, l);
		tmp = ft_strdup(&(*str)[l + 1]);
	   free(*str);
   		*str = tmp;	   
	}
	else
	{
		*line = ft_strdup(*str);
		free(*str);
		*str = NULL;
		return (0);
	}
	return (1);
}
int get_next_line(char **line)
{
	char buff[BUFFER_SIZE + 1];
	static char *str;
	int br;
	int l;
	char *tmp;

	if (!line)
		return(-1);
	while (ft_strlen_until(str, '\n') < 0)
	{
		br = read(0, buff, BUFFER_SIZE);
		if (br < 0)
			return (-1);
		if (br == 0)
			break ;
		buff[br] = '\0';
		if (!str)
		{
			str = ft_strdup(buff);
		}
		else
		{
			tmp = ft_strjoin(str, buff);
			free(str);
			str = tmp;
		}
	}
	if (br == 0 && !str)
	{
		*line = ft_strdup("");
		return(0);
	}
	else
		return(new_line(line, &str));

}
