/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 01:14:40 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/14 02:07:11 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

// valable flags to cmp for nm or otool (depend of section)
static t_flag_data      g_flags[2][10] = {
    {
        {'n', "-numeric-sort", MASK_N},
		{'r', "-reverse-sort", MASK_R},
		{'g', "-extern-only", MASK_G},
		{'p', "-no-sort", MASK_P},
		{'u', "-undefined-only", MASK_U},
		{'U', "-defined-only", MASK_UU},
		{'j', "-simple-output", MASK_J},
		{'a', "-debug-syms", MASK_A},
		{'h', "-help", MASK_HLP},
		{0, "", 0}
    },
    {
        {'t', "-text-section", MASK_T},
		{'d', "-data-section", MASK_D},
		{'m', "-macho-header", MASK_M},
		{'f', "-fat-header", MASK_F},
		{'h', "-help", MASK_HLP},
		{0, "", 0}
    }
};

static t_flag_data      *get_flags(char *flag, char bin)
{
    int                 it;

    it = -1;
    // iterate into the flag options
    while (g_flags[bin][++it].simple_name)
    {
        // check if falg is valable by short or long way
        if((g_flags[bin][it].simple_name == flag[0] && !flag[1]) 
                || !ft_strcmp(flag, g_flags[bin][it].full_name))
            return (g_flags[bin][it]);
    }
    return (NULL);
}

static int              parse_flags(t_data *data, char bin, char **argv)
{
    t_flag_data         *flag;
    
    // no knowed flag == error
    if (!(flag = get_flags(argv + 1, bin)))
    {
        ft_printf("%s: Unknow command line argument '%s'. Try '%s' -help\n",
		data->name_of_exec, argv, data->name_of_exec);
		return (FAILURE);
    }
    // check double flag
    if (data->flags & flag->val)
    {
        ft_printf("%s: for the %s option: may only occur zero or one times!\n",
		data->name_of_exec, data->name_of_exec);
		return (FAILURE);
    }
    data->flags |= flag->val;
    return (SUCCES);
}

static int              parse_args(t_data *data, char bin, int ac, char **argv)
{
    int                 i;
    char                **exec_names;

    i = 1;
    while (--ac)
    {
        if (**(argv + i) == MINUS)
        {
            // verify arg is start with '-'
            if (!parse_flags(data, bin, argv))
                return (FAILURE);
        }
        else
        {
            // take all arg names
            if (!(exec_names = malloc(sizeof(char *) * data->nfiles + 1)))
                return (FAILURE);
            /* TO DO : take and copy filenames */
            exec_names[data->nfiles] = *argv;
            data->names_of_execs = (const char **)exec_names;
            data->nfiles++;
        }
        i++;
    }
    return (SUCCES);
}

int                     init_exec(t_data *data, char bin, int ac, char **argv)
{
    ft_bzero(data, sizeof(t_data));
    data->name_of_exec = argv[0];
    data->bin = bin;
    data->cpu_type = CPU_TYPE_X86_64;
    return (parse_args(data, ac, argv, bin));
}