/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 01:12:45 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/14 01:13:37 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void        nm_help(char const *bin)
{
    ft_printf("USAGE: %s [options] <input files>\n", bin);
	ft_printf("\nOPTIONS:\n\nGeneral options:\n\n");
	ft_printf("  %-25s %s\n", "-n --numeric-sort", "Sort symbols by address");
	ft_printf("  %-25s %s\n", "-r --reverse-sort", "Sort in reverse order");
	ft_printf("  %-25s %s\n", "-g --extern-only",
		"Show only external symbols");
	ft_printf("  %-25s %s\n", "-p --no-sort",
		"Show symbols in order encountered");
	ft_printf("  %-25s %s\n", "-u --undefined-only",
		"Show only undefined symbols");
	ft_printf("  %-25s %s\n", "-U --defined-only", "Show only defined symbols");
	ft_printf("  %-25s %s\n", "-j --simple-output",
		"Print just the symbol's name");
	ft_printf("  %-25s %s\n", "-a --debug-syms",
		"Show all symbols, even debugger only");
	ft_printf("  %-25s %s\n", "-h --help", "Display available options");
}