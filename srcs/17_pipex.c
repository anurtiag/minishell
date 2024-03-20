/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 07:13:42 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/20 17:13:27 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// int	ft_var_found(t_var_list **list, char *name, char *content)
// {
// 	t_var_list	*current;

// 	current = *list;
// 	while (current != NULL)
// 	{
// 		if (strcmp(current->name, name) == 0)
// 		{
// 			current->content = content;
// 			return (TRUE);
// 		}
// 		current = current->next;
// 	}
// 	return (FALSE);
// }

char	*ft_getenv(t_var_list **list, char *name)
{
	t_var_list	*current;
	char		*content;

	current = *list;
	content = NULL;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			content = ft_strdup(current->content);
			return (content);
		}
		current = current->next;
	}
	return (NULL);
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

	// printf("ENTRAMOS A PIPEX\n\n\n");
	control = TRUE;
	cmd_list = (*struct_input)->parsed_table;
	// printf("madarikatua\n");
	// while (!cmd_list->cmd && cmd_list->next)
	// 	cmd_list = cmd_list->next;
	if (!cmd_list->next)
	{
		printf("no entraras por aqui putito de mierda\n");
		ft_built_in(cmd_list, struct_input, &control, 2);
	}
	if (control == FALSE)
		return(0);
	fd[READ] = 0;
	fd[WRITE] = 0;
	ft_make_process(cmd_list, fd, struct_input);
	if(access(".tempfile.txt", F_OK) == 0)
		unlink(".tempfile.txt");
	return (0);
}
