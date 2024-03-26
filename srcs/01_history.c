/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:46:17 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/26 13:39:21 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//This function checks if the txt is created
static int	check_history_file(void)
{
	FILE	*file;

	file = fopen(".history.txt", "r");
	if (file == NULL)
	{
		file = fopen(".history.txt", "w");
		if (file == NULL)
			return (1);
		fclose(file);
	}
	else
		fclose(file);
	return (0);
}

//This function loads the history from the txt
void	load_history(void)
{
	char	*tmp;
	int		fd;

	if (check_history_file() != 0)
		return ;
	fd = open(".history.txt", O_RDONLY);
	if (fd == -1)
	{
		print_error(4, NULL, NULL);
		return ;
	}
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		add_history(tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
}

//This function saves the input into the local and text history
void	save_history(char	*input)
{
	int	file;

	file = open(".history.txt", O_RDWR | O_APPEND);
	if (file == -1)
		check_history_file();
	ft_putstr_fd(input, file);
	ft_putstr_fd("\n", file);
	close(file);
	add_history(input);
	free(input);
}
