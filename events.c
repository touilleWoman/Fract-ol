/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:11:54 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/04 13:11:55 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				reset(t_context *pctx)
{
	pctx->key.zoom = 1;
	pctx->key.variation_cl = 0;
	pctx->limit.x2 = 2;
	pctx->limit.x1 = -2;
	pctx->limit.y2 = 1;
	pctx->limit.y1 = -1;
	pctx->key.var_x = 0;
	pctx->key.var_y = 0;
	pctx->max_iteration = 50;

}

int					key_press(int keycode, void *param)
{
	t_context *pctx;

	pctx = (t_context *)param;
	if (keycode == KEYCODE_ESC)
	{
		mlx_destroy_window(pctx->mlx_ptr, pctx->win_ptr);
		exit(0);
	}
	if (keycode == KEYCODE_LEFT)
		pctx->key.var_x = pctx->key.var_x + 0.1;
	if (keycode == KEYCODE_RIGHT)
		pctx->key.var_x = pctx->key.var_x - 0.1;
	if (keycode == KEYCODE_UP)
		pctx->key.var_y = pctx->key.var_y + 0.1;
	if (keycode == KEYCODE_DOWN)
		pctx->key.var_y = pctx->key.var_y - 0.1;
	if (keycode == KEYCODE_C)
		pctx->key.variation_cl = pctx->key.variation_cl + 10;
	if (keycode == KEYCODE_V)
		pctx->key.variation_cl = pctx->key.variation_cl - 10;
	if (keycode == KEYCODE_R)
		reset(pctx);


	mlx_clear_window(pctx->mlx_ptr, pctx->win_ptr);
	ft_bzero(pctx->data_a, (pctx->size_l) * WIN_Y);
	browse_pixel(pctx);


	return (0);
}


int				mouse_press(int button, int x, int y, void *param)
{
	t_context *pctx;
	float		b;

	pctx = (t_context *)param;
	if (button == MOUSE_UP)
	{
		pctx->limit.x2 = pctx->limit.x2 * 0.8;
		pctx->limit.x1 = pctx->limit.x1 * 0.8;
		pctx->limit.y2 = pctx->limit.y2 * 0.8;
		pctx->limit.y1 = pctx->limit.y1 * 0.8;
		pctx->max_iteration = pctx->max_iteration + 50;
		x++;
		y++;

	}
	if (button == MOUSE_DOWN )
	{
		b = 1.25;
		pctx->limit.x2 = pctx->limit.x2 * b;
		pctx->limit.x1 = pctx->limit.x1 * b;
		pctx->limit.y2 = pctx->limit.y2 * b;
		pctx->limit.y1 = pctx->limit.y1 * b;
		if (pctx->max_iteration >=100)
		{
			pctx->max_iteration = pctx->max_iteration - 50;

		}
		x++;
		y++;

	}
	mlx_clear_window(pctx->mlx_ptr, pctx->win_ptr);
	ft_bzero(pctx->data_a, (pctx->size_l) * WIN_Y);
	browse_pixel(pctx);
	return (0);
}

int				closewindow(void *param)
{
	t_context *pctx;

	pctx = (t_context *)param;
	mlx_destroy_window(pctx->mlx_ptr, pctx->win_ptr);
	exit(0);
	return (0);
}