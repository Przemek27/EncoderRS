#ifndef RS_7_3_H_INCLUDED
#define RS_7_3_H_INCLUDED

//wielomian generuj¹cy g(x) = a3 + a0x2 + a3x3 + x4
#define G0 0b011        //g0 = a3 = 1+a = 0*a2 + 1*a1+1 + 1*a0
#define G1 0b010        //g1 = a1
#define G2 0b001        //g2 = a0
#define G3 0b011        //g3 = a3

void encode(uint8_t *message, uint8_t *encoded_message, uint8_t code_length, uint8_t data_length);

uint8_t multiply(uint8_t a, uint8_t b);

#endif // RS_7_3_H_INCLUDED
