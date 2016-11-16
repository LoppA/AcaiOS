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

#include "vga.h"

uint8_t* screen_start = (uint8_t *) 0xB8000;
int32_t pos = 0;

uint8_t characterColor = 0;
uint16_t charac = 0;

void set_character_color (enum color letterColor, enum color bgColor)
{
    //primeira metade do byte indica a cor de fundo, segunda metade indica a cor do caracter
    bgColor = bgColor << 4;
    characterColor = letterColor | bgColor;
}

void clear_screen() {
    uint32_t i;
	set_character_color (BLACK, BLACK);
    for (i = 0; i < 2*SCREEN_HEIGHT * SCREEN_WIDTH; i+=2) {
		*(screen_start+i) = ' ';
		*(screen_start+i + 1) = characterColor;
	}
	pos = 0;
}

void print_character (char letter, enum color letterColor, enum color bgColor) {
    //cada impressao exige dois bytes, um indicando a cor e outro o caracter a ser impresso

	if (letter == '\n') {
		pos += 2*(SCREEN_WIDTH - ((pos/2)%SCREEN_WIDTH));
	} else if (letter == '\t') {
		set_character_color (BLACK, BLACK);

		if (!(pos%16)) {
			*(screen_start + pos) = ' ';
			*(screen_start + pos + 1) = characterColor;
			pos += 2;
		}

		for ( ; pos%16; pos+=2) {
			*(screen_start + pos) = ' ';
			*(screen_start + pos + 1) = characterColor;
		}
	} else { 
    	set_character_color(letterColor, bgColor);
	    *(screen_start+pos) = letter;
		*(screen_start+pos+1) = characterColor;
	    pos+=2;//posicao se move de 2 em 2 bytes
	}

    if (pos >= 2 * SCREEN_HEIGHT * SCREEN_WIDTH) {
        //limpar tela e voltar pos para 0
        clear_screen();
    }
}
