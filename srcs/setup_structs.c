/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:10:17 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/02/03 19:57:27 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_state(t_parse *state)
{
	state->in_single_quote = 0;
	state->in_double_quote = 0;
	state->i = 0;
	state->j = 0;
}

void	init_token(t_token *token)
{
	token->tokens = malloc(sizeof(char *) * 50);
	token->expanded = NULL;
	token->word = NULL;
}

void	init_path(t_path *path_info)
{
	path_info->exit_status = 0;
	path_info->full_path = NULL;
	path_info->cmd_path = NULL;
	path_info->directories = NULL;
	path_info->environ = NULL;
}

void	init_process(t_process *process)
{
	process->prev_fd = 0;
	process->i = 0;
}
