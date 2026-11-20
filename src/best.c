/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseltenr <kseltenr@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:05:55 by kseltenr          #+#    #+#             */
/*   Updated: 2026/11/20 23:12:00 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wkw.h"
#include <fcntl.h>
#include <unistd.h>

#define BEST_FILE ".2048_best"


#include "wkw.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define BEST_FILE ".2048_best"

bool	load_best(uint64_t best[2])
{
	int		fd;
	ssize_t	ret;

	best[0] = 0;
	best[1] = 0;
	fd = open(BEST_FILE, O_RDONLY);
	while (fd == -1 && errno == EINTR)
		fd = open(BEST_FILE, O_RDONLY);
	if (fd == -1)
		return (errno == ENOENT);
	ret = read(fd, best, sizeof(uint64_t) * 2);
	while (ret == -1 && errno == EINTR)
		ret = read(fd, best, sizeof(uint64_t) * 2);
	if (close(fd) == -1 || ret != sizeof(uint64_t) * 2)
	{
		best[0] = 0;
		best[1] = 0;
		return (false);
	}
	return (true);
}

bool	save_best(uint64_t best[2])
{
	int		fd;
	ssize_t	ret;

	fd = open(BEST_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (fd == -1 && errno == EINTR)
		fd = open(BEST_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (false);
	ret = write(fd, best, sizeof(uint64_t) * 2);
	while (ret == -1 && errno == EINTR)
		ret = write(fd, best, sizeof(uint64_t) * 2);
	if (close(fd) == -1 || ret != sizeof(uint64_t) * 2)
		return (false);
	return (true);
}
