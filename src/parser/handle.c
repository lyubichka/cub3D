/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:24:14 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/18 17:13:27 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int try_handle_texture_ids(t_hdr_ctx *ctx, char *trim)
{
    int handled;

    handled = handle_no(ctx, trim);
    if (!handled)
        handled = handle_so(ctx, trim);
    if (!handled)
        handled = handle_we(ctx, trim);
    if (!handled)
        handled = handle_ea(ctx, trim);
    if (!handled)
        handled = handle_s(ctx, trim);
    return (handled);
}

static int try_handle_rfc_ids(t_hdr_ctx *ctx, char *trim)
{
    if (trim[0] == 'R')
    {
        dup_or_parse_resolution(ctx, trim, &ctx->seen_r);
        return (1);
    }
    if (trim[0] == 'F')
    {
        dup_or_parse_color(ctx, trim, &ctx->seen_f,
            "Duplicate F directive");
        return (1);
    }
    if (trim[0] == 'C')
    {
        dup_or_parse_color(ctx, trim, &ctx->seen_c,
            "Duplicate C directive");
        return (1);
    }
    return (0);
}

void handle_header_trim_ctx(t_hdr_ctx *ctx, char *trim)
{
    int handled;

    handled = try_handle_texture_ids(ctx, trim);
    if (!handled)
        handled = try_handle_rfc_ids(ctx, trim);
    if (!handled)
    {
        free(trim);
        free_split(ctx->lines);
        print_error("Unknown identifier in header");
    }
}