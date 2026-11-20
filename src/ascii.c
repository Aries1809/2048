/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseltenr <kseltenr@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:27:23 by kseltenr          #+#    #+#             */
/*   Updated: 2026/11/20 20:15:03 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"

void	draw_art(int y, int x, uint64_t v, int len)
{
	static const char	*font[10][ART_DIGIT_H] = {
		{" _ ", "| |", "|_|"}, {"   ", "  |", "  |"},
		{" _ ", " _|", "|_ "}, {" _ ", " _|", " _|"},
		{"   ", "|_|", "  |"}, {" _ ", "|_ ", " _|"},
		{" _ ", "|_ ", "|_|"}, {" _ ", "  |", "  |"},
		{" _ ", "|_|", "|_|"}, {" _ ", "|_|", " _|"},
	};
	uint64_t			div = 1;

	for (int i = 1; i < len; i++)
		div *= 10;
	for (int i = 0; i < len; i++, div /= 10)
		for (int row = 0; row < ART_DIGIT_H; row++)
			mvaddstr(y + row, x + i * ART_DIGIT_H, font[(v / div) % 10][row]);
}
