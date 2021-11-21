#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct s_specifier
{
	va_list	args;
	int		nprint;
}	t_specifier;

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

void	ft_putstr(int *nprint, char *str)
{
	if (!str)
		*nprint += write(1, "(null)", ft_strlen("(null)"));
	else
		*nprint += write(1, str, ft_strlen(str));
}

void	ft_putnbr_base(int *nprint, int num, char *base_str)
{
	int	base_len;

	base_len = ft_strlen(base_str);
	if (num < 0)
	{
		*nprint = write(1, "-", 1);
		num *= -1;
	}
	if (num > base_len)
		ft_putnbr_base(nprint, num / base_len, base_str);
	*nprint += write(1, &base_str[num % base_len], 1);
}

void	ft_puthex(int *nprint, unsigned int num)
{
	char *base_str;

	base_str = "0123456789abcdef";
	if (num > 16)
		ft_puthex(nprint, num / 16);
	*nprint += write(1, &base_str[num % 16], 1);
}

void	converter(t_specifier *specifier, char c)
{
	if (c == 's')
		ft_putstr(&specifier->nprint, va_arg(specifier->args, char *));
	else if (c == 'd')
		ft_putnbr_base(&specifier->nprint,
			va_arg(specifier->args, int), "0123456789");
	else if (c == 'x')
		ft_puthex(&specifier->nprint, va_arg(specifier->args, unsigned int));
}

char	*ft_strchr(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (&str[i]);
	}
	return (NULL);
}

int	ft_printf(const char *format, ...)
{
	t_specifier	specifier;

	specifier.nprint = 0;
	va_start(specifier.args, format);
	while (*format)
	{
		if (*format == '%' && ft_strchr("sdx", *(format + 1)))
		{
			format++;
			converter(&specifier, *format);
		}
		else if (*format == '%' && (*(format + 1) == '%'))
		{
			format++;
			specifier.nprint += write(1, format, 1);
		}
		else
			specifier.nprint += write(1, format, 1);
		format++;
	}
	va_end(specifier.args);
	return (specifier.nprint);
}
