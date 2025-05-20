/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_at_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:31:49 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/20 18:33:43 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	copy_normal_token(char **tokens, char **new_tokens, int *i, int *j)
{
	new_tokens[(*j)++] = ft_strdup(tokens[*i]);
}

static void	toggle_quotes(char c, bool *squote, bool *dquote)
{
	if (c == '\'' && !(*dquote))
		*squote = !(*squote);
	else if (c == '"' && !(*squote))
		*dquote = !(*dquote);
}

static void	add_token_part(char *token, int start, int end, t_split_res r)
{
	char	*part;

	if (end > start)
	{
		part = ft_substr(token, start, end - start);
		(*(r.result))[(*(r.res_i))++] = part;
	}
}

static void	add_operator(char *token, int *i, t_split_res r)
{
	if (token[*i] == '>' && token[*i + 1] == '>')
	{
		(*(r.result))[(*(r.res_i))++] = ft_strdup(">>");
		(*i)++;
	}
	else if (token[*i] == '<' && token[*i + 1] == '<')
	{
		(*(r.result))[(*(r.res_i))++] = ft_strdup("<<");
		(*i)++;
	}
	else
	{
		(*(r.result))[(*(r.res_i))++] = ft_substr(token, *i, 1);
	}
}

void	split_token_at_operator(char *token, char ***result, int *res_i)
{
	int			i;
	int			start;
	bool		sq;
	bool		dq;
	t_split_res	r;

	r.result = result;
	r.res_i = res_i;
	i = 0;
	start = 0;
	sq = false;
	dq = false;
	while (token[i])
	{
		toggle_quotes(token[i], &sq, &dq);
		if (!sq && !dq && should_split_at(token, i))
		{
			add_token_part(token, start, i, r);
			add_operator(token, &i, r);
			start = i + 1;
		}
		i++;
	}
	if (token[start])
		(*(r.result))[(*(r.res_i))++] = ft_strdup(token + start);
}
