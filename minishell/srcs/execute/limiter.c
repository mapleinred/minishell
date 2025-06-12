/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*     limiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:38:14 by xzhang            #+#    #+#             */
/*   Updated: 2024/06/23 05:38:17 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_heredocwarninginp(char *limiter, char *input, \
	t_mini *mini, t_exitnum *exitnum)
{
	ft_putstr_fd("\nminishell: warning: here-document delimited by " \
	"end-of-file (wanted '", 1);
	ft_putstr_fd(limiter, 1);
	ft_putstr_fd("')\n", 1);
	free_resourcesinp(input, mini, exitnum);
}

int	check_heredocdelimiterinp(char *input, char *limiter)
{
	return ((ft_strlen(input) - 1 == ft_strlen(limiter)) \
	&& (ft_strncmp(input, limiter, ft_strlen(limiter)) == 0));
}

void	free_resourcesinp(char *input, t_mini *mini, t_exitnum *exitnum)
{
	if (input)
		free(input);
	free_env(mini->e);
	free_mini(mini);
	free(exitnum);
	get_next_line(-1);
}

int	f_n_c(char *str, int fd, t_mini *mini, t_exitnum *exitnum)
{
	close(fd);
	free_resourcesinp(str, mini, exitnum);
	set_up_signals();
	return (1);
}

void	handle_sigint2(int sig)
{
	(void) sig;
	g_exit = 1;
}
