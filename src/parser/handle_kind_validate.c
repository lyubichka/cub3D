/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_kind_validate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:09:14 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/24 13:13:19 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int handle_kind_result(int kind, char *trim)
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

void validate_after_header(t_hdr_ctx *ctx)
{
    if (ctx->map_start == -1)
    {
        free_split(ctx->lines);
        print_error("Map section not found");
    }
    if (!ctx->seen_r || !ctx->seen_no || !ctx->seen_so || !ctx->seen_we
        || !ctx->seen_ea || !ctx->seen_f || !ctx->seen_c)
    {
        free_split(ctx->lines);
        print_error("Missing one or more directives (R, NO, SO, WE, EA, F, C) before map");
    }
}
