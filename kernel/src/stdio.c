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

int revert (int val, int base) {
	int rval = 0;

	while (val) {
		rval *= base;
		rval += val%base;
		val /= base;
	}

	return rval;
}

int print_int (int val) {
	int rval, n = 0;

	if (val < 0) {
		putchar('-');
		n++;
	}
	
	rval = revert (val, 10);

	while (rval) {
		putchar((rval%10) + '0');
		rval /= 10;
		n++;
	}
	return n;
}

int print_hex (int val) {
	int rval, n = 0;

	rval = revert (val, 16);

	while (rval) {
		int num = (rval%16);
		n++;

		if (num < 10)
			putchar(num + '0');
		else
			putchar('A' + num - 10);
	}

	return n;
}

int print_bin (int val) {
	int rval, n = 0;

	rval = revert(val, 2);

	while (rval) {
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
