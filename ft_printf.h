#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define FLAGS "-+ #0"

int		ft_printf(const char *format, ...);

#endif
