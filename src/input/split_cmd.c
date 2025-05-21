/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:27:15 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/21 10:16:08 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	should_split_at(char *token, int i)
{
	if (!is_operator_char(token[i]))
		return (0);
	if (token[i] == '|')
		return (1);
	if (i == 0)
		return (0);
	if (((token[i] == '>' && token[i + 1] == '>') || \
		(token[i] == '<' && token[i + 1] == '<')) && ft_strlen(token) > 1)
		return (1);
	if (i > 0 && ((token[i - 1] == '>' && token[i] == '>') || \
			(token[i - 1] == '<' && token[i] == '<')))
		return (0);
	return (1);
}

static int	count_tokens_after_split(char *token)
{
	int		i;
	int		count;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	count = 1;
	in_single_quote = false;
	in_double_quote = false;
	while (token[i])
	{
		if (token[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (token[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (!in_single_quote && !in_double_quote && should_split_at(token, i))
			count += 2;
		i++;
	}
	return (count);
}

static int	count_total_tokens(char **tokens, bool *has_op)
{
	int	i;
	int	total;
	int	count;

	i = 0;
	total = 0;
	*has_op = false;
	while (tokens[i])
	{
		count = count_tokens_after_split(tokens[i]);
		total += count;
		if (count > 1)
			*has_op = true;
		i++;
	}
	return (total);
}

static void	fill_result(char **tokens, t_split_ctx *ctx)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (count_tokens_after_split(tokens[i]) > 1)
			split_token_at_operator(tokens[i], &ctx->result, &ctx->index);
		else
			ctx->result[(ctx->index)++] = ft_strdup(tokens[i]);
		i++;
	}
	ctx->result[ctx->index] = NULL;
}

char	**split_tokens_with_operators(char **tokens)
{
	int				total;
	bool			has_op;
	t_split_ctx		ctx;

	total = count_total_tokens(tokens, &has_op);
	if (!has_op)
		return (tokens);
	ctx.result = calloc(total + 1, sizeof(char *));
	if (!ctx.result)
		return (tokens);
	ctx.index = 0;
	fill_result(tokens, &ctx);
	free_arr(tokens);
	return (ctx.result);
}
