/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocinpipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 05:44:37 by xzhang            #+#    #+#             */
/*   Updated: 2024/06/23 05:44:40 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signalinpipeheredocs(struct sigaction *sa)
{
	sa->sa_handler = handle_sigint1;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGINT, sa, NULL);
}

int	is_heredoc_end(char *delimiter, char *str)
{
	if (!str)
		return (0);
	if (ft_strlen(delimiter) == ft_strlen(str) - 1 \
	&&ft_strncmp(str, delimiter, ft_strlen(delimiter)) == 0)
	{
		free(str);
		return (1);
	}
	return (0);
}

int	heredoc_loop(int pipefd, t_instr *instr, int j, t_exitnum *exitnum)
{
	char	*str;
	char	*expand;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(instr->mini->pipe->orgstdin);
		if (g_exit == 1)
			return (get_next_line(-1), free_and_close(str, pipefd));
		if (!str)
		{
			print_heredoc_warning(instr->redir[j].str);
			break ;
		}
		if (is_heredoc_end(instr->redir[j].str, str))
			break ;
		expand = expand_var(str, instr->mini, exitnum);
		write(pipefd, expand, ft_strlen(expand));
		free(expand);
	}
	get_next_line(-1);
	return (0);
}

int	handle_heredocinpipe(t_instr *instr, int j, t_exitnum *exitnum)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	instr->redir[j].heredoc_fd = dup(pipefd[0]);
	close(pipefd[0]);
	if (heredoc_loop(pipefd[1], instr, j, exitnum) == 1)
		return (1);
	close(pipefd[1]);
	return (0);
}

int	open_all_heredocs(t_mini *mini, t_exitnum *exitnum)
{
	int					i;
	int					j;
	struct sigaction	sa;

	i = -1;
	signalinpipeheredocs(&sa);
	while (++i < mini->instr_num)
	{
		j = -1;
		while (++j < mini->instr[i].redir_num)
		{
			if (mini->instr[i].redir[j].type == 4)
			{
				if (handle_heredocinpipe(&mini->instr[i], j, exitnum) == 1)
					return (1);
			}
		}
	}
	return (0);
}
/*
int	open_all_heredocs(t_mini *mini)
{
	int					i;
	int					j;
	char				*str;
	int					pipefd[2];
	struct sigaction	sa;

	i = -1;
	sa.sa_handler = handle_sigint1;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	while (++i < mini->instr_num)
	{
		j = -1;
		while (++j < mini->instr[i].redir_num)
		{
			if (mini->instr[i].redir[j].type == 4)
			{
				if (pipe(pipefd) == -1)
					perror("pipe");
				mini->instr[i].redir[j].heredoc_fd = dup(pipefd[0]);
				close(pipefd[0]);
				while (1)
				{
					ft_putstr_fd("> ", 1);
					str = get_next_line(mini->pipe->orgstdin);
					if (g_exit == 1)
					{
						if (str)
							free(str);
						close(pipefd[1]);
						set_up_signals();
						return (1);
					}
					if (!str || (((ft_strlen(mini->instr[i].redir[j].str)) \
					== ft_strlen(str) - 1) && (ft_strncmp(str, \
					mini->instr[i].redir[j].str, ft_strlen\
					(mini->instr[i].redir[j].str)) == 0)))
					{
						if (str)
							free(str);
						break ;
					}
					write(pipefd[1], str, ft_strlen(str));
					free(str);
				}
				close(pipefd[1]);
			}
		}
	}
	get_next_line(-1);
	return (0);
}*/
