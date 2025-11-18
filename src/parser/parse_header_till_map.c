/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_till_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:21:38 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/18 17:13:03 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Проверка: строка состоит только из допустимых символов карты (' ', '0', '1', 'N', 'S', 'E', 'W')
int is_map_line(const char *s)
{
    int i = 0;
    if (!s)
        return 0;
    if (s[0] == '\0')
        return 0;
    while (s[i])
    {
        char c = s[i];
        if (!(c == ' ' || c == '0' || c == '1' ||
              c == 'N' || c == 'S' || c == 'E' || c == 'W'))
            return 0;
        i++;
    }
    return 1;
}

// Обработка одной строки заголовка; возвращает следующий индекс или -1 для break
static int decide_line_kind(t_hdr_ctx *ctx, int i, char *trim)
{
    int next_i;

    next_i = i + 1;
    if (trim[0] == '\0')
        return (next_i);
    if (is_map_line(ctx->lines[i]))
    {
        ctx->map_start = i;
        return (-1);
    }
    return (0);
}

static int process_header_line(t_hdr_ctx *ctx, int i)
{
    char *trim;
    int   kind;
    int   res;

    trim = ft_strtrim(ctx->lines[i], " \t");
    if (!trim)
    {
        free_split(ctx->lines);
        print_error("alloc fail");
    }
    kind = decide_line_kind(ctx, i, trim);
    res = handle_kind_result(kind, trim);
    if (res != 0)
        return (res);
    handle_header_trim_ctx(ctx, trim);
    free(trim);
    return (i + 1);
}

static void init_seen_flags(t_hdr_ctx *ctx)
{
    ctx->seen_r = false;
    ctx->seen_no = false;
    ctx->seen_so = false;
    ctx->seen_we = false;
    ctx->seen_ea = false;
    ctx->seen_s = false;
    ctx->seen_f = false;
    ctx->seen_c = false;
}

int parse_header_until_map(char **lines, t_scene *scene)
{
    t_hdr_ctx ctx;
    int       i;
    int       next_i;

    ctx.lines = lines;
    ctx.scene = scene;
    ctx.map_start = -1;
    init_seen_flags(&ctx);
    i = 0;
    while (ctx.lines[i])
    {
        next_i = process_header_line(&ctx, i);
        if (next_i == -1)
            break;
        i = next_i;
    }
    validate_after_header(&ctx);
    return (ctx.map_start);
}