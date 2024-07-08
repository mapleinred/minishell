/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsinexec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:51:41 by xzhang            #+#    #+#             */
/*   Updated: 2024/06/23 05:51:43 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_and_close(char *str, int fd)
{
	if (str)
		free(str);
	close(fd);
	set_up_signals();
	return (1);
}

void	print_heredoc_warning(char *delimiter)
{
	ft_putstr_fd("\nminishell: warning: here-document delimited by " \
	"end-of-file (wanted '", 1);
	ft_putstr_fd(delimiter, 1);
	ft_putstr_fd("')\n", 1);
}

int	handle_redirectionsinpipe(t_instr *instr, t_exitnum *exitnum)
{
	int		fd;
	int		i;

	i = 0;
	fd = 0;
	while (i < instr->redir_num)
	{
		if (instr->redir[i].type == 0)
			break ;
		else if (checkredirections(instr, i, fd) == 1)
		{
			free_resourcesinp(NULL, instr->mini, exitnum);
			return (1);
		}
		else if (instr->redir[i].type == 4)
		{
			if (dup2(instr->redir[i].heredoc_fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	handle_child_signals(int i)
{
	(void) i;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_sigint(int sig)
{
	(void) sig;
	write(1, "\n", 1);
}
