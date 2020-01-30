/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marandre <marandre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:34:48 by marandre          #+#    #+#             */
/*   Updated: 2020/01/13 15:19:11 by marandre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

/*
** Roadmap:
** - while str
** - - check if str[i] == c (the char we're looking for)
** - - - return (i)
** - - increment i
** - check if i == c (meaning c == '\0')
** - - return (i)
** - return (-1) if no char were found
*/
static int		ft_len_until_c(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}

/*
** Roadmap:
** - malloc new string for the size of the two string until \0 for each.
** - copy the whole s1 string to the new string using a simple i index.
** - then copy the whole s2 string to the new string using simple j index.
** - - while(str[j]) ==> str[i + j] = s2[j]; j++
** - free s1 string
** - finally null terminate new string using str[i + j] = '\0';
** - return new string
*/
static char		*ft_strjoin(char *s1, char *s2)
{ 
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
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

/*
** Roadmap:
** - verify is !s ==> return NULL
** - if start > len of *s
** - malloc new str of size len + 1
** - while s[start] && len
** - - str[i++] = s[start++]; len--;
** - null terminate str[i]
** - return new string
*/
static char		*ft_substr(char *s, unsigned int start, int len)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if ((int)start > ft_len_until_c(s, '\0'))
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

/*
** Roadmap:
** - init total
** - malloc void *mem for the total
** - while total-- is bigger than 0
** - - deference mem as a *(unsigned char*)mem++ and define it = 0
** - return mem - size * count
*/
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

/**
 * Roadmap is :
 * - if no line return
 * - if no rest calloc rest with size of 1
 * - read as long as ret is > 0 and that we don't have a \n in rest
 * - - each time null terminate the buf and rest = strjoin(rest, buf)	| join free rest
 * - out of the loop *line is the rest from the start to the first '\n'
 * - if not found '\n' free rest and return (0)
 * - else use a temp char to save the current pointer of rest (to free later)
 * - rest is the substring of rest from the first '\n' + 1 to the end
 * - then return 1 and free temp char
 */
int				get_next_line(char **line)
{
	static char		*rest;
	char			*tmp; // used to free the previous pointer of rest which is changed by the substr
	char			buf[BUFFER_SIZE + 1];
	int				ret;

	if (!line)
		return (-1);
	if (!rest && !(rest = ft_calloc(1, sizeof(char))))
		return (-1);
	while ((ft_len_until_c(rest, '\n')) < 0 && (ret = read(0, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		rest = ft_strjoin(rest, buf);
	}
	*line = ft_substr(rest, 0, ft_len_until_c(rest, '\n'));
	if ((ft_len_until_c(rest, '\n')) < 0)
	{
		free(rest);
		return (0);
	}
	tmp = rest;
	rest = ft_substr(rest, ft_len_until_c(rest, '\n') + 1, ft_len_until_c(rest, '\0'));
	free(tmp);
	return (1);
}