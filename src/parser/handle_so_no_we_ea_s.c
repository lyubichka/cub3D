/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_so_no_we_ea_s.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:16:51 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/16 15:17:30 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int handle_no(t_hdr_ctx *ctx, char *trim)
{
    if (ft_strncmp(trim, "NO", 2) == 0)
    {
        dup_or_parse_texture(ctx, trim, &ctx->seen_no,
            "Duplicate NO directive");
        return (1);
    }
    return (0);
}

int handle_so(t_hdr_ctx *ctx, char *trim)
{
    if (ft_strncmp(trim, "SO", 2) == 0)
    {
        dup_or_parse_texture(ctx, trim, &ctx->seen_so,
            "Duplicate SO directive");
        return (1);
    }
    return (0);
}

int handle_we(t_hdr_ctx *ctx, char *trim)
{
    if (ft_strncmp(trim, "WE", 2) == 0)
    {
        dup_or_parse_texture(ctx, trim, &ctx->seen_we,
            "Duplicate WE directive");
        return (1);
    }
    return (0);
}

int handle_ea(t_hdr_ctx *ctx, char *trim)
{
    if (ft_strncmp(trim, "EA", 2) == 0)
    {
        dup_or_parse_texture(ctx, trim, &ctx->seen_ea,
            "Duplicate EA directive");
        return (1);
    }
    return (0);
}

int handle_s(t_hdr_ctx *ctx, char *trim)
{
    if (ft_strncmp(trim, "S ", 2) == 0 || ft_strncmp(trim, "S\t", 2) == 0)
    {
        dup_or_parse_texture(ctx, trim, &ctx->seen_s,
            "Duplicate S directive");
        return (1);
    }
    return (0);
}