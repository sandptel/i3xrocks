/*
 * main.c - main entry point
 * Copyright (C) 2014-2019  Vivien Didelot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include "i3xrocks-config.h"
#endif

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "bar.h"
#include "log.h"
#include "sys.h"

unsigned int log_level;

int main(int argc, char *argv[])
{
	char *output = NULL;
	char *path = NULL;
	char *conf_dir = NULL;
	char *user_conf_dir = NULL;
	bool term;
	int c;

	while (c = getopt(argc, argv, "c:o:d:u:vhV"), c != -1) {
		switch (c) {
		case 'c':
			path = optarg;
			break;
		case 'd':
			conf_dir = optarg;
			break;
		case 'u':
			user_conf_dir = optarg;
			break;				
		case 'o':
			output = optarg;
			break;
		case 'v':
			log_level++;
			break;
		case 'h':
			printf("Usage: %s [-c <configfile>] [-d <conf.d dir>] [-u <conf.d dir>] [-o <output>] [-v] [-h] [-V]\n", argv[0]);
			return EXIT_SUCCESS;
		case 'V':
			printf(PACKAGE_STRING " © 2020 - 2021 Ken Gilmer\n");
			return EXIT_SUCCESS;
		default:
			error("Try '%s -h' for more information.", argv[0]);
			return EXIT_FAILURE;
		}
	}

	term = !sys_isatty(STDOUT_FILENO);
	if (output)
		term = !strcmp(output, "term");

	if (bar_init(term, path, conf_dir, user_conf_dir))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
