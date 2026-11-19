/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseltenr <kseltenr@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 09:53:15 by kseltenr          #+#    #+#             */
/*   Updated: 2026/11/19 10:29:00 by kseltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"
#include <ncurses.h>

static bool	is_arrow(int key)
{
	return (key == KEY_LEFT || key == KEY_RIGHT
		|| key == KEY_UP || key == KEY_DOWN);
}

static t_dir	key_to_dir(int key)
{
	if (key == KEY_LEFT)
		return (DIR_LEFT);
	if (key == KEY_RIGHT)
		return (DIR_RIGHT);
	if (key == KEY_UP)
		return (DIR_UP);
	return (DIR_DOWN);
}

static void	wait_message(const char *msg)
{
	mvprintw(LINES - 1, 0, "%s", msg);
	refresh();
	getch();
}

static void	handle_win(t_game *g)
{
	bool	was_won = g->win;

	check_win(g);
	if (!was_won && g->win)
		wait_message("You win! Press any key to keep playing.");
}

static void	show_game_over(void)
{
	wait_message("Game over! Press any key to quit.");
}

static int	uint_len(uint64_t i)
{
	int	ret = 0;

	while (i)
	{
		ret++;
		i /= 10;
	}
	return ret;
}

static int	max_value_len(t_game *g)
{
	int	max = 0;

	for (uint64_t i = 0; i < g->size; i++)
	{
		for (uint64_t j = 0; j < g->size; j++)
		{
			if (max < uint_len(g->grid[i][j]))
				max = uint_len(g->grid[i][j]);
		}
	}
	return max;
}

static void	draw(t_game *g)
{
	clear();
	int	cell_width = max_value_len(g) + 2;
	if (cell_width < 6)
		cell_width = 6;
	int	grid_width = g->size * (cell_width + 1) + 1;
	int	grid_height = g->size * 2 + 1;
	if (COLS < grid_width || LINES < grid_height + 1)
	{
		const char	*msg = "Terminal too small";
		int			len = (int)strlen(msg);
		int			x = (COLS - len) / 2;

		if (x < 0)
			x = 0;
		mvprintw(LINES / 2, x, "%s", msg);
		refresh();
		return ;
	}

	int top = (LINES - (grid_height + 1)) / 2;
	int left = (COLS - grid_width) / 2;

	for (uint64_t r = 0; r <= g->size; r++)
	{
		int y = top + r * 2;
		for (int x = 0; x < grid_width; x++)
			mvaddch(y, left + x, (x % (cell_width + 1) == 0) ? '+' : '-');
		if (r < g->size)
			for (uint64_t c = 0; c <= g->size; c++)
				mvaddch(y + 1, left + c * (cell_width + 1), '|');
	}

	for (uint64_t r = 0; r < g->size; r++)
	{
		for (uint64_t c = 0; c < g->size; c++)
		{
			uint64_t v = g->grid[r][c];
			if (!v)
				continue ;
			int x = left + 1 + c * (cell_width + 1)
				+ (cell_width - uint_len(v)) / 2;
			mvprintw(top + r * 2 + 1, x, "%"PRIu64"", v);
		}
	}

	mvprintw(top + grid_height, left, "Score: %"PRIu64"", g->score);
	refresh();
}

int	main(void)
{
	t_game	g = {0};
	int		key;

	srand(time(NULL));
	g.size = 4;
	spawn_tile(&g);
	spawn_tile(&g);

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	set_escdelay(25);
	init_signals();

	while (!should_quit())
	{
		draw(&g);
		key = getch();
		if (key == 27)
			break ;
		if (key == KEY_RESIZE)
			continue ;
		if (is_arrow(key) && move_board(&g, key_to_dir(key)))
		{
			spawn_tile(&g);
			handle_win(&g);
			if (!can_move(&g))
			{
				draw(&g);
				show_game_over();
				break ;
			}
		}
	}
	endwin();
	return (0);
}
