/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:03:53 by cosmos            #+#    #+#             */
/*   Updated: 2025/05/07 14:59:11 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*allocate_cleaned_token(char *token)
{
	char	*cleaned_token;

	cleaned_token = malloc(ft_strlen(token) + 1);
	if (!cleaned_token)
		return (NULL);
	return (cleaned_token);
}

void	copy_char_or_space(char *cleaned_token, char token_char, \
	int *k, int *space_found)
{
	if (token_char != ' ')
	{
		cleaned_token[*k] = token_char;
		(*k)++;
		*space_found = 0;
	}
	else if (!(*space_found))
	{
		cleaned_token[*k] = ' ';
		(*k)++;
		*space_found = 1;
	}
}

char	*clean_space(char *token)
{
	int		j;
	int		k;
	int		space_found;
	char	*cleaned_token;

	j = 0;
	k = 0;
	space_found = 0;
	cleaned_token = allocate_cleaned_token(token);
	if (!cleaned_token)
		return (NULL);
	while (token[j])
	{
		copy_char_or_space(cleaned_token, token[j], &k, &space_found);
		j++;
	}
	cleaned_token[k] = '\0';
	return (cleaned_token);
}

void	init_new_variable(t_env *new_var, char **tokens)
{
	char	*cleaned_value;

	new_var->variable = ft_strdup(tokens[0]);
	if (tokens[1])
	{
		cleaned_value = clean_space(tokens[1]);
		new_var->value = cleaned_value;
		free(cleaned_value);
	}
	else
		new_var->value = ft_strdup("");
}

int	is_valid_variable_name(char *name)
{
	int	i;

	if (name == NULL || name[0] == '\0')
		return (0);
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!(ft_isalpha(name[i]) || ft_isdigit(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
