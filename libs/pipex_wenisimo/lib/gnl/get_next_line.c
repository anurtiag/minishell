/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:15:11 by anurtiag          #+#    #+#             */
/*   Updated: 2023/12/26 09:00:36 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strjoin(char const *s1, char const *s2);
static char	*read_buffer(char *buf, int fd, char *st_var);
char		*ft_strchr(const char *s, int c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*need_more_lines(char *st_var, char *str, char *buf);

char	*get_next_line(int fd)
{
	char		*buf;
	char		*st_var;
	char		*str;
	char		*tmp;

	str = NULL;
	st_var = NULL;
	buf = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	tmp = st_var;
	st_var = read_buffer(buf, fd, st_var);
	if (st_var == NULL)
		return (free (buf), NULL);
	else if (!(ft_strchr(st_var, '\n')))
		return (need_more_lines(st_var, str, buf));
	str = ft_substr(st_var, 0, ft_strchr(st_var, 10) - st_var + 1);
	if (!str)
		return (NULL);
	tmp = st_var;
	st_var = ft_strdup(ft_strchr(st_var, 10) + 1);
	if (!st_var)
		return (free(tmp), NULL);
	return (free(buf), free(tmp), free(st_var), str);
}

char	*need_more_lines(char *st_var, char *str, char *buf)
{
	str = ft_strdup(st_var);
	if (!str)
		return (NULL);
	if (st_var)
	{
		free(st_var);
		st_var = NULL;
	}
	return (free (buf), str);
}

static char	*read_buffer(char *buf, int fd, char *st_var)
{
	char	*tmp;
	int		rd;

	if (!st_var)
		st_var = ft_strdup("");
	rd = BUFFER_SIZE;
	while (!(ft_strchr(st_var, '\n')))
	{
		rd = read (fd, buf, BUFFER_SIZE);
		if ((rd == 0 && st_var[0] == '\0') || rd < 0)
			return (free (st_var), NULL);
		buf[rd] = '\0';
		tmp = st_var;
		st_var = ft_strjoin(st_var, buf);
		if (!st_var)
			return (NULL);
		if (tmp)
			free(tmp);
		if (rd != BUFFER_SIZE)
			break ;
	}
	return (st_var);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (str && *str != '\0')
	{
		if (*str == (unsigned char)c)
			return (str);
		str++;
	}
	if (*str == (unsigned char)c)
		return (str);
	return (NULL);
}
