/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:40 by diana             #+#    #+#             */
/*   Updated: 2025/05/07 15:10:24 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    join_quoted_values(char **cmd, char **value)
{
        int             i;
        char    *temp;

        i = 0;
        while (cmd[i])
        {
                temp = ft_strjoin(*value, " ");
                free(*value);
                *value = ft_strjoin(temp, cmd[i]);
                free(temp);
                i++;
        }
}

void    assign_value(char **cmd, char **value)
{
        char    *tmp;

        tmp = ft_strdup(cmd[1]);
        *value = tmp;
        free(tmp);
}

void    add_new_variable(t_env *env_mini, char **tokens, t_env *new_var)
{
        if (!tokens || !tokens[0] || !new_var)
                return ;
        join_cmd_values(tokens, &new_var->value);
        delete_quotes(new_var->value);
        new_var->next = NULL;
        
        if (!env_mini)
                return;
                
        while (env_mini->next)
                env_mini = env_mini->next;
        env_mini->next = new_var;
}

static int      is_invalid_identifier(char *tokens)
{
        if (!tokens || !*tokens || !is_valid_variable_name(tokens))
        {
                ft_putstr_fd("export: `", 2);
                ft_putstr_fd(tokens, 2);
                ft_putstr_fd("': not a valid identifier\n", 2);
                return (1);
        }
        return (0);
}

int     ft_export(t_env *env_mini, char **cmd)
{
        char    **tokens;
        int             i;
        t_env   *new_var;

        i = 1;
        if (!cmd || !cmd[1])
                return (1);
        while (cmd[i])
        {
                if (is_invalid_identifier(cmd[i]))
                        return (1);
                tokens = get_tokens(cmd[i]);
                if (!env_mini || !update_existing_variable(env_mini, tokens))
                {
                        new_var = malloc(sizeof(t_env));
                        if (!new_var)
                                return (1);
                        init_new_variable(new_var, tokens);
                        if (env_mini)
                        {
                                add_new_variable(env_mini, tokens, new_var);
                        }
                        else
                        {
                                // We can't modify env_mini directly since it's passed by value
                                // This is a limitation - we need to handle this at a higher level
                                free(new_var->variable);
                                free(new_var->value);
                                free(new_var);
                                free_arr(tokens);
                                return (1);
                        }
                }
                free_arr(tokens);
                i++;
        }
        return (0);
}
