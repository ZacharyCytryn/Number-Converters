#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Edge cases to consider:
Max sign magnitude (11111111 or 01111111)
Max Ones or Twos (11111111 or 01111111)
Negative zero values (print positive 0) **DONE FOR SIGN/MAG AND ONES**
Inproper sign value for BCD (01 or 10) **DONE**
Overflow for BCD (Number greater than 999,999) **DONE**
Error if 5 bits are greater than 9 for BCD
*/

int two_pow(int power) {
    int answer = 1;
    for (int i = 0; i < power; i++) {
        answer *= 2;
    }
    return answer;
}

int decimal_to_bcd_bits(int num) {
    unsigned int new_repr = 0x00000000;
    int rem = 0;
    int bit = 0;
    int temp_bit = 3;
    while (num != 0) {
        rem = num % 10;
        for (int i = 8; i > 0; i /= 2) {
            if ((rem % i) != rem) {
                new_repr |= 1 << (temp_bit + bit);
                rem -= i;
            }
            temp_bit--;
        }
        temp_bit = 3;
        num /= 10;
        bit += 5;
    }
    return new_repr;
}

int bcd_bits_to_decimal(unsigned int num) {
    int new_decimal = 0;
    int temp_sum = 0;
    int place_value = 1;
    int bit;
    int pow = 0; //Reset every five times it is used
    for (bit = 0; bit < 30; bit++) {
        if (pow == 5) {
            pow = 0;
            new_decimal += temp_sum * place_value;
            place_value *= 10;
            temp_sum = 0;

        }
        if (num & 1 << bit) {
            temp_sum += two_pow(pow);
        }
        pow++;
    }
    if (num & 0xC0000000) {
        return -new_decimal;
    }
    else {
        return new_decimal;
    }
}
//Up to 2^19 = 524288
unsigned int decimal_to_hex(int num) {
    unsigned int answer = 0x00000000;
    int bit = 19;
    for (int i = 524288; i > 0; i /= 2) {
        if ((num % i) != num) {
            answer |= 1 << bit;
            num -= i;
        }
        bit--;
    }
    return answer;
}

void repr_convert(char source_repr, char target_repr, unsigned int repr) {
    switch(source_repr) {
        case '1':
            switch(target_repr) {
                //Ones to ones (Same) Untested
                case '1':
                    if (repr == 0xFFFFFFFF) {
                        repr = 0x00000000;
                        printf("%08x\n", repr);
                    }
                    else {
                        printf("%08x\n", repr);
                    }
                    break;

                //Ones to twos Untested
                case '2':
                    if ((repr >> 31) == 0) {
                        printf("%08x\n", repr);
                    }
                    else {
                        if (repr == 0xFFFFFFFF) {
                            repr = 0x00000000;
                            printf("%08x\n", repr);
                        }
                        else {
                            repr += 0b1;
                            printf("%08x\n", repr);
                        }
                    }
                    break;
                
                //Ones to sign/magnitude Untested
                case 'S':
                    if ((repr >> 31) == 0) {
                        printf("%08x\n", repr);
                    }
                    else {
                        if (repr == 0xFFFFFFFF) {
                            repr = 0x00000000;
                            printf("%08x\n", repr);
                        }
                        else {
                            repr = ~repr | 0x80000000;
                            printf("%08x\n", repr);
                        }
                    }
                    break;
                
                //Ones to BCD
                case 'D':
                    //No flip
                    if ((repr >> 31) == 0) {
                        if (repr > 999999) {
                            printf("undefined\n");
                        }
                        else {
                            int sum = 0;
                            int unsigned second_repr = 0x00000000;
                            for (int i = 0; i < 31; i++) {
                                sum += (repr & 1 << i);
                            }
                            second_repr |= decimal_to_bcd_bits(sum);
                            //LATER: CHECK FOR INDEX OUT OF BOUND ERROR (NUMBER TOO LARGE)
                            printf("%08x\n", second_repr);
                        }
                    }
                    //With flip (negative)
                    else {
                        if (repr == 0xFFFFFFFF) {
                            repr = 0x00000000;
                            printf("%08x\n", repr);
                        }
                        else {
                            repr = ~repr;
                            int sum = 0;
                            int unsigned second_repr = 0x00000000;
                            for (int i = 0; i < 31; i++) {
                                sum += (repr & 1 << i);
                            }
                            if (sum > 999999) {
                                printf("undefined\n");
                            }
                            else {
                                second_repr |= (0xC0000000 | decimal_to_bcd_bits(sum));
                                printf("%08x\n", second_repr);
                            }
                        }
                    }
                    break;

                default:
                    printf("error\n");
                    break;
            }

            break;

        case '2':
            switch(target_repr) {
                //Twos to ones
                case '1':
                    if (repr == 0x80000000) {
                        printf("undefined\n");
                    }
                    else {
                        if ((repr >> 31) == 0) {
                            printf("%08x\n", repr);
                        }
                        else {
                            repr -= 0b1;
                            printf("%08x\n", repr);
                        }
                    }
                    break;

                //Twos to twos (Same)
                case '2':
                    printf("%08x\n", repr);
                    break;
                
                //Twos to sign/magnitude
                case 'S':
                    if ((repr >> 31) == 0) {
                        printf("%08x\n", repr);
                    }
                    else {
                        repr -= 0b1;
                        repr = ~repr | 0x80000000;
                        printf("%08x\n", repr);
                    }
                    break;
                
                //Twos to BCD
                case 'D':
                    //No flip
                    if ((repr >> 31) == 0) {
                        int sum = 0;
                        int unsigned second_repr = 0x00000000;
                        for (int i = 0; i < 31; i++) {
                            sum += (repr & 1 << i);
                        }
                        if (sum > 999999) {
                            printf("undefined\n");
                        }
                        else {
                            second_repr |= decimal_to_bcd_bits(sum);
                            //LATER: CHECK FOR INDEX OUT OF BOUND ERROR (NUMBER TOO LARGE)
                            printf("%08x\n", second_repr);
                        }
                    }
                    else {
                        repr -= 0b1;
                        repr = ~repr;
                        int sum = 0;
                        int unsigned second_repr = 0x00000000;
                        for (int i = 0; i < 31; i++) {
                            sum += (repr & 1 << i);
                        }
                        if (sum > 999999) {
                            printf("undefined\n");
                        }
                        else {
                            second_repr |= (0xC0000000 | decimal_to_bcd_bits(sum));
                            printf("%08x\n", second_repr);
                        }
                    }
                    break;

                default:
                    printf("error\n");
                    break;
            }
            break;

        case 'S':
            switch(target_repr) {
                //Sign/magnitude to ones
                case '1':
                    if (repr == 0x80000000) {
                        repr = 0x00000000;
                        printf("%08x\n", repr);
                    }
                    else {
                        if ((repr >> 31) == 0) {
                            printf("%08x\n", repr);
                        }
                        else {
                            repr = (~repr | 0x80000000);
                            printf("%08x\n", repr);
                        }
                    }
                    break;

                //Sign/magnitude to twos
                case '2':
                    if (repr == 0x80000000) {
                        repr = 0x00000000;
                        printf("%08x\n", repr);
                    }
                    else {
                        if ((repr >> 31) == 0) {
                            printf("%08x\n", repr);
                        }
                        else {
                            repr = (~repr | 0x80000000);
                            repr += 0b1;
                            printf("%08x\n", repr);
                        }
                    }
                    break;
                
                //Sign/magnitude to sign/magnitude (Same)
                case 'S':
                    if (repr == 0x80000000) {
                        repr = 0x00000000;
                        printf("%08x\n", repr);
                    }
                    else {
                        printf("%08x\n", repr);
                    }
                    break;
                
                //Sign/magnitude to BCD
                case 'D':
                    if (repr == 0x80000000) {
                        repr = 0x00000000;
                        printf("%08x\n", repr);
                    }
                    else {
                        if ((repr & 0x7FFFFFFF) > 999999) {
                            printf("undefined\n");
                        }
                        else {
                            //No flip
                            if ((repr >> 31) == 0) {
                                int sum = 0;
                                int unsigned second_repr = 0x00000000;
                                for (int i = 0; i < 31; i++) {
                                    sum += (repr & 1 << i);
                                }
                                second_repr |= decimal_to_bcd_bits(sum);
                                //LATER: CHECK FOR INDEX OUT OF BOUND ERROR (NUMBER TOO LARGE)
                                printf("%08x\n", second_repr);
                            }
                            else {
                                int sum = 0;
                                int unsigned second_repr = 0x00000000;
                                for (int i = 0; i < 31; i++) {
                                    sum += (repr & 1 << i);
                                }
                                second_repr |= (0xC0000000 | decimal_to_bcd_bits(sum));
                                printf("%08x\n", second_repr);
                            }
                        }
                    }
                    break;

                default:
                    printf("error\n");
                    break;
            }
            break;

        case 'D':
            switch(target_repr) {
                //BCD to ones
                case '1':
                    if ((((repr & 1 << 31) != 0) & ((repr & 1 << 30) == 0)) || (((repr & 1 << 31) == 0) & ((repr & 1 << 30) != 0))) {
                        printf("error\n");
                    }
                    else {
                        int dec_1 = bcd_bits_to_decimal(repr);
                        unsigned int new_repr_1 = decimal_to_hex(dec_1);
                        if (dec_1 < 0) {
                            new_repr_1 = ~new_repr_1;
                            printf("%08x\n", new_repr_1);
                        }
                        else {
                            printf("%08x\n", new_repr_1);
                        }
                    }
                    break;

                //BCD to twos
                case '2':
                    if ((((repr & 1 << 31) != 0) & ((repr & 1 << 30) == 0)) || (((repr & 1 << 31) == 0) & ((repr & 1 << 30) != 0))) {
                        printf("error\n");
                    }
                    else {
                        int dec_2 = bcd_bits_to_decimal(repr);
                        unsigned int new_repr_2 = decimal_to_hex(dec_2);
                        if (dec_2 < 0) {
                            new_repr_2 = ~new_repr_2;
                            new_repr_2 += 0b1;
                            printf("%08x\n", new_repr_2);
                        }
                        else {
                            printf("%08x\n", new_repr_2);
                        }
                    }
                    break;
                
                //BCD to sign/magnitude
                case 'S':
                    if ((((repr & 1 << 31) != 0) & ((repr & 1 << 30) == 0)) || (((repr & 1 << 31) == 0) & ((repr & 1 << 30) != 0))) {
                        printf("error\n");
                    }
                    else {
                        int dec_S = bcd_bits_to_decimal(repr);
                        unsigned int new_repr_S = decimal_to_bcd_bits(dec_S);
                        if (dec_S < 0) {
                            new_repr_S |= 0x80000000;
                            printf("%08x\n", new_repr_S);
                        }
                        else {
                            printf("%08x\n", new_repr_S);
                        }
                    }
                    break;
                
                //BCD to BCD (Same)
                case 'D':
                    printf("%x\n", repr);
                    break;

                default:
                    printf("error\n");
                    break;
            }
            break;

        default:
            printf("error\n");
            break;
    }
}




// DO NOT CHANGE ANY CODE BELOW THIS LINE
int main(int argc, char *argv[]) {
    (void)argc; // Suppress compiler warning
    repr_convert(argv[1][0], argv[2][0], (int)strtol(argv[3], NULL, 16));
    return 0;
}
