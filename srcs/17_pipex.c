/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 07:13:42 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/15 12:53:38 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"


void	ft_exit(int i)
{
	if (i == 1)
	{
		perror(NULL);
		exit(1);
	}
}

void	freeall(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

int	pipex(t_input **struct_input)
{
	int		fd[2];
	t_var_parsed_table	*cmd_list;
	int		control;

	control = TRUE;
	cmd_list = (*struct_input)->parsed_table;
	if (!cmd_list->next)
		ft_built_in(cmd_list->cmd_splited, struct_input, &control);
	if (control == FALSE)
		return(0);
	fd[READ] = 0;
	fd[WRITE] = 0;
	// ft_make_process(struct_input, fd);
	ft_make_process(cmd_list, fd, struct_input);
	if(access(".tempfile.txt", F_OK) == 0)
		unlink(".tempfile.txt");
	return (0);
}
