/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:00:33 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/02 11:00:41 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					create_window(t_context *pctx)
{
	pctx->mlx_ptr = mlx_init();
	if (pctx->mlx_ptr == NULL)
	{
		ft_putendl_fd("mlx_init error", 2);
		return (-1);
	}
	pctx->win_ptr = mlx_new_window(pctx->mlx_ptr, WIN_X, WIN_Y, WIN_NAME);
	if (pctx->win_ptr == NULL)
	{
		ft_putendl_fd("mlx_new_window error", 2);
		return (-1);
	}
	pctx->img_ptr = mlx_new_image(pctx->mlx_ptr, WIN_X, WIN_Y);
	if (pctx->img_ptr == NULL)
	{
		ft_putendl_fd("mlx_new_image error", 2);
		return (-1);
	}
	return (0);
}

int					window(t_context *pctx)
{
	int		bpp;
	int		e;

	reset(pctx);
	if (create_window(pctx) == -1)
		return (-1);
	pctx->data_a = mlx_get_data_addr(pctx->img_ptr, &bpp, &pctx->size_l, &e);
	thread(pctx);
	mlx_hook(pctx->win_ptr, 2, 0, key_press, pctx);
	mlx_hook(pctx->win_ptr, 17, 0, closewindow, pctx);
	mlx_hook(pctx->win_ptr, 4, 0, mouse_press, pctx);
	mlx_hook(pctx->win_ptr, 6, 0, mouse_move, pctx);
	mlx_loop(pctx->mlx_ptr);
	return (0);
}
