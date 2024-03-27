/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:41:16 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/27 12:14:25 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// void	remove_quotes_aux(char **cmd_ptr)
// {
// 	int		control[2];
// 	int		start;
// 	int		i;
// 	int		end;
// 	int		size;
// 	char	*tmp;
// 	char	*joined_tmp;
// 	char	quotes_flag;

// 	quotes_flag = 0;
// 	size = ft_strlen(*cmd_ptr) - 1;
// 	start = 0;
// 	i = 0;
// 	end = 0;
// 	tmp = NULL;
// 	control[SIMPLE] = FALSE;
// 	control[DOUBLE] = FALSE;
// 	tmp = NULL;
// 	joined_tmp = ft_strdup("");
// 	while (i <= size)
// 	{
// 		if ((*cmd_ptr)[i] == '\'' && control[DOUBLE] == FALSE)
// 		{
// 			if (control[SIMPLE] == FALSE)
// 			{
// 				start = i;
// 				control[SIMPLE] = TRUE;
// 				if (quotes_flag == 1)
// 					tmp = ft_substr(*cmd_ptr, end + 1, start - end - 1);
// 				else
// 					tmp = ft_substr(*cmd_ptr, end, start - end);
// 				joined_tmp = ft_strjoin(joined_tmp, tmp, 1);
// 			}
// 			else
// 			{
// 				quotes_flag = 1;
// 				end = i;
// 				control[SIMPLE] = FALSE;
// 				tmp = ft_substr(*cmd_ptr, start + 1, end - start - 1);
// 				joined_tmp = ft_strjoin(joined_tmp, tmp, 5);
// 			}
// 		}
// 		if ((*cmd_ptr)[i] == '\"' && control[SIMPLE] == FALSE)
// 		{
// 			if (control[DOUBLE] == FALSE)
// 			{
// 				start = i;
// 				control[DOUBLE] = TRUE;
// 				if (quotes_flag == 1)
// 					tmp = ft_substr(*cmd_ptr, end + 1, start - end - 1);
// 				else
// 					tmp = ft_substr(*cmd_ptr, end, start - end);
// 				joined_tmp = ft_strjoin(joined_tmp, tmp, 1);
// 			}
// 			else
// 			{
// 				quotes_flag = 1;
// 				end = i;
// 				control[DOUBLE] = FALSE;
// 				tmp = ft_substr(*cmd_ptr, start + 1, end - start - 1);
// 				joined_tmp = ft_strjoin(joined_tmp, tmp, 5);
// 			}
// 		}
// 		i++;
// 	}
// 	if (quotes_flag == 1)
// 	{
// 		tmp = ft_substr(*cmd_ptr, end + 1, size - end);
// 		joined_tmp = ft_strjoin(joined_tmp, tmp, 5);
// 		*cmd_ptr = joined_tmp;
// 	}
// 	else
// 		free(joined_tmp);
// }

//Main function to remove the quotes
void	remove_quotes(t_var_parsed_table **head)
{
	t_var_parsed_table	*first;
	int					i;

	first = *head;
	while ((*head) != NULL)
	{
		i = 0;
		if ((*head)->cmd_splited != NULL)
		{
			while ((*head)->cmd_splited[i] != NULL)
			{
				remove_quotes_aux(&((*head)->cmd_splited[i]));
				i++;
			}
		}
		(*head) = (*head)->next;
	}
	*head = first;
}

//Handles the simple quotes
void	single_quote(char **cmd_ptr, int *control, int *a, char **joined_tmp)
{
	char	*tmp;

	tmp = NULL;
	if ((*cmd_ptr)[a[CUR]] == '\'' && control[DOUBLE] == FALSE)
	{
		if (control[SIMPLE] == FALSE)
		{
			a[START] = a[CUR];
			control[SIMPLE] = TRUE;
			if (a[QUOTES] == 1)
				tmp = ft_substr(*cmd_ptr, a[END] + 1, a[START] - a[END] - 1);
			else
				tmp = ft_substr(*cmd_ptr, a[END], a[START] - a[END]);
			*joined_tmp = ft_strjoin(*joined_tmp, tmp, 1);
		}
		else
		{
			a[QUOTES] = 1;
			a[END] = a[CUR];
			control[SIMPLE] = FALSE;
			tmp = ft_substr(*cmd_ptr, a[START] + 1, a[END] - a[START] - 1);
			*joined_tmp = ft_strjoin(*joined_tmp, tmp, 5);
		}
	}
}

//Handles the double quotes
void	double_quote(char **cmd_ptr, int *control, int *a, char **joined_tmp)
{
	char	*tmp;

	tmp = NULL;
	if ((*cmd_ptr)[a[CUR]] == '\"' && control[SIMPLE] == FALSE)
	{
		if (control[DOUBLE] == FALSE)
		{
			a[START] = a[CUR];
			control[DOUBLE] = TRUE;
			if (a[QUOTES] == 1)
				tmp = ft_substr(*cmd_ptr, a[END] + 1, a[START] - a[END] - 1);
			else
				tmp = ft_substr(*cmd_ptr, a[END], a[START] - a[END]);
			*joined_tmp = ft_strjoin(*joined_tmp, tmp, 1);
		}
		else
		{
			a[QUOTES] = 1;
			a[END] = a[CUR];
			control[DOUBLE] = FALSE;
			tmp = ft_substr(*cmd_ptr, a[START] + 1, a[END] - a[START] - 1);
			*joined_tmp = ft_strjoin(*joined_tmp, tmp, 5);
		}
	}
}

//Handles the remaining quotes(last one)
void	process_remaining_quotes(char **cmd_ptr, char **joined_tmp, int *vault)
{
	char	*tmp;

	tmp = NULL;
	if (vault[QUOTES] == 1)
	{
		tmp = ft_substr(*cmd_ptr, vault[END] + 1, vault[SIZE] - vault[END]);
		*joined_tmp = ft_strjoin(*joined_tmp, tmp, 5);
		*cmd_ptr = *joined_tmp;
	}
	else
		free(*joined_tmp);
}

//Aux function to remove the quotes
void	remove_quotes_aux(char **cmd_ptr)
{
	int		control[2];
	int		vault[5];
	char	*tmp;
	char	*joined_tmp;

	tmp = NULL;
	joined_tmp = ft_strdup("");
	vault[QUOTES] = 0;
	vault[SIZE] = ft_strlen(*cmd_ptr) - 1;
	vault[START] = 0;
	vault[CUR] = 0;
	vault[END] = 0;
	control[SIMPLE] = FALSE;
	control[DOUBLE] = FALSE;
	while (vault[CUR] <= vault[SIZE])
	{
		single_quote(cmd_ptr, control, vault, &joined_tmp);
		double_quote(cmd_ptr, control, vault, &joined_tmp);
		vault[CUR]++;
	}
	process_remaining_quotes(cmd_ptr, &joined_tmp, vault);
}
