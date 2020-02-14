/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:25:10 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/14 03:07:33 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static int          open_fd(t_data *data, const char *name_of_file, int *fd,
    uint64_t *size)
{
    struct stat     sb;

    // verify if openable file
    if ((*fd = open(name_of_file, O_RDONLY)) < 0 )
    {
        ft_printf("error: %s: Open error on file %s\n", 
                data->name_of_exec, name_of_file);
        return (FAILURE);
    }
    // verify fstat error
    if (fstat(*fd, &sb) < 0)
    {
        ft_printf("error: %s: Fstat error on file %s\n",
			data->name_of_exec, name_of_file);
		return (FAILURE);
    }
    // verify size (EOF)
    if (!(*size = sb.st_size))
    {
        ft_printf("%s: is not an object file\n", name_of_file);
		return (FAILURE);
	}
    return (SUCCES);
}

int                 start_exec(t_data *data, const char *name_of_file)
{
    t_file          file;
    uint64_t        size_of_file;
    void            *start;
    int             *fd;

    ft_bzero(&file, sizeof(t_file));
    // open the file
    if (open_fd(data, name_of_file, &fd, &size_of_file))
        return (FAILURE);
    // take file starts addr allocated
    if ((start = mmap(NULL, size_of_file, PROT_READ, MAP_PRIVATE,
            fd, 0)) == MAP_FAILED)
    {
        ft_printf("error: %s: Mmap error on file %s\n",
			data->name_of_exec, name_of_file);
		return (FAILURE);
    }
    // create a new file
    new_file(&file, name_of_file, size_of_file, start);
    
    // handle binary
    /* TO DO */
    
    // de-allocate the mem allcated with mmap and close
    if (munmap(start, size_of_file) < 0 || close(fd) < 0)
        return (FAILURE);
    return (SUCCES);
}