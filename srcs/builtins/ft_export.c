/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:37 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/04 00:12:49 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	var_index(char *name, t_data *data)
{
	int		j;
	int		i;

	i = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j] && data->env[i][j] == name[j]
		&& name[j] != '\0' && name[j] != '=' &&
		data->env[i][j] != '\0' && data->env[i][j] != '=')
			j++;
		if ((data->env[i][j] == '\0' || data->env[i][j] == '=') &&
		(name[j] == '\0' || name[j] == '='))
			return (i);
		i++;
	}
	return (-1);
}

void	replace_var(char *new_var, t_data *data, int index)
{
	if (ft_strchr(new_var, '='))
	{
		free(data->env[index]);
		data->env[index] = ft_strdup(new_var);
	}
}

char	**export_env(char **old_env, char *export)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = ft_calloc((envlen(old_env) + 2), sizeof(char *));
	if (!new_env)
		exit(EXIT_FAILURE);
	while (old_env[i])
	{
		new_env[i] = ft_strdup(old_env[i]);
		i++;
	}
	free_env(old_env);
	new_env[i] = ft_strdup(export);
	return (new_env);
}

void	export_alone(t_data *data)
{
	int		i;
	int		j;
	char	**tmp_env;
	char	*swap;

	i = 0;
	tmp_env = dup_env(data->env);
	while (tmp_env[i + 1])
	{
		j = i + 1;
		if (ft_strcmp(tmp_env[i], tmp_env[j]) > 0)
		{
			swap = tmp_env[j];
			tmp_env[j] = tmp_env[i];
			tmp_env[i] = swap;
			i = 0;
		}
		else
			i++;
	}
	print_export(tmp_env);
	free_env(tmp_env);
}

void	ft_export(char **args, t_data *data)
{
	int	i;
	int	index;

	i = 1;
	if (args[i])
	{
		while (args[i])
		{
			index = var_index(args[i], data);
			if (check_export(args[i]))
			{
				if (index >= 0)
					replace_var(args[i], data, index);
				else
				{   // The variable doesn't exist, add it to the environment.
					data->env = export_env(data->env, args[i]);
					if (!data->env)
						exit(EXIT_FAILURE);
				}
			}
			else
				return (error_sentence("export: not a valid identifier\n"));
			i++;
		}
	}
	else
		export_alone(data);
}

