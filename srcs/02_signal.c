/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:03:55 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/14 11:12:31 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
extern int	main_loop;
//Handles the signals
static void	signal_handler(int	signal)
{
	if (signal == SIGINT)
	{
		//printf("Changing the prompt\n");
		//printf("loop %i\n", main_loop);
		if (main_loop == 0)
			rl_set_prompt("");
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();

	}
}

//Receives the signals
void	signal_receiver()
{
	struct sigaction	sa;

	// rl_catch_signals = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = signal_handler;
	// sa.sa_handler = *(void (*)(int))signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
