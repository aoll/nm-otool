/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mess.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:42:56 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 17:02:21 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MESS_H
# define FT_MESS_H

# define CONTENT_TEXT_TEXT 	"Contenu de (__TEXT,__text) section\n"
# define ERROR_LOAD_MIN_SIZE	"Mach-O load command avec taille < 8 octets\n"
# define ERROR_LOAD_SIZE	"Mach-O segment load command taille trop petite\n"
# define ERR_VA "Le fichier n'est pas reconnu comme un objet valide\n"
# define ERROR_FORMAT_FILE	ERR_VA
# define NO_ACCESS			"Acces refuse pour : "
# define ERROR_FLAG			"ft_nm: Argument inconnu"
# define TYPE_HELP			"Entrez './ft_nm -aide' pour plus d'informations\n"
# define HELP				"-aide"
# define USAGE "USAGE: nm [options] <fichier>\n\n"
# define OPTION "Options:\n\n"
# define O_G "-g     Affiche uniquement symboles (extern) global\n\n"
# define O_U "-u     Affiche uniquement symboles indefenis\n\n"
# define O_UU "-U     N'affiche pas symboles indefenis\n\n"
# define O_P "-p     Pas de tri; affiche les symboles par odre d'apparition\n\n"
# define O_J "-j     Affiche uniquement le nom des symboles\n\n"
# define O_R "-r     Tri inverse\n\n"
# define HELP_MESS	USAGE OPTION O_G O_U O_UU O_P O_J O_R

#endif
