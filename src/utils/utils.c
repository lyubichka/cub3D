/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:59:19 by veronikalub       #+#    #+#             */
/*   Updated: 2026/01/11 19:44:12 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	print_error_ctx(const char *msg, t_hdr_ctx *ctx, char **extra)
{
	if (extra)
		free_split(extra);
	if (ctx)
	{
		if (ctx->current_trim)
			free(ctx->current_trim);
		if (ctx->lines)
			free_split(ctx->lines);
		if (ctx->scene)
			free_full_scene(ctx->scene);
	}
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

int	is_number_str(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	get_max_width(char **lines, int start, int end)
{
	int	max;
	int	len;

	max = 0;
	while (start < end)
	{
		len = ft_strlen(lines[start]);
		if (len > max)
			max = len;
		start++;
	}
	return (max);
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
