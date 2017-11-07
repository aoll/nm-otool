/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mess.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:42:43 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 17:05:20 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MESS_H
# define FT_MESS_H

# define CONTENT_TEXT_TEXT 	"Contents of (__TEXT,__text) section\n"
# define ERROR_LOAD_MIN_SIZE	"Mach-O load command with size < 8 bytes\n"
# define ERROR_LOAD_SIZE	"Mach-O segment load command size is too small\n"

# define ERROR_FORMAT "The file was not recognized as a valid object file\n"
# define ERROR_FORMAT_FILE ERROR_FORMAT
# define NO_ACCESS			"No access to : "
# define ERROR_FLAG			"ft_nm: Unknown command line argument"
# define TYPE_HELP			"Type './ft_nm -help' for more informations\n"
# define HELP				"-help"
# define USAGE "USAGE: nm [options] <input files>\n\n"
# define OPTION "General options:\n\n"
# define O_G "-g     Display only global (external) symbols\n\n"
# define O_U "-u     Display only undefined symbols\n\n"
# define O_UU "-U     Don't display undefined symbols\n\n"
# define O_P "-p     Don't sort; display in symbol-table order\n\n"
# define O_J "-j     Just display the symbol names (no value or type)\n\n"
# define O_R "-r     Sort in reverse order\n\n"
# define HELP_MESS	USAGE OPTION O_G O_U O_UU O_P O_J O_R

#endif
