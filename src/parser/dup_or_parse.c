/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_or_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:19:33 by veronikalub       #+#    #+#             */
/*   Updated: 2026/01/11 19:20:41 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Хелперы для компактной обработки заголовков
void	dup_or_parse_texture(t_hdr_ctx *ctx, char *trim, bool *seen,
		const char *dup_msg)
{
	if (*seen)
	{
		free(trim);
		print_error_ctx(dup_msg, ctx, NULL);
	}
	*seen = true;
	parse_texture(trim, ctx);
}

void	dup_or_parse_resolution(t_hdr_ctx *ctx, char *trim, bool *seen)
{
	if (*seen)
	{
		free(trim);
		print_error_ctx("Duplicate R directive", ctx, NULL);
	}
	*seen = true;
	parse_resolution(trim, ctx->scene);
}

void	dup_or_parse_color(t_hdr_ctx *ctx, char *trim, bool *seen,
		const char *dup_msg)
{
	if (*seen)
	{
		free(trim);
		print_error_ctx(dup_msg, ctx, NULL);
	}
	*seen = true;
	parse_color(trim, ctx);
}
