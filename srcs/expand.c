/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:04:54 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/17 10:44:52 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(const char *var_name, char **environ)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (strncmp(environ[i], var_name, strlen(var_name)) == 0
			&& environ[i][strlen(var_name)] == '=')
			return (environ[i] + strlen(var_name) + 1);
		// Retorna o valor após o '='
		i++;
	}
	return (NULL); // Se não encontrar
}

char *get_env_value(const char *name, char **environ)
{
	
}

char	*allocate_expansion_buffer(const char *s)
{
	char	*buffer;

	int len = strlen(s) + 128; // Inicial com margem para expansão.
	buffer = malloc(len);
	if (!buffer)
		exit(EXIT_FAILURE);
	return (buffer);
}

void	expand_exit_status(char *expanded, int *j, int exit_status)
{
	char	tmp[12];

	snprintf(tmp, sizeof(tmp), "%d", exit_status);
	for (int k = 0; tmp[k]; k++)
		expanded[(*j)++] = tmp[k];
}

char	*extract_variable_name(const char *start, const char **end)
{
	const char	*ptr = start;

	while (*ptr && (isalnum(*ptr) || *ptr == '_'))
		ptr++;
	*end = ptr;
	return (strndup(start, ptr - start));
}

void	append_variable_value(char *expanded, int *j, const char *var_value,
		int *len)
{
	while (*var_value)
	{
		if (*j >= *len - 1)
		{
			*len *= 2;
			expanded = realloc(expanded, *len);
			if (!expanded)
				exit(EXIT_FAILURE);
		}
		expanded[(*j)++] = *var_value++;
	}
}
char	*expand_variable(const char *s, char **environ, int exit_status)
{
	char		*expanded;
	int			i;
	int			j;
	int			len;
	const char	*end;
	char		*var_name;
	char		*var_value;

	i = 0;
	expanded = allocate_expansion_buffer(s);
	i = 0;
	j = 0;
	len = strlen(s) + 128;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1])
		{
			if (s[i + 1] == '?') // Caso para expansão do exit_status
			{
				expand_exit_status(expanded, &j, exit_status);
				// Expande o exit_status
				i += 2;
				// Avança para o próximo caractere após o ?
			}
			else
			{
				var_name = extract_variable_name(&s[i + 1], &end);
				if (!var_name)
				{
					free(expanded);
					exit(EXIT_FAILURE);
				}
				var_value = get_env_value(var_name, environ);
				free(var_name);
				if (var_value)
					append_variable_value(expanded, &j, var_value, &len);
				i = end - s;
			}
		}
		else
		{
			if (j >= len - 1)
			{
				len *= 2;
				expanded = realloc(expanded, len);
				if (!expanded)
					exit(EXIT_FAILURE);
			}
			expanded[j++] = s[i++];
		}
	}
	expanded[j] = '\0';
	return (expanded);
}
