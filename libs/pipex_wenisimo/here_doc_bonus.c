/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 06:58:17 by anurtiag          #+#    #+#             */
/*   Updated: 2024/01/09 07:41:05 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_here_doc_errors(int argc, char **argv)
{
	int	i;

	i = -1;
	if (argc != 6)
	{
		write(2, "Wrong arguments\n", 16);
		exit(EXIT_FAILURE);
	}
	else if (access (argv[5], W_OK) < 0 && access (argv[5], F_OK) == 0)
		file_permissions(argv[argc - 1], 0);
	else if (ft_strlen(argv[argc - 1]) == 0)
		file_permissions(argv[argc - 1], 1);
	ft_here_doc(argv, 0);
}

void	ft_here_doc(char *argv[], int fd)
{
	char	*delimiter;
	char	*line;
	int		outfile;
	char	*output;
	char	*tmp;

	output = (char *)malloc(sizeof(char) * 1);
	output[0] = '\0';
	delimiter = ft_strjoin(argv[2], "\n");
	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(fd);
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0)
			break ;
		tmp = output;
		output = ft_strjoin(output, line);
		free(line);
		free(tmp);
	}
	outfile = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		ft_exit(1);
	free_here_doc(delimiter, output, line, outfile);
}

void	free_here_doc(char *delimiter, char *output, char *line, int outfile)
{
	if (write(outfile, output, ft_strlen(output)) == -1)
		ft_exit(1);
	free(delimiter);
	free(output);
	free(line);
	line = NULL;
	if (close(outfile) < 0)
		ft_exit(1);
}

t_fd	*fd_handle(int i, int argc, char **argv)
{
	t_fd	*fds;

	fds = (t_fd *)malloc(sizeof(t_fd));
	if (i == 0)
	{
		if (ft_strncmp (argv[1], "here_doc", 8) == 0)
		{
			fds->fdin = open("tempfile", O_RDONLY);
			if (fds->fdin < 0)
				ft_exit(1);
		}
		else
		{
			fds->fdin = open(argv[1], O_RDONLY);
			if (fds->fdin < 0)
				ft_exit(1);
		}
	}
	else if (i == argc - 4)
	{
		fds->fdout = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fds->fdout < 0)
			ft_exit(EXIT_FAILURE);
	}
	return (fds);
}

void	free_nodes(t_data *cmd)
{
	t_data	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		freeall(cmd->cmd);
		free(cmd->path);
		free(cmd->fd);
		free(cmd);
		cmd = tmp;
	}
}
