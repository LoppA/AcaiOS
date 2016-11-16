/*Copyright © 2016 - Jorge Hideki Motokubo Halker (jorge.halker@usp.br), 	Lucas de Oliveira Pacheco (lucas.oliveira.pacheco@usp.br), Raul Wagner da Costa Silva (raul.wagner.costa@usp.br).


This file is part of AcaiOS.

AcaiOS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

AcaiOS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.


You should have received a copy of the GNU General Public License
along with AcaiOS.  If not, see <http://www.gnu.org/licenses/>.*/

#include "stdio.h"

int putchar (int c) {
	print_character(c, WHITE, BLACK);
	return c;
}

int putstring (const char* str) {
	int i = 0;

	while (str[i])
		putchar(str[i++]);

	return i;
}

int puts (const char* str) {
	int n;
	n = putstring (str);
	putchar('\n');

	return n + 1;
}

int revert (int val, int base, int* total) {
	int rval = 0;
	*total = 0;

	while (val) {
		*total = *total + 1;
		rval *= base;
		rval += val%base;
		val /= base;
	}

	return rval;
}

int print_int (int val) {
	int rval, total, n = 0;

	if (val == 0) {
		putchar('0');
		return 1;
	}

	if (val < 0) {
		putchar('-');
		n++;
	}
	
	rval = revert (val, 10, &total);

	while (total--) {
		putchar((rval%10) + '0');
		rval /= 10;
		n++;
	}
	return n;
}

int print_hex (int val) {
	int rval, total, n = 0;

	if (val == 0) {
		putchar('0');
		return 1;
	}

	rval = revert (val, 16, &total);

	while (total--) {
		int num = (rval%16);
		n++;

		if (num < 10)
			putchar(num + '0');
		else
			putchar('A' + num - 10);

		rval /= 16;
	}

	return n;
}

int print_bin (int val) {
	int rval, total, n = 0;

	if (val == 0) {
		putchar('0');
		return 1;
	}

	rval = revert(val, 2, &total);

	while (total--) {
		n++;
		putchar ((rval%2) + '0');
		rval /= 2;
	}
	return n;
}

int vfprintf (const char* format, va_list arg) {
	int n = 0;

	while (*format) {
		if (*format == '%') {
			format++;
			if (*format == '%') {
				putchar('%');
				n++;
			} else if (*format == 'c') {
				putchar(va_arg(arg, int));
				n++;
			} else if (*format == 's') {
				n += putstring(va_arg(arg, char *));
			} else if (*format == 'd') {
				n += print_int(va_arg(arg, int));
			} else if (*format == 'b') {
				n += print_bin(va_arg(arg, int));
			} else if (*format == 'x') {
				n += print_hex(va_arg(arg, int));
			} else {
				return -1;
			}
		} else if (*format == '\n') { 
			putchar('\n');
		} else {
			putchar(*format);
			n++;
		}
		format++;
	}

	return n;
}

int printf (const char* format, ...) {
	va_list arg;
	int n;

	va_start (arg, format);
		n = vfprintf (format, arg);
	va_end (arg);

	return n;
}
