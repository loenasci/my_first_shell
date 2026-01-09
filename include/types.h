/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:07:38 by lsarraci          #+#    #+#             */
/*   Updated: 2026/01/06 18:23:52 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef enum e_verbose				t_verbose;
typedef enum e_color_mode			t_color_mode;
typedef enum e_terminal_type		t_terminal_type;
typedef enum e_prompt_type			t_prompt_type;
typedef enum e_prompt_style			t_prompt_style;
typedef enum e_output_format		t_output_format;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_VARIABLE,
	TOKEN_AND,
	TOKEN_OR,
}	t_token_type;

typedef enum e_word_part_type
{
	PART_LITERAL,
	PART_SINGLE_QUOTE,
	PART_DOUBLE_QUOTE,
	PART_VARIABLE,
}	t_word_part_type;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
}	t_node_type;

enum e_output_format
{
	OUTPUT_FORMAT_PLAIN,
	OUTPUT_FORMAT_TABLE,
	OUTPUT_FORMAT_COLORED,
	OUTPUT_FORMAT_CSV,
	OUTPUT_FORMAT_HTML,
	OUTPUT_FORMAT_JSON,
	OUTPUT_FORMAT_XML,
}	;

enum e_prompt_type
{
	PROMPT_PRIMARY,
	PROMPT_SECONDARY,
	PROMPT_HEREDOC,
	PROMPT_QUOTE,
	PROMPT_DQUOTE,
	PROMPT_ERROR,
	PROMPT_COUNT,
	PROMPT_NONE,
	PROMPT_CUSTOM,
}	;

enum e_prompt_style
{
	PROMPT_STYLE_DEFAULT,
	PROMPT_STYLE_MINIMAL,
	PROMPT_STYLE_DETAILED,
	PROMPT_STYLE_FANCY,
}	;

enum	e_verbose
{
	VERBOSE,
	NONVERBOSE,
	OFF,
}	;

enum e_terminal_type
{
	TERMINAL_TYPE_DUMB,
	TERMINAL_TYPE_OTHER,
}	;

enum	e_color_mode
{
	COLOR_MODE_AUTO,
	COLOR_MODE_ALWAYS,
	COLOR_MODE_NEVER,
}	;

#endif