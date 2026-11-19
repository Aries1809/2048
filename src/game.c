/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseltenr <kseltenr@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 09:25:42 by kseltenr          #+#    #+#             */
/*   Updated: 2026/11/19 09:50:11 by kseltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"

void	spawn_tile(t_game *g)
{
	uint64_t	empty = 0;
	uint64_t	pos;

	for (uint64_t i = 0; i < g->size; i++)
	{
		for (uint64_t j = 0; j < g->size; j++)
		{
			if (!g->grid[i][j])
				empty++;
		}
	}
	if (!empty)
		return;
	pos = rand() % empty;
	empty = 0;
	for (uint64_t i = 0; i < g->size; i++)
	{
		for (uint64_t j = 0; j < g->size; j++)
		{
			if (!g->grid[i][j])
			{
				if (empty != pos)
					empty++;
				else
				{
					if (rand() % 10 == 0)
						g->grid[i][j] = 4;
					else
						g->grid[i][j] = 2;
					return;
				}
			}
		}
	}
}

bool	can_move(t_game *g)
{
	for (uint64_t i = 0; i < g->size; i++)
	{
		for (uint64_t j = 0; j < g->size; j++)
		{
			if (!g->grid[i][j])
				return true;
			if (i && g->grid[i][j] == g->grid[i - 1][j])
				return (true);
			if (j && g->grid[i][j] == g->grid[i][j - 1])
				return (true);
		}
	}
	return false;
}

void	check_win(t_game *g)
{
	uint64_t	v = WIN_VALUE;

	if (!v || (v & (v - 1)))
		return;
	for (uint64_t i = 0; i < g->size; i++)
	{
		for (uint64_t j = 0; j < g->size; j++)
		{
			if (g->grid[i][j] == v)
			{
				g->win = true;
				return;
			}
		}
	}
}
