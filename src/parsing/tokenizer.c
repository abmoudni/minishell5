/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtawil <mtawil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:45:36 by mtawil            #+#    #+#             */
/*   Updated: 2025/12/06 17:29:37 by mtawil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_word_token(const char *line, int *i)
{
	int		start;
	char	c;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && !is_operator_start(line[*i]))
	{
		if (line[*i] == '"' || line[*i] == '\'')
		{
			c = line[*i];
			(*i)++;
			while (line[*i] && line[*i] != c)
				(*i)++;
			if (line[*i] == c)
				(*i)++;
		}
		else
			(*i)++;
	}
	return (ft_strndup(line + start, *i - start));
}

void	check_token(t_tokens *tokens)
{
	while (tokens)
	{
		if (ft_strcmp(tokens->value, "<") == 0)
			tokens->type = REDIR_IN;
		else if (ft_strcmp(tokens->value, ">") == 0)
			tokens->type = REDIR_OUT;
		else if (ft_strcmp(tokens->value, ">>") == 0)
			tokens->type = REDIR_APPEND;
		else if (ft_strcmp(tokens->value, "<<") == 0)
			tokens->type = REDIR_HEREDOC;
		else if (ft_strcmp(tokens->value, "|") == 0)
			tokens->type = TOKEN_PIPE;
		else
			tokens->type = TOKEN_WORD;
		tokens = tokens->next;
	}
}

t_tokens	*parse_tokens(const char *line, int *i, int *size)
{
	t_tokens	*tokens;
	t_tokens	*new_tok;
	char		*tok;

	tokens = NULL;
	while (line[*i])
	{
		while (ft_isspace(line[*i]))
			(*i)++;
		if (!line[*i])
			break ;
		if (is_operator_start(line[*i]))
			tok = get_operator_token(line, i);
		else
			tok = get_word_token(line, i);
		if (!tok)
			break ;
		new_tok = create_token(tok, 0);
		if (!new_tok)
			break ;
		add_token(&tokens, new_tok);
		(*size)++;
	}
	return (tokens);
}

t_tokens	*tokenize(const char *line, int *size)
{
	int			i;
	t_tokens	*tokens;

	i = 0;
	*size = 0;
	tokens = parse_tokens(line, &i, size);
	if (tokens)
		check_token(tokens);
	return (tokens);
}
