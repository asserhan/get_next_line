/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:40:52 by hasserao          #+#    #+#             */
/*   Updated: 2022/10/30 22:41:45 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_add(int fd,char *reserve)
{
	char *buff;
	char *tmp;
	ssize_t read_line ;
	
	read_line = 1;
	buff = malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (buff == NULL)
		return (NULL);
	while ( read_line != 0)
	{
		read_line =read(fd,buff,BUFFER_SIZE);	
		if ((reserve == NULL && read_line == 0)|| read_line == -1)
		{	
			free(buff);
			return (NULL);
		}
		buff[read_line] = '\0';
		if (!reserve)
			reserve =ft_strdup("");
		tmp = reserve;
		reserve =ft_strjoin(reserve ,buff);
		free (tmp);
		if (ft_strchr(reserve,'\n'))
			break;
	}
	free (buff);
	return (reserve);
}
char *extract(char *reserve)
{
	char *line;
	int i;
	int j;
	
	i = 0;
	if (reserve == NULL)
		return(NULL);
	while (reserve[i] && reserve[i] !='\n')
			i++;
	line = malloc (sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (reserve[i] && reserve[i] != '\n')
	{
		line[j++] = reserve[i++];
	}
	if(reserve[i] == '\n')
		line[j++] = reserve[i++];
	line[j] = '\0';
	return(line);
}
char	*get_next_line(int fd)
{
	//1.read from fd and add to reserve
	//2.extract from reserve to line
	//3.free reserve
	static char	*reserve;
	char *line;

	if (fd < 0  || BUFFER_SIZE <= 0 )
		return (NULL);
	reserve = read_and_add(fd,reserve);
	if (reserve == NULL)
		return (NULL);
	line = extract(reserve);
	free(reserve);
	reserve = NULL;
	//printf("%s\n",line);
	return (line);
}
// #include <stdio.h>
// #include <fcntl.h>
// int main ()
// {
// 	char *reserve=NULL;
// 	int fd;
// 	fd =open ("test2.txt",O_RDONLY );
// 	if (!fd)
// 		return (-1);
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd));
// }