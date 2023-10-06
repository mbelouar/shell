/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:34 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/04 22:06:03 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_sentence(char *str)
{
	ft_putstr_fd(str, 2);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **args)
{
	if (!args[1])
		exit(0);
	if (!is_number(args[1]))
	{
		error_sentence("exit: numeric argument required\n");
		exit(255);
	}
	else if (is_number(args[1]) && args[2])
		return (error_sentence("exit: too many arguments\n"));
	else if (is_number(args[1]))
		exit(ft_atoi(args[1]));
}
