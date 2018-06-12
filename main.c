#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "RS_7_3.h"

int main()
{
    uint8_t *msg;
    uint8_t code[7];
    uint8_t i;

    msg = "abc";

    encode(msg,code,7,3);

    printf("Encoded message: \n\t");
    for(i=0;i<7;i++){
        printf("%d ",code[i]);
    }

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

    for(i=0;i<data_length;i++){
        uint8_t temp;

        encoded_message[i] = message[i];        //przepisz niezmienione dane

        /*generowanie dodatkowych słów*/
        temp = reg[3] ^ message[i];

        reg[3] = reg[2] ^ (multiply(temp,G3));      //wartosci rejestrow celowo przypisane w odwrotnej kolejnosci (najpierw reg[3], na koncu reg[0])
        reg[2] = reg[1] ^ (multiply(temp,G2));
        reg[1] = reg[0] ^ (multiply(temp,G1));
        reg[0] = multiply(temp,G0);
    }

    for(i=0;i<fec_length;i++){
        encoded_message[data_length+i] = reg[3];

        reg[3] = reg[2];    //przesun wartosci pomiedzy rejestrami
        reg[2] = reg[1];
        reg[1] = reg[0];
        reg[0] = 0;
    }
}

//uint8_t multiply(uint8_t a, uint8_t b){
//    uint8_t result;
//
//    result = 0;
//
//	while (a && b) {
//            if (b & 1) /* if b is odd, then add the corresponding a to result (final product = sum of all a's corresponding to odd b's) */
//                result ^= a; /* since we're in GF(2^m), addition is an XOR */
//
//            if (a & 0x80) /* GF modulo: if a >= 128, then it will overflow when shifted left, so reduce */
//                a = (a << 1) ^ 0x11b; /* XOR with the primitive polynomial x^8 + x^4 + x^3 + x + 1 (0b1_0001_1011) – you can change it but it must be irreducible */
//            else
//                a <<= 1; /* equivalent to a*2 */
//            b >>= 1; /* equivalent to b // 2 */
//	}
//
//    return result;
//}

/*Mnozenie pol Galois. Wielomian pierowtny: 1 + x + x^3*/
uint8_t multiply(uint8_t a, uint8_t b){
    uint8_t result;
    uint8_t temp;

    result = 0;

    result = ((a & 1) & (b & 1)) ^ ((a & 2) & (b & 4)) ^ ((a & 4) & (b & 2)); // C(0) = (A(0) and B(0)) xor (A(1) and B(2)) xor (A(2) and B(1))

    temp = ((a & 1) & (b & 2)) ^ ((a & 2) & (b & 1)) ^ ((a & 2) & (b & 4)) ^ ((a & 4) & (b & 2)) ^ ((a & 4) & (b & 4)); // C(1) = (A(0) and B(1)) xor (A(1) and B(0)) xor (A(1) and B(2)) xor (A(2) and B(1)) xor (A(2) and B(2))
    temp <<= 1;
    result |= temp;

    temp = ((a & 1) & (b & 4)) ^ ((a & 2) & (b & 2)) ^ ((a & 4) & (b & 1)) ^ ((a & 4) & (b & 4));  //C(2) = (A(0) and B(2)) xor (A(1) and B(1)) xor (A(2) and B(0)) xor (A(2) and B(2))
    temp <<= 2;
    result |= temp;

    return result;
}
