/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 07:13:42 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/25 17:11:09 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//finds a env and returns the content
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
//verifies if it is one built in and deletess the here_doc file
int	pipex(t_input **struct_input, t_step *step)
{
	int		fd[2];
	t_var_parsed_table	*cmd_list;
	int		control;

	control = TRUE;
	cmd_list = (*struct_input)->parsed_table;
	if (!cmd_list->next)
		ft_built_in(cmd_list, struct_input, &control, 2, step);
	if (control == FALSE)
		return(0);
	fd[READ] = 0;
	fd[WRITE] = 0;
	ft_make_process(cmd_list, fd, struct_input, step);
	if(access(".tempfile.txt", F_OK) == 0)
		unlink(".tempfile.txt");
	return (0);
}
