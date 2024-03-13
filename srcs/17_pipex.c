/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 07:13:42 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/13 16:11:16 by anurtiag         ###   ########.fr       */
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

// int	ft_built_in(char **argv, t_input **struct_input)
// {
// 	if (ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) == 0 && ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0)
// 		ft_echo(argv, 1);
// 	else if(ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])) == 0)
// 		ft_pwd();
// 	else if(ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) == 0)
// 		ft_cd(argv, struct_input);
// 	else if(ft_strncmp(argv[0], "export", ft_strlen(argv[0])) == 0)
// 		ft_export(argv[1], struct_input);
// 	else if(ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) == 0)
// 		ft_unset(argv[1], struct_input);
// 	else if(ft_strncmp(argv[0], "env", ft_strlen(argv[0])) == 0)
// 		ft_print_var(*struct_input);
// 	return (0);	
// }


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

int	pipex(t_var_parsed_table *cmd_list)
{
	// t_data	*cmd;
	// t_data	*tmp;
	int		fd[2];
	int		pid;

	// cmd = NULL;
	// tmp = NULL;
	pid = 0;
	fd[READ] = 0;
	fd[WRITE] = 0;
	ft_make_process(cmd_list, fd, pid);
	if(access(".tempfile.txt", F_OK) == 0)
		unlink(".tempfile.txt");
	return (0);
}
