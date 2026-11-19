/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   slide.c                                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: kseltenr <kseltenr@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/18 23:09:02 by kseltenr         #+#    #+#              */
/*   Updated: 2026/11/19 08:42:39 by kseltenr        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"

static uint64_t	*cell(t_game *g, t_dir dir, uint64_t i, uint64_t j)
{
	uint64_t	last = g->size - 1;

	if (dir == DIR_LEFT)
		return (&g->grid[i][j]);
	if (dir == DIR_RIGHT)
		return (&g->grid[i][last - j]);
	if (dir == DIR_UP)
		return (&g->grid[j][i]);
	return (&g->grid[last - j][i]);
}

static int32_t	compact(uint64_t *line, uint64_t size)
{
	uint64_t		w = 0;
	int32_t			moved = 0;

	for (uint64_t r = 0; r < size; r++)
	{
		if (!line[r])
			continue ;
		if (r != w)
		{
			line[w] = line[r];
			line[r] = 0;
			moved = 1;
		}
		w++;
	}
	return (moved);
}

int32_t	slide_line(uint64_t *line, uint64_t size, uint64_t *score)
{
	int32_t	moved;

	moved = compact(line, size);
	for (uint64_t n = 1; n < size; n++)
	{
		if (line[n] && line[n - 1] == line[n])
		{
			line[n - 1] *= 2;
			line[n] = 0;
			*score += line[n - 1];
			moved = 1;
		}
	}
	if (compact(line, size))
		moved = 1;
	return (moved);
}

int32_t	move_board(t_game *g, t_dir dir)
{
	uint64_t	tmp[MAX_SIZE];
	int32_t		moved = 0;

	for (uint64_t i = 0; i < g->size; i++)
	{
		for (uint64_t j = 0; j < g->size; j++)
			tmp[j] = *cell(g, dir, i, j);
		if (slide_line(tmp, g->size, &g->score))
			moved = 1;
		for (uint64_t j = 0; j < g->size; j++)
			*cell(g, dir, i, j) = tmp[j];
	}
	return (moved);
}
