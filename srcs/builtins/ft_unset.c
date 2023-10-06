/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:43 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/21 05:54:51 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env(char **env)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = envlen(env);
	while (i < env_len)
		free(env[i++]);
	free(env);
}

char	**delete_env_var(char **old_env, int index)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (envlen(old_env) - 1));
	if (!new_env)
		exit(EXIT_FAILURE);
	while (old_env[i])
	{
		if (i != index)
		{
			new_env[j] = ft_strdup(old_env[i]);
			j++;
		}
		i++;
	}
	free_env(old_env);
	i--;
	new_env[i] = NULL;
	return (new_env);
}

void	ft_unset(char **args, t_data *data)
{
	int	i;
	int	index;

	i = 1;
	while (args[i])
	{
		if (check_export(args[i]))
		{
			index = var_index(args[i], data);
			if (index > 0)
				data->env = delete_env_var(data->env, index);
			i++;
		}
		else
			return (error_sentence("unset: invalid identifier\n"));
	}
}
