/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:55:02 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/21 10:15:04 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*DIANA NUEVO ARCHIVO
char	**ft_strjoin_arr(char *first, char **arr)
{
	int		i;
	int		len;
	char	**new_arr;

	len = 0;
	while (arr && arr[len])
		len++;
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	new_arr[0] = ft_strdup(first);
	i = 0;
	while (i < len)
	{
		new_arr[i + 1] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[len + 1] = NULL;
	free_arr(arr);
	return (new_arr);
}*/

static void	update_quote_flags(char c, bool *single, bool *double_q)
{
	if (c == '\'')
		*single = !(*single);
	else if (c == '"')
		*double_q = !(*double_q);
}

static void	add_token(char ***tokens, char *start, int *count)
{
	*tokens = realloc(*tokens, sizeof(char *) * (*count + 2));
	(*tokens)[*count] = ft_strdup(start);
	(*count)++;
	(*tokens)[*count] = NULL;
}

static void	handle_pipe_token(char ***tokens, char **start, char *p, int *count)
{
	char	tmp;
	char	pipe_str[2];

	if (p != *start)
	{
		tmp = *p;
		*p = '\0';
		add_token(tokens, *start, count);
		*p = tmp;
	}
	pipe_str[0] = *p;
	pipe_str[1] = '\0';
	add_token(tokens, pipe_str, count);
	*start = p + 1;
}

static void	process2_tokens(char *input, char ***tokens, bool *s_q, bool *d_q)
{
	int		count;
	char	*p;
	char	*start;

	count = 0;
	p = input;
	start = input;
	while (*p)
	{
		update_quote_flags(*p, s_q, d_q);
		if ((*p == ' ' || *p == '\t') && !(*s_q) && !(*d_q))
		{
			if (p != start)
			{
				*p = '\0';
				add_token(tokens, start, &count);
			}
			start = p + 1;
		}
		else if (*p == '|' && !(*s_q) && !(*d_q))
			handle_pipe_token(tokens, &start, p, &count);
		p++;
	}
	if (*start)
		add_token(tokens, start, &count);
}

/*
static void	process2_tokens(char *input, char ***tokens, bool *s_q, bool *d_q)
{
	int		count;
	char	*p;
	char	*start;
	char	tmp;

	count = 0;
	start = input;
	p = input;
	while (*p)
	{
		update_quote_flags(*p, s_q, d_q);
		if ((*p == ' ' || *p == '\t') && !(*s_q) && !(*d_q))
		{
			if (p != start)
			{
				*p = '\0';
				add_token(tokens, start, &count);
			}
			start = p + 1;
		}
		else if (*p == '|' && !(*s_q) && !(*d_q))
		{
			if (p != start)
			{
				tmp = *p;
				*p = '\0';
				add_token(tokens, start, &count);
				*p = tmp;
			}
			char	pipe_str[2] = {*p, '\0'};
			add_token(tokens, pipe_str, &count);
			start = p + 1;
		}
		p++;
	}
	if (*start)
		add_token(tokens, start, &count);
}*/

char	**tokenize_quotes(char *input)
{
	char	**tokens;
	bool	single_q;
	bool	double_q;

	tokens = NULL;
	single_q = false;
	double_q = false;
	process2_tokens(input, &tokens, &single_q, &double_q);
	return (tokens);
}
