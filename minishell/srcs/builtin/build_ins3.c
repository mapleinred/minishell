/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/04/10 11:53:13 by mertan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_export_error(t_instr *instr, char *var, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_isdigit(var[0]) == 1 || var[0] == '\0')
	{
		tmp = ft_strjoin(str, ": export: not a valid identifier");
		ft_error(instr->mini, tmp, 1);
		free(tmp);
		free(var);
		return (1);
	}
	while (var[i])
	{
		if (ft_isalnumus(var[i]) == 0)
		{
			tmp = ft_strjoin(str, ": export: not a valid identifier");
			ft_error(instr->mini, tmp, 1);
			free(tmp);
			free(var);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export_exec_f1(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i);
}

int	ft_export_exec(t_instr *instr, char *str)
{
	int		i;
	int		exit_num;
	char	*var;

	i = 0;
	var = NULL;
	exit_num = 0;
	i = ft_export_exec_f1(str, i);
	var = ft_substr(str, 0, i);
	exit_num = ft_export_error(instr, var, str);
	if (exit_num != 0)
		return (exit_num);
	if (check_env(str, var, instr) == 0)
		append_env(instr, str, instr->mini->env_count);
	free(var);
	return (0);
}

void	ft_export_nq(t_instr *instr)
{
	char	**vars;
	int		i;

	i = 0;
	vars = ft_split(instr->arg, ' ');
	while (vars[i])
	{
		ft_export_exec(instr, vars[i]);
		free(vars[i]);
		vars[i] = NULL;
		i++;
	}
	free(vars);
}

int	check_omitspaces(t_instr *instr)
{
	char	*str;
	int		i;
	int		flag;
	int		count;

	i = 0;
	flag = 0;
	count = 0;
	str = instr->mini->input;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			flag = 1;
		if (flag == 1 && str[i] == ' ')
			count++;
		i++;
	}
	return (count);
}
