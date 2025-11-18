/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_or_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:19:33 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/16 15:20:18 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Хелперы для компактной обработки заголовков
void dup_or_parse_texture(t_hdr_ctx *ctx, char *trim, bool *seen,
        const char *dup_msg)
{
    if (*seen)
    {
        free(trim);
        free_split(ctx->lines);
        print_error(dup_msg);
    }
    *seen = true;
    parse_texture(trim, ctx->scene);
}

void dup_or_parse_resolution(t_hdr_ctx *ctx, char *trim, bool *seen)
{
    if (*seen)
    {
        free(trim);
        free_split(ctx->lines);
        print_error("Duplicate R directive");
    }
    *seen = true;
    parse_resolution(trim, ctx->scene);
}

void dup_or_parse_color(t_hdr_ctx *ctx, char *trim,
        bool *seen, const char *dup_msg)
{
    if (*seen)
    {
        free(trim);
        free_split(ctx->lines);
        print_error(dup_msg);
    }
    *seen = true;
    parse_color(trim, ctx->scene);
}
