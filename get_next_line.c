/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:40:52 by hasserao          #+#    #+#             */
/*   Updated: 2022/11/01 21:28:56 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	size ;
	size_t	i;

	i = 0;
	size = ft_strlen(s1) + 1;
	p = (char *)malloc (size * sizeof(char));
	if (!p || !s1)
		return (NULL);
	else
	{
		while (i < size)
		{
			((char *)p)[i] = ((char *)s1)[i];
			i++;
		}
	}
	return (p);
}

char	*read_and_add(int fd, char *reserve)
{
	char	*buff;
	char	*tmp;
	ssize_t	read_line ;

	read_line = 1;
	buff = malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (read_line != 0)
	{
		read_line = read(fd, buff, BUFFER_SIZE);
		if ((reserve == NULL && read_line == 0) || read_line == -1)
			return (free (buff), NULL);
		buff[read_line] = '\0';
		if (!reserve)
			reserve = ft_strdup("");
		tmp = reserve;
		reserve = ft_strjoin(tmp, buff);
		free (tmp);
		if (ft_strchr(reserve, '\n'))
			break ;
	}
	free (buff);
	return (reserve);
}

char	*update_reserve(char **reserve, int j, int i)
{
	char	*tmp;

	tmp = malloc (sizeof (char) * ft_strlen(*reserve) - j);
	if (!tmp)
		return (NULL);
	j = 0;
	while ((*reserve)[i])
		tmp[j++] = (*reserve)[i++];
	tmp[j] = '\0';
	if (tmp [0] == '\0')
	{
		free (tmp);
		tmp = NULL;
	}
	free (*reserve);
	return (tmp);
}

char	*extract(char **reserve)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (*reserve == NULL)
		return (NULL);
	while ((*reserve)[i] && (*reserve)[i] != '\n')
			i++;
	line = malloc (sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while ((*reserve)[i] && (*reserve)[i] != '\n')
		line[j++] = (*reserve)[i++];
	if ((*reserve)[i] == '\n')
		line[j++] = (*reserve)[i++];
	line[j] = '\0';
	*reserve = update_reserve(reserve, j, i);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reserve = read_and_add(fd, reserve);
	if (reserve == NULL)
		return (NULL);
	line = extract(&reserve);
	return (line);
}
// #include<stdio.h>
// #include<fcntl.h>
// #include<stdlib.h>
// int main()
// {
// 	int fd;
// 	fd = open("test.txt",O_RDONLY);
// 	if (!fd)
// 		return(-1);
// 	char *s;
// 	s = get_next_line(fd);
// 	printf("%s",s);
// 	free(s);
// }