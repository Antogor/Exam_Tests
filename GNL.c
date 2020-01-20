#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

int ft_len_until_c(char *s, char c)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == c)
            return (i);
        i++;
    }
    if (s[i] == c)
        return (i);
    return (-1);
}

char *ft_strjoin(char *s1, char *s2)
{
    char *str;
    int i = 0, j = 0;

    if (!(str = malloc(sizeof(char) *
        (ft_len_until_c(s1, '\0') + ft_len_until_c(s2, '\0') + 1))))
        return (NULL);
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        str[i + j] = s2[j];
        j++;
    }
    free(s1);
    str[i + j] = '\0';
    return (str);        
}

char *ft_substr(char *s, int start, int len)
{
    char *str;
    int i = 0;
    if (!s)
        return (NULL);
    if (start > ft_len_until_c(s, '\0'))
        return (NULL);
    if (!(str = malloc(sizeof(char) * len + 1)))
        return (NULL);
    while (s[start] && len)
    {
        str[i++] = s[start++];
        len--;
    }
    str[i] = '\0';
    return (str);    
}

static void		*ft_calloc(int count, int size)
{
	void	*mem;
	int		total;

	total = size * count;
	if (!(mem = malloc(total)))
		return (NULL);
	while (total-- > 0)
	{
		*(unsigned char*)mem++ = 0;
	}
	return (mem - count * size);
}

int get_next_line(char **line)
{
    static char *rest;
    char *tmp;
    char buf[BUFFER_SIZE + 1];
    int ret;

    if (!line)
        return (-1);
    if (!rest && !(rest = ft_calloc(sizeof(char), 1)))
        return (-1);
    while (ft_len_until_c(rest, '\n') < 0 && (ret = read(0, buf, BUFFER_SIZE)) > 0)
    {
        buf[ret] = '\0';
        rest = ft_strjoin(rest, buf);
    }
    *line = ft_substr(rest, 0, ft_len_until_c(rest, '\n'));
    if (ft_len_until_c(rest, '\n') < 0)
    {
        free(rest);
        return (0);    
    }
    tmp = rest;
    rest = ft_substr(rest, ft_len_until_c(rest, '\n') + 1, ft_len_until_c(rest, '\0'));
    free(tmp);
    return (1);
}
