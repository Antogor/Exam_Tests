#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 42

int ft_strlen_until(char *s, char c)
{
	int l = 0;
	while(s[l] != '\0')
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
	while (len > 0)
	{
		new[l] = s[start];
		l++;
		start++;
		len--;
	}
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
	printf("STR: %s\n", str);
	if (ft_strlen_until(str, '\n') < 0)
	{
		free(str);
		return(0);
	}
	tmp = str;
	str = ft_substr(tmp, ft_strlen_until(tmp, '\n') + 1, ft_strlen_until(tmp, '\0'));
	free(tmp);
	return(1);

}


int main (int argc, char **argv)
{
	int l;
	char line[0][200] =	"hola que pasa";
	l = get_next_line(line);
	//	printf("%d\n", l);
	l = get_next_line(argv);
//	printf("%d\n", l);
	l = get_next_line(argv);
//	printf("%d\n", l);

}

