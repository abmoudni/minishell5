/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtawil <mtawil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 18:42:12 by mtawil            #+#    #+#             */
/*   Updated: 2025/12/06 17:29:32 by mtawil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_operator_start(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

char	*get_operator_token(const char *line, int *i)
{
	char	*token;

	if ((line[*i] == '>' && line[*i + 1] == '>') || (line[*i] == '<'
			&& line[*i + 1] == '<'))
	{
		token = ft_strndup(line + *i, 2);
		*i += 2;
		return (token);
	}
	token = ft_strndup(line + *i, 1);
	(*i)++;
	return (token);
}

t_tokens	*create_token(char *str, int fla)
{
	t_tokens	*new;
	char		*tmp;

	if (!str)
		return (NULL);
	new = malloc(sizeof(t_tokens));
	if (!new)
	{
		free(str);
		return (NULL);
	}
	tmp = remove_quotes(str);
	if (!tmp)
	{
		free(new);
		free(str);
		return (NULL);
	}
	new->value = tmp;
	free(str);
	new->flag = fla;
	new->next = NULL;
	return (new);
}

void	add_token(t_tokens **head, t_tokens *new_token)
{
	t_tokens	*tmp;

	if (!new_token)
		return ;
	if (!*head)
		*head = new_token;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

void	print_tokens(t_tokens *head)
{
	t_tokens	*current;

	current = head;
	while (current)
	{
		printf("(type=%s)\n", current->value);
		printf("(type=%d)\n", current->flag);
		current = current->next;
	}
}
