#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 100

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
	free(s1);
	s1 = NULL;
	new[l + q] = '\0';
	return(new);
}

char *ft_substr(char *s, int start, int len)
{
	char *new;
	int l = 0;
	if (start > ft_strlen_until(s, '\0'))
		return(NULL);
	if (!s)
		return(NULL);
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

static void *ft_calloc(int size, int count)
{
	void *meme;
	int total;

	total = size * count;
	meme = malloc (total);
	while(total > 0)
	{
		*(unsigned char*)meme++ = 0;
		total--;
	}
	return(meme - size * count);

}

int get_next_line(char **line)
{
	static char *str;
	int br;
	char buff[BUFFER_SIZE + 1];
	char *tmp;
	
	if (!line)
		return(-1);
	if (!(str = ft_calloc(sizeof(char), 1)))
		return(-1);
	while(ft_strlen_until(str, '\n') < 0 && (br = read(0, buff, BUFFER_SIZE)) > 0)
	{
		
		buff[br] = '\0';
		str = ft_strjoin(str, buff);
		
	}
	*line = ft_substr(str, 0, ft_strlen_until(str, '\n'));
	if (ft_strlen_until(str, '\n') < 0)
	{
		*line = ft_substr(str, 0, ft_strlen_until(str, '\0'));
		free(str);
		str= NULL;
		return(0);
	}
	tmp = str;
	free(str);
	str = ft_substr(tmp, ft_strlen_until(tmp, '\n') + 1, ft_strlen_until(tmp, '\0'));
	free(tmp);
	tmp = NULL;
	printf("%s\n", str);
	free(tmp);
	return(1);

}

int main()
{
    int l;
    char *a;

    l = get_next_line(&a);
	printf("L = %d A = %s\n", l, a);
	free(a);
	a = NULL;
	l = get_next_line(&a);
    printf("L = %d A = %s\n", l, a);
	free(a);
	a = NULL;
	getchar();
    return(0);
}

