/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:32 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/21 05:46:16 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	envlen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (++i);
}

void	ft_env(char **env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env[i])
	{
		str = ft_strchr(env[i], '=');
		if (str)
		{
			j = 0;
			while (env[i][j])
			{
				write(1, &env[i][j], 1);
				j++;
			}
			ft_putchar('\n');
		}
		i++;
	}
}
