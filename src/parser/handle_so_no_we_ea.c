/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_so_no_we_ea.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:16:51 by veronikalub       #+#    #+#             */
/*   Updated: 2026/01/02 14:43:35 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	handle_no(t_hdr_ctx *ctx, char *trim)
{
	if (ft_strncmp(trim, "NO", 2) == 0)
	{
		dup_or_parse_texture(ctx, trim, &ctx->seen_no,
			"Duplicate NO directive");
		return (1);
	}
	return (0);
}

int	handle_so(t_hdr_ctx *ctx, char *trim)
{
	if (ft_strncmp(trim, "SO", 2) == 0)
	{
		dup_or_parse_texture(ctx, trim, &ctx->seen_so,
			"Duplicate SO directive");
		return (1);
	}
	return (0);
}

int	handle_we(t_hdr_ctx *ctx, char *trim)
{
	if (ft_strncmp(trim, "WE", 2) == 0)
	{
		dup_or_parse_texture(ctx, trim, &ctx->seen_we,
			"Duplicate WE directive");
		return (1);
	}
	return (0);
}

int	handle_ea(t_hdr_ctx *ctx, char *trim)
{
	if (ft_strncmp(trim, "EA", 2) == 0)
	{
		dup_or_parse_texture(ctx, trim, &ctx->seen_ea,
			"Duplicate EA directive");
		return (1);
	}
	return (0);
}
