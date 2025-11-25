/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:12:12 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	draw_filled_rect(t_image *img, t_rect rect, int color)
{
	int	x;
	int	y;

	if (rect.w <= 0 || rect.h <= 0)
		return ;
	y = 0;
	while (y < rect.h)
	{
		x = 0;
		while (x < rect.w)
		{
			put_pixel(img, rect.x + x, rect.y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_filled_square_centered(t_image *img, t_point center, int color)
{
	int	x0;
	int	y0;
	int	x;
	int	y;

	x0 = center.x - center.radius;
	y0 = center.y - center.radius;
	y = 0;
	while (y < 2 * center.radius + 1)
	{
		x = 0;
		while (x < 2 * center.radius + 1)
		{
			put_pixel(img, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

static void	draw_line_pixels(t_image *img, t_line_state *state, int color)
{
	int	i;

	i = 0;
	while (i <= (int)state->steps)
	{
		put_pixel(img, (int)round(state->cx), (int)round(state->cy), color);
		state->cx += state->sx;
		state->cy += state->sy;
		i++;
	}
}

void	draw_line(t_image *img, t_line line, int color)
{
	t_line_state	state;

	state.dx = (double)(line.x1 - line.x0);
	state.dy = (double)(line.y1 - line.y0);
	if (fabs(state.dx) > fabs(state.dy))
		state.steps = fabs(state.dx);
	else
		state.steps = fabs(state.dy);
	if (state.steps < 1.0)
	{
		put_pixel(img, line.x0, line.y0, color);
		return ;
	}
	state.sx = state.dx / state.steps;
	state.sy = state.dy / state.steps;
	state.cx = (double)line.x0;
	state.cy = (double)line.y0;
	draw_line_pixels(img, &state, color);
}
