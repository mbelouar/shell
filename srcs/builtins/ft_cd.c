/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:26 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/21 05:44:57 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cd_minus(t_data *data)
{
	char	*oldpwd_env;

	oldpwd_env = getenv("OLDPWD");
	if (oldpwd_env == NULL || chdir(oldpwd_env) == -1)
		return (0);
	change_pwd(data, NULL);
	return (1);
}

int	cd_alone(t_data *data)
{
	char	*home_env;

	home_env = getenv("HOME");
	if (home_env == NULL || chdir(home_env) == -1)
		return (0);
	change_pwd(data, NULL);
	return (1);
}

int	cd_path(char **args, t_data *data)
{
	if (chdir(args[1]) == -1)
		return (0);
	change_pwd(data, args[1]);
	return (1);
}

void	ft_cd(char **args, t_data *data)
{
	if (args[1] && args[2])
		return (error_sentence("cd: too many arguments\n"));
	else if (!args[1])
	{
		if (!cd_alone(data))
			return (error_sentence("cd: HOME: is undefined\n"));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (!cd_minus(data))
			return (error_sentence("cd: OLDPWD is undefined\n"));
	}
	else
	{
		if (!cd_path(args, data))
			return (error_sentence("cd: no such file or directory\n"));
	}
}
