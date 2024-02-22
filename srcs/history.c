/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:46:17 by emimenza          #+#    #+#             */
/*   Updated: 2024/02/22 12:26:58 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/minishell.h"

int		check_history_file(void)
{
	FILE *file;

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

void	load_history(void)
{
	char	*tmp;
	int		fd;

	check_history_file();
	fd = open(".history.txt", O_RDONLY);
	tmp = "a";
	while (tmp)
	{
		tmp = get_next_line(fd);
		add_history(tmp);
		free(tmp);
	}
	close(fd);
}

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
}