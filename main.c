#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "RS_7_3.h"

int main()
{


    return 0;
}

/*
@param *message - kodowana wiadomosc
@param *encoded_message - wiadomosc po zakodowaniu
@param code_length - dlugosc zakodowanej wiadomosci (w bajtach)
@param data_length - dlugosc wiadomosci (bez dodatkowych slow)

Funkcja implementuje kodowanie Reed-Solomona. W funkcji zamodelowana zostala struktura LFSR (Linear Feedback Shift Register)
*/
void encode(uint8_t *message, uint8_t *encoded_message, uint8_t code_length, uint8_t data_length){
    uint8_t i;
    uint8_t fec_length;     //iloœæ dodatkowych s³ów

    if(data_length >= code_length){
        printf("Error!\n Code Length must be greater than Data Length\n");
        return;
    }
    fec_length = code_length - data_length;

    uint8_t reg[fec_length];           //rejestry

    for(i=0;i<fec_length;i++){      //wyzeruj rejestry
        reg[i] = 0;
    }
    //data without change
    for(i=0;i<data_length;i++){
        encoded_message[i] = message[i];

        //R[0] = mnoz(G0, (R[3] xor message[i]))
        //R[1] = R[0] xor (mnoz(G1,(R[3] xor message[i])))
        //R[2] = R[1] xor (mnoz(G2,(R[3] xor message[i])))
        //R[3] = R[2] xor (mnoz(G3,(R[3] xor message[i])))
    }
    //add to message check data
    for(i=0;i<fec_length;i++){

    }
}

uint8_t multiply(uint8_t a, uint8_t b){

}
