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
		for ( ; pos < (pos/2)%8; pos+=2) {
			*(screen_start + pos) = ' ';
			*(screen_start + pos + 1) = characterColor;
		}
	} else { 
    	set_character_color(letterColor, bgColor);
	    *(screen_start+pos) = letter;
		*(screen_start+pos+1) = characterColor;
	    pos+=2;//posicao se move de 2 em 2 bytes
	}

    if (pos >= SCREEN_HEIGHT * SCREEN_WIDTH) {
        //limpar tela e voltar pos para 0
        clear_screen();
    }
}
