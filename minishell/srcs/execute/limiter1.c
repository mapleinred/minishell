/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*     limiter1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:38:14 by xzhang            #+#    #+#             */
/*   Updated: 2024/06/23 05:38:17 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	limiter(char *limiter, int *fd, t_mini *mini, t_exitnum *exitnum)
{
	char	*input;
	char	*expand;

	while (1)
	{
		ft_putstr_fd("> ", 2);
		input = get_next_line(mini->pipe->orgstdin);
		if (g_exit == 1)
			return (f_n_c(input, fd[1], mini, exitnum));
		if (!input)
		{
			print_heredocwarninginp(limiter, input, mini, exitnum);
			break ;
		}
		if (check_heredocdelimiterinp(input, limiter))
		{
			free_resourcesinp(input, mini, exitnum);
			break ;
		}
		expand = expand_var(input, mini, exitnum);
		write(fd[1], expand, ft_strlen(expand));
		free(expand);
	}
	close(fd[0]);
	return (0);
}

// void	handle_sigint(int sig)
// {
// 	(void) sig;
// 	write(1, "\n", 1);
// }
