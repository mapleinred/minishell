/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:51:23 by xzhang            #+#    #+#             */
/*   Updated: 2024/06/26 17:51:37 by xzhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit;

void	init_mini_instr(t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	while (i < 64)
	{
		mini->instr[i].cmd_arr = NULL;
		mini->instr[i].cmd = NULL;
		mini->instr[i].arg = NULL;
		mini->instr[i].mini = mini;
		j = 0;
		while (j < 64)
		{
			mini->instr[i].redir[j].str = NULL;
			mini->instr[i].redir[j].type = 0;
			mini->instr[i].redir[j].heredoc_fd = -1;
			j++;
		}
		mini->instr[i].redir_num = 0;
		i++;
	}
}

void	init_mini(t_mini *mini)
{
	int	i;

	i = 0;
	mini->input = NULL;
	while (i < 128)
	{
		mini->tkn[i].mini = mini;
		mini->tkn[i].str = NULL;
		mini->tkn[i].type = 0;
		i++;
	}
	mini->tks_num = 0;
	init_mini_instr(mini);
	mini->instr_num = 0;
	mini->exit_status = 0;
}

//duplicate envp
void	init_env(t_mini *mini, char *envp[])
{
	int		i;
	char	*s;
	int		value;

	i = 0;
	ft_memset(mini, 0, sizeof(t_mini));
	while (envp[i])
		i++;
	mini->env_count = i;
	mini->e = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i] != NULL)
	{
		mini->e[i] = ft_strdup(envp[i]);
		if (ft_strncmp(mini->e[i], "SHLVL", 5) == 0)
		{
			value = ft_atoi(&mini->e[i][6]);
			s = ft_itoa(value + 1);
			free(mini->e[i]);
			mini->e[i] = ft_strjoin("SHLVL=", s);
			free(s);
		}
		i++;
	}
	mini->e[i] = NULL;
}

void	run_mini(t_mini *mini, t_exitnum *exitnum)
{
	if (mini->input == NULL)
	{
		free_env(mini->e);
		free_mini(mini);
		free(exitnum);
		printf("exit\n");
		exit (0);
	}
	if (g_exit != 0)
	{
		exitnum->num = 130;
		g_exit = 0;
	}
	add_history(mini->input);
	make_tkn(mini);
	if (mini->exit_status == 0)
		parse_tkn(mini, exitnum);
	if (mini->exit_status == 0)
		create_instr(mini);
	if (mini->exit_status == 0)
		exec_instr(mini, exitnum);
	if (mini->exit_status >= 0)
		exitnum->num = mini->exit_status;
}

int	main(int ac, char **av, char *envp[])
{
	t_mini		mini;
	t_exitnum	*exitnum;

	(void)ac;
	(void)av;
	init_env(&mini, envp);
	exitnum = (t_exitnum *)malloc(sizeof(t_exitnum));
	if (!exitnum)
		exitnum = NULL;
	exitnum->num = 0;
	g_exit = 0;
	while (1)
	{
		init_mini(&mini);
		init_sighandler(&mini);
		initfd(&mini);
		mini.input = readline("Minishell: ");
		run_mini(&mini, exitnum);
		restorefd(&mini);
		free_mini(&mini);
	}
	free(exitnum);
}
/*
// tkns print test
int i = 0;
while (i < mini->tks_num)
{
	printf("tkn[%d]: %s, type: %d\n", i, mini->tkn[i].str, \
	mini->tkn[i].type);
	i++;
}
printf("instr_num: %d\n", mini->instr_num);

	// instr print test
	i = 0;
	while (i < mini->instr_num)
	{
		printf("cmd[%d]: %s, arg: %s\n", i, mini->instr[i].cmd, \
		mini->instr[i].arg);
		int k = 0;
		while (k < mini->instr[i].redir_num)
		{
			printf("redir[%d]: %d, %s\n", k, mini->instr[i].redir[k].type, \
			mini->instr[i].redir[k].str);
			k++;
		}
		i++;
	}*/