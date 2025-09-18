#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
        // You may insert code here
    return (0);
}

int match_char(FILE *f, char c)
{
        // You may insert code here
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}

int scan_int(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}

int scan_string(FILE *f, va_list ap)
{
    char *str = va_arg(ap, char*);
    int c = fgetc(f);
    int scanned = 0;

    while (c != EOF && !isspace(c)){
        str[scanned] = c;
        scanned++;
        c = fgetc(f);
    }
    if (c != EOF) 
        ungetc(c, f);
    str[scanned] = "\0";
    if(scanned == 0)
        return 0;
    return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			return scan_int(f, ap);
		case 's':
			return scan_string(f, ap);
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;
    int ret;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
            ret = match_conv(f, &format, ap);
			if (ret == -1)
				return (nconv == 0) ? -1 : nconv;
            else if (ret == 0){
                    return nconv;
            }
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else {
            ret = match_char(f, *format);
            if (ret == -1){
                return (nconv == 0) ? -1 : nconv;
            } 
            else if (ret == 0){
                return nconv;
            }
        }
			break;
		format++;
	}
	
	if (ferror(f))
		return -1;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
    va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}