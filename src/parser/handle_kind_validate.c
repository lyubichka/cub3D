/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_kind_validate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:09:14 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/16 15:11:58 by veronikalub      ###   ########.fr       */
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

// Валидация после окончания прохода по заголовку
void validate_after_header(t_hdr_ctx *ctx)
{
    if (ctx->map_start == -1)
    {
        free_split(ctx->lines);
        print_error("Map section not found");
    }
    // По требованиям из темы: обязательны NO, SO, WE, EA, F, C.
    // R и S не обязательны.
    if (!ctx->seen_no || !ctx->seen_so || !ctx->seen_we
        || !ctx->seen_ea || !ctx->seen_f || !ctx->seen_c)
    {
        free_split(ctx->lines);
        print_error("Missing one or more directives before map");
    }
}