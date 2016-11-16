Copyright © 2016 - Jorge Hideki Motokubo Halker (jorge.halker@usp.br), 	Lucas de Oliveira Pacheco (lucas.oliveira.pacheco@usp.br), Raul Wagner da Costa Silva (raul.wagner.costa@usp.br).


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
along with AcaiOS.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _STDIO_H_
#define _STDIO_H_

#include "stdarg.h"
#include "vga.h"
#include "stddef.h"

int putchar (int);
int puts (const char *);
int printf(const char *, ...);

#endif
