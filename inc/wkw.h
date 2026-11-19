/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wkw.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseltenr <kseltenr@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 22:48:59 by kseltenr          #+#    #+#             */
/*   Updated: 2026/11/18 22:50:17 by kseltenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WKW_H
# define WKW_H

# define MAX_SIZE 5

# include <stdint.h>
# include <stdbool.h>
# include <signal.h>
# include <stdlib.h>
# include <ncurses.h>
# include <time.h>
# include <inttypes.h>
# include <string.h>

typedef enum	e_const
{
	WIN_VALUE = 16,
}	t_const;

typedef enum e_dir
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN
}	t_dir;

typedef struct	s_game
{
	uint64_t	grid[MAX_SIZE][MAX_SIZE];
	uint64_t	size;
	uint64_t	score;
	bool		win;
}	t_game;

/* SLIDE.C */
int32_t	slide_line(uint64_t *line, uint64_t size, uint64_t *score);
int32_t	move_board(t_game *g, t_dir dir);

/* SIGNALS.C */
void	init_signals(void);
bool	should_quit(void);

/* GAME.C */
void	check_win(t_game *g);
bool	can_move(t_game *g);
void	spawn_tile(t_game *g);

#endif
