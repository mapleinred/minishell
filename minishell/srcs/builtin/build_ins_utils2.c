/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ins_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:10 by mertan            #+#    #+#             */
/*   Updated: 2024/04/10 11:53:13 by mertan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	append_env(t_instr *instr, char *str, int count)
{
	int		i;
	char	**tmp_env;

	tmp_env = (char **)malloc(sizeof(char *) * (count + 2));
	i = 0;
	while (instr->mini->e[i])
	{
		tmp_env[i] = ft_strdup(instr->mini->e[i]);
		i++;
	}
	tmp_env[i] = ft_strdup(str);
	tmp_env[i + 1] = NULL;
	free_env(instr->mini->e);
	instr->mini->e = tmp_env;
	instr->mini->env_count = i + 1;
}
