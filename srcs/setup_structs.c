/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:10:17 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/27 17:22:07 by ahamuyel         ###   ########.fr       */
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
	token->expanded = NULL;
	token->word = NULL;
}
