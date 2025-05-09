/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:54:32 by diana             #+#    #+#             */
/*   Updated: 2025/05/07 17:56:41 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*read_command_line(int mode)
{
	if (mode == 0)
		return (readline("\033[1;32mCBS$ \033[0m"));
	else
		return (get_next_line(0));
}
