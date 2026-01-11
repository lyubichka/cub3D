/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_kind_validate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:09:14 by veronikalub       #+#    #+#             */
/*   Updated: 2026/01/11 19:44:18 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	handle_kind_result(int kind, char *trim)
{
	if (kind == -1)
	{
		free(trim);
		return (-1);
	}
	if (kind > 0)
	{
		free(trim);
		return (kind);
	}
	return (0);
}

void	validate_after_header(t_hdr_ctx *ctx)
{
	if (ctx->map_start == -1)
		print_error_ctx("Map section not found", ctx, NULL);
	if (!ctx->seen_no || !ctx->seen_so || !ctx->seen_we
		|| !ctx->seen_ea || !ctx->seen_f || !ctx->seen_c)
		print_error_ctx("Missing one or more directives before map", ctx, NULL);
}
