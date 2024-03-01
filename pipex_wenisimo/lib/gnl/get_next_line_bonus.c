/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:10:00 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/30 06:51:46 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char		*ft_strjoin(char const *s1, char const *s2);
static char	*read_buffer(char *buf, int fd, char *st_var);
char		*ft_strchr(const char *s, int c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*need_more_lines(char *st_var, char *str, char *buf);

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*st_var[4096];
	char		*str;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	buf = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	tmp = st_var[fd];
	st_var[fd] = read_buffer(buf, fd, st_var[fd]);
	if (st_var[fd] == NULL)
		return (free (buf), NULL);
	else if (!(ft_strchr(st_var[fd], '\n')))
		return (need_more_lines(st_var[fd], str, buf));
	str = ft_substr(st_var[fd], 0, ft_strchr(st_var[fd], 10) - st_var[fd] + 1);
	if (!str)
		return (NULL);
	tmp = st_var[fd];
	st_var[fd] = ft_strdup(ft_strchr(st_var[fd], 10) + 1);
	if (!st_var[fd])
		return (NULL);
	return (free(buf), free(tmp), str);
}

char	*need_more_lines(char *st_var, char *str, char *buf)
{
	str = ft_strdup(st_var);
	if (!str)
		return (NULL);
	st_var[0] = 0;
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

// int	main(void)
// {
// 	int		fd = open("archivo.txt", O_RDWR);
// 	int		fd1 = open("41_no_nl", O_RDWR);
// 	int		fd2 = open("41_with_nl", O_RDWR);
// 	int		fd3 = open("42_no_nl", O_RDWR);
// 	int		fd4 = open("42_with_nl", O_RDWR);
// 	int		fd5 = open("43_no_nl", O_RDWR);
// 	int		fd6 = open("43_with_nl", O_RDWR);
// 	int		fd7 = open("big_line_no_nl", O_RDWR);
// 	int		fd8 = open("archivo1.txt", O_RDWR);
// 	char	*s;
// 	char	*s1;
// 	char	*s2;
// 	char	*s3;
// 	char	*s4;
// 	char	*s5;
// 	char	*s6;
// 	char	*s7;
// 	char	*s8;

// 	s = get_next_line(fd);
// 	s1 = get_next_line(fd1);
// 	s2 = get_next_line(fd2);
// 	s3 = get_next_line(fd3);
// 	s4 = get_next_line(fd4);
// 	s5 = get_next_line(fd5);
// 	s6 = get_next_line(fd6);
// 	s7 = get_next_line(fd7);
// 	s8 = get_next_line(fd8);
// 	while (s || s1 || s2 || s3 || s4 || s5 || s6 || s7 || s8)
// 	{
// 		if (s)
// 		{
// 			printf ("%s", s);
// 			free(s);
// 			printf("\n\n\n");
// 		}
// 		if (s1)
// 		{
// 			printf ("%s", s1);
// 			free(s1);
// 			printf("\n\n\n");
// 		}
// 		if (s2)
// 		{
// 			printf ("%s", s2);
// 			free(s2);
// 			printf("\n\n\n");
// 		}
// 		if (s3)
// 		{
// 			printf ("%s", s3);
// 			free(s3);
// 			printf("\n\n\n");
// 		}
// 		if (s4)
// 		{
// 			printf ("%s", s4);
// 			free(s4);
// 			printf("\n\n\n");
// 		}
// 		if (s5)
// 		{
// 			printf ("%s", s5);
// 			free(s5);
// 			printf("\n\n\n");
// 		}
// 		if (s6)
// 		{
// 			printf ("%s", s6);
// 			free(s6);
// 			printf("\n\n\n");
// 		}
// 		if (s7)
// 		{
// 			printf ("%s", s7);
// 			free(s7);
// 			printf("\n\n\n");
// 		}
// 		if (s8)
// 		{
// 			printf ("%s", s8);
// 			free(s8);
// 			printf("\n\n\n");
// 		}
// 		s = get_next_line(fd);
// 		s1 = get_next_line(fd1);
// 		s2 = get_next_line(fd2);
// 		s3 = get_next_line(fd3);
// 		s4 = get_next_line(fd4);
// 		s5 = get_next_line(fd5);
// 		s6 = get_next_line(fd6);
// 		s7 = get_next_line(fd7);
// 		s8 = get_next_line(fd8);
// 	}
// 	free(s);
// 	free(s1);
// 	free(s2);
// 	free(s3);
// 	free(s4);
// 	free(s5);
// 	free(s6);
// 	free(s7);
// 	free(s8);
// 	close(fd);
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	close(fd4);
// 	close(fd5);
// 	close(fd6);
// 	close(fd7);
// 	close(fd8);
// 	return (0);
// }
