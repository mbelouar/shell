/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:23:08 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/19 20:23:08 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_export(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) || str[i] == '=')    // Check if the string starts with a digit.
		return (0);    // Invalid: Starts with a digit.
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')     // Check if the character is not alphanumeric and not an underscore.
			return (0);    // Invalid: Contains a non-alphanumeric character.
		i++;
	}
	return (1);      // Valid exportable variable.
}

int	print_export(char **env)
{
	int	i;
	int	j;
	int	equal;

	i = -1;
	while (env[++i])
	{
		equal = 1;
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][j])
		{
			if (env[i][j] == '\\' || env[i][j] == '$' || env[i][j] == '\"')
				write(1, "\\", 1);       //escapes special characters by adding a backslash before them
			write(1, &env[i][j], 1);
			if (env[i][j] == '=' && equal-- == 1)
				write(1, "\"", 1);
			j++;
		}
		if (equal != 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
	return (1);
}

char	**dup_env(char **env)
{
	char	**data_env;
	int		i;

	i = 0;
	data_env = ft_calloc((envlen(env) + 1), sizeof(char*));
	if (!data_env)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		data_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (data_env);
}
