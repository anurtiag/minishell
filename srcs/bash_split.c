/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 06:51:35 by anurtiag          #+#    #+#             */
/*   Updated: 2024/01/25 14:24:44 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	ignore_separator(char const *s, int *control, int *i)
{
	if((control[0] == TRUE && control[1] == TRUE) && s[*i] == '\'')
		control[0] = FALSE;
	else if(control[0] == FALSE && s[*i] == '\'')
		control[0] = TRUE;
	else if((control[1] == TRUE && control[0] == TRUE) && s[*i] == '\"')
		control[1] = FALSE;
	else if(control[1] == FALSE && s[*i] == '\"')
		control[1] = TRUE;
}

static	int	ft_count(char const *s, char c, int *control)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (s[i] != c && s[i] != '\0')
		count++;
	while (s[i])
	{
		ignore_separator(s, control, &i);
		if ((control[0] == TRUE && control[1] == TRUE) && ((s[i] == c) && (s[i + 1] != c) && (s[i + 1])))
				count++;
		i++;
	}
	//printf("el num de palabras es: %d\n", count);
	return (count);
}

static void	freeall(char **splits)
{
	int		i;

	i = 0;
	while (splits[i])
	{
		free(splits[i]);
		i++;
	}
	free(splits);
}

static int	check_str(char **str, int j)
{
	if (str[j - 1] == NULL)
	{
		freeall(str);
		return (1);
	}
	return (0);
}

//size = i - start
//TRUE = no estamos dentro de comillas
//FALSE = estamos dentro de las comillas
char	**ft_bash_split(char const *s, char c, int *control, t_var_list **variable_list)
{
	int		i;
	int		j;
	int		start;
	int		end;
	char	**str;
	char	*content;

	i = 0;
	j = 0;
	str = ft_calloc(ft_count(s, c, control) + 1, sizeof(char *));
	if (!s || !str)
		return (NULL);
	//while recorriendo el input siempre que las comillas esten cerradas
	while(s[i] && (control[1] == TRUE && control[0] == TRUE))
	{
		//actualizamos el estado de los controles
		ignore_separator(s, control, &i);
		
		//si tenemos espacios al principo nos los saltamos
		while ((s[i] == c) && (control[1] == TRUE && control[0] == TRUE))
		{
			i++;
			ignore_separator(s, control, &i);
		}

		//Actualiamos start
		start = i;

		//Actualizamos end cuando encontramos un espacio que no este entre comillas
		while ((s[i] != c && s[i]) || (control[1] == FALSE || control[0] == FALSE))
		{
			i++;
			ignore_separator(s, control, &i);
		}
		end = i;

		if (( end > start))
		{
			ft_look_4_equal(s, start, end, variable_list);
			
			if (ft_look_4_dollar(s, start, end, variable_list, &content) == 0)
				str[j++] = content;
			else
				str[j++] = ft_substr(s, start, end - start);
				
			if (check_str(str, j))
				return (NULL);
		}
	}
	return (str);
}
