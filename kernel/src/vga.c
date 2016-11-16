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
    for (i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
        pos = i;
        print_character( 0, BLACK, BLACK);
    }
}

void print_character (char letter, enum color letterColor, enum color bgColor) {
    //cada impressao exige dois bytes, um indicando a cor e outro o caracter a ser impresso
	int f = 1;

    set_character_color(letterColor, bgColor);
    charac = characterColor;
    charac = charac << 8; //posiciona a cor no primeiro byte
    charac = charac | letter;

	if (letter == '\n') {
		pos += 2*(SCREEN_WIDTH - ((pos/2)%SCREEN_WIDTH));
		f = 0;
	} else if (letter == '\t') {
		pos += 2*(8 - ((pos/2)%8));
		f = 0;
	}
   
	if (f) {
	    *(screen_start+pos) = charac;
	    pos+=2;//posicao se move de 2 em 2 bytes
	}

    if (pos >= SCREEN_HEIGHT * SCREEN_WIDTH) {
        //limpar tela e voltar pos para 0
        clear_screen();
        pos = 0;
    }
}
