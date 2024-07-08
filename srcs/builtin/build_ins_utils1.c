/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ins_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/04/10 11:53:13 by mertan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sort_env_ascii(char **env, int env_count)
{
	int		i;
	int		j;

	i = 0;
	while (i + 1 < env_count && env[i])
	{
		j = 0;
		while (env[i][j] && env[i + 1][j])
		{
			if (env[i][j] > env[i + 1][j])
			{
				ft_swap(&env[i], &env[i + 1]);
				i = -1;
				break ;
			}
			else if (env[i][j] < env[i + 1][j])
				break ;
			j++;
		}
		i++;
	}
	find_var_str(env);
}

void	find_var_str(char **env)
{
	int		i;
	int		varlen;
	char	*var;
	char	*value;

	i = -1;
	while (env[++i])
	{
		value = NULL;
		varlen = 0;
		while (env[i][varlen])
		{
			if (env[i][varlen] == '=')
				break ;
			varlen++;
		}
		var = ft_substr(env[i], 0, varlen);
		if (varlen != (int)ft_strlen(env[i]))
			value = env[i] + varlen + 1;
		if (value)
			printf("declare -x %s=\"%s\"\n", var, value);
		else
			printf("declare -x %s\n", var);
		free(var);
	}
}

void	ft_exit_a(t_mini *mini, int i)
{
	free_mini(mini);
	exit (i);
}

void	ft_exit_sign(t_instr *instr)
{
	int	i;

	i = 1;
	while (instr->arg[i])
	{
		if (instr->arg[i] == '+' || instr->arg[i] == '-')
		{
			printf("exit: numeric argument required\n");
			ft_exit_a(instr->mini, 2);
		}
		i++;
	}
}

int	ft_unset_exec(t_instr *instr, char *str)
{
	char	**new_e;
	int		i;
	int		j;

	i = instr->mini->env_count;
	j = 0;
	new_e = (char **)malloc(sizeof(char *) * (i + 2 - 1));
	i = 0;
	while (instr->mini->e[i])
	{
		if (ft_strncmp(instr->mini->e[i], str, ft_strlen(str)) != 0)
		{
			new_e[j] = ft_strdup(instr->mini->e[i]);
			j++;
		}
		i++;
	}
	free_env(instr->mini->e);
	instr->mini->e = new_e;
	new_e[j] = NULL;
	instr->mini->env_count = j;
	return (0);
}
