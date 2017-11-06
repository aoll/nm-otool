#ifndef FT_MESS_H
#define FT_MESS_H

#define CONTENT_TEXT_TEXT 	"Contenu de (__TEXT,__text) section\n"
#define ERROR_LOAD_MIN_SIZE	"Mach-O load command avec taille < 8 octets\n"
#define ERROR_LOAD_SIZE		"Mach-O segment load command taille trop petite\n"
#define ERROR_FORMAT_FILE	"Le fichier n'est pas reconnu \
comme un objet valide\n"
#define NO_ACCESS			"Acces refuse pour : "
#define ERROR_FLAG			"ft_nm: Argument inconnu"
#define TYPE_HELP			"Entrez './ft_nm -help' pour plus d'informations\n"
#define HELP				"-aide"
#define HELP_MESS			"USAGE: nm [options] <fichier>\n\n\
Options:\n\n\
-g     Affiche uniquement symboles (extern) global\n\n\
-u     Affiche uniquement symboles indefenis\n\n\
-U     N'affiche pas symboles indefenis\n\n\
-p     Pas de tri; affiche les symboles par odre d'apparition\n\n\
-j     Affiche uniquement le nom des symboles (pas de value ou de type)\n\n\
-r     Tri inverse\n\n"

#endif
