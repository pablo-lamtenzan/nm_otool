/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 01:11:45 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/14 03:05:18 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int             nm(int ac, char **argv)
{
    t_data      data;
    int         it;

    it = -1;
    // parse arguments and init
    if (!init_exec(&data, 0, ac, argv))
    {
        // check option -help
        if (data.flags & MASK_HLP)
            nm_help(data.bin);
        else
        {
            // no nfiles ? start with "a.out"
            if (!data.nfiles && start_exec(&data, DEFAULT_EXEC))
                return (FAILURE);
            while (++it < data.nfiles)
            {
                // print exec names
                if (data.nfiles > 1)
                    ft_printf("\n%s:\n", data.name_of_exec[it]);
                // start exec of files
                if (start_exec(&data, data.names_of_execs[it]))
                    return (FAILURE);
            }
        }
        free(&data.names_of_execs);
        return (SUCCES);
    }
    return (FAILURE);
}