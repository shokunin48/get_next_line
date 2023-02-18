/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibellash <ibellash@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:32:27 by ibellash          #+#    #+#             */
/*   Updated: 2023/02/18 20:08:54 by ibellash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_setup(char *s)
{
	int		i;
	char	*temp;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\0' || s[i + 1] == '\0')
	{
		free(s);
		return (0);
	}
	temp = ft_substr(s, i + 1, ft_strlen(s) - i);
	if (*temp == '\0')
	{
		free (temp);
		temp = NULL;
	}
	free (s);
	return (temp);
}

char	*fd_reader(int fd, char *statstr)
{
	int		i;
	char	*line;

	line = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	i = 1;
	while (i != 0)
	{
		i = read(fd, line, BUFFER_SIZE);
		if (i == -1)
		{
			free (line);
			free (statstr);
			return (0);
		}
		line[i] = '\0';
		statstr = ft_strjoin(statstr, line);
		if (ft_strrchr(statstr, '\n'))
			break ;
	}
	free (line);
	return (statstr);
}

char	*ft_get_line(char *s)
{
	int		i;
	char	*new;

	i = 0;
	if (s[i] == '\0')
		return (NULL);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		new = malloc (sizeof(char) * (i + 2));
	else
		new = malloc (sizeof(char) * (i + 1));
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
	{
		new[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		new[i] = '\n';
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*get_next_line(int fd)
{
	char		*nextline;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = fd_reader(fd, line);
	if (line == NULL)
		return (NULL);
	nextline = ft_get_line(line);
	line = ft_setup(line);
	return (nextline);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		i;
// 	char	*s;

// 	i = open("1.txt", O_RDONLY);
// 	s = get_next_line(i);
// 	//puts(s);
// 	close(i);
// }
