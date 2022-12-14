#include <cstdint>
#include <stdio.h>
#include <fstream>

void print_hex(char test[], uint64_t binary) {
    
    printf("This is `%s`: %lX\n", test, binary);
}

int permuted_choice_1 [] = {
    57, 49, 41, 33, 25, 17, 9, 
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27, 
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29, 
    21, 13, 5, 28, 20, 12, 4
};

int permuted_choice_2 [] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10, 
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

int left_shifts [] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};


int initial_permutation [] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};


int expansion_table [] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

int s_box [8][4 * 16] = {
    {
        14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
        0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
        4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
        15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
    },
    {
        15,  1,   8, 14,   6, 11 ,  3,  4 ,  9,  7 ,  2, 13  ,12,  0,   5, 10,
        3 ,13 ,  4 , 7 , 15 , 2  , 8 ,14  ,12 , 0  , 1 ,10   ,6 , 9 , 11 , 5,
        0 ,14 ,  7 ,11 , 10 , 4  ,13 , 1  , 5 , 8  ,12 , 6   ,9 , 3 ,  2 ,15,
        13,  8,  10,  1,   3, 15 ,  4,  2 , 11,  6 ,  7, 12  , 0,  5,  14,  9
    },
    {
        10,  0,   9, 14,   6,  3,  15,  5,   1, 13,  12,  7 , 11,  4,   2,  8,
        13,  7,   0,  9,   3,  4,   6, 10,   2,  8,   5, 14 , 12, 11,  15,  1,
        13,  6,   4,  9,   8, 15,   3,  0,  11,  1,   2, 12 ,  5, 10,  14,  7,
        1 ,10 , 13 , 0 ,  6 , 9 ,  8 , 7 ,  4 ,15 , 14 , 3  ,11 , 5 ,  2 ,12
    },
    {
        7 ,13 , 14 , 3 ,  0 , 6 ,  9 ,10  , 1 , 2 ,  8 , 5 , 11 ,12 ,  4 ,15,
        13,  8,  11,  5,   6, 15,   0,  3 ,  4,  7,   2, 12,   1, 10,  14,  9,
        10,  6,   9,  0,  12, 11,   7, 13 , 15,  1,   3, 14,   5,  2,   8,  4,
        3 ,15 ,  0 , 6 , 10 , 1 , 13 , 8  , 9 , 4 ,  5 ,11 , 12 , 7 ,  2 ,14
    },
    {
        2 ,12 ,  4 , 1 ,  7 ,10 , 11 , 6 ,  8 , 5 ,  3 ,15 , 13 , 0 , 14 , 9,
        14, 11,   2, 12,   4,  7,  13,  1,   5,  0,  15, 10,   3,  9,   8,  6,
        4 , 2 ,  1 ,11 , 10 ,13 ,  7 , 8 , 15 , 9 , 12 , 5 ,  6 , 3 ,  0 ,14,
        11,  8,  12,  7,   1, 14,   2, 13,   6, 15,   0,  9,  10,  4,   5,  3
    },
    {
        12,  1,  10, 15,   9,  2,   6,  8,   0, 13,   3,  4,  14,  7,   5, 11,
        10, 15,   4,  2,   7, 12,   9,  5,   6,  1,  13, 14,   0, 11,   3,  8,
        9 ,14 , 15 , 5 ,  2 , 8 , 12 , 3 ,  7 , 0 ,  4 ,10 ,  1 ,13 , 11 , 6,
        4 , 3 ,  2 ,12 ,  9 , 5 , 15 ,10 , 11 ,14 ,  1 , 7 ,  6 , 0 ,  8 ,13
    },
    {
        4 ,11 ,  2 ,14 , 15 , 0 ,  8 ,13 ,  3 ,12 ,  9 , 7 ,  5 ,10 ,  6 , 1,
        13,  0,  11,  7,   4,  9,   1, 10,  14,  3,   5, 12,   2, 15,   8,  6,
        1 , 4 , 11 ,13 , 12 , 3 ,  7 ,14 , 10 ,15 ,  6 , 8 ,  0 , 5 ,  9 , 2,
        6 ,11 , 13 , 8 ,  1 , 4 , 10 , 7 ,  9 , 5 ,  0 ,15 , 14 , 2 ,  3 ,12
    },
    {
        13,  2,   8,  4,   6, 15,  11,  1,  10,  9,   3, 14,   5,  0,  12,  7,
        1 ,15 , 13 , 8 , 10 , 3 ,  7 , 4 , 12 , 5 ,  6 ,11 ,  0 ,14 ,  9 , 2,
        7 ,11 ,  4 , 1 ,  9 ,12 , 14 , 2 ,  0 , 6 , 10 ,13 , 15 , 3 ,  5 , 8,
        2 , 1 , 14 , 7 ,  4 ,10 ,  8 ,13 , 15 ,12 ,  9 , 0 ,  3 , 5 ,  6 ,11,
    }
};

int f_permutaion [] = {
    16,   7,  20,  21,
    29,  12,  28,  17,
    1 , 15 , 23 , 26,
    5 , 18 , 31 , 10,
    2 ,  8 , 24 , 14,
    32,  27,   3,   9,
    19,  13,  30,   6,
    22,  11,   4,  25
};

int inverse_permutation [] = {
    40,     8,  48,    16,    56,   24,    64,   32,
    39,     7,  47,    15,    55,   23,    63,   31,
    38,     6,  46,    14,    54,   22,    62,   30,
    37,     5,  45,    13,    53,   21,    61,   29,
    36,     4,  44,    12,    52,   20,    60,   28,
    35,     3,  43,    11,    51,   19,    59,   27,
    34,     2,  42,    10,    50,   18,    58,   26,
    33,     1,  41,     9,    49,   17,    57,   25,
};

uint64_t keys [16];

uint64_t ONE = 1;

uint64_t circular_shift (uint64_t& target, int shifts, int len) {
    return ((target << shifts) | (target >> len - shifts)) & ((ONE << 28) - 1);
}



void generate_keys(uint64_t& key) {

    uint64_t permuted_out = 0;
    for(int i = 0; i < 56; i++) {
        permuted_out =  (((key >> (64 - permuted_choice_1[i]) ) & ONE) | (permuted_out << 1));
    }

    uint64_t left = permuted_out >> 28;
    uint64_t right = permuted_out & 0x000000000FFFFFFF;

    for(int i = 0; i < 16; i++) {
        left = circular_shift(left, left_shifts[i], 28);
        right = circular_shift(right, left_shifts[i], 28);

        uint64_t concat_keys = (left << 28) | right;
        uint64_t final_key = 0;
        for(int j = 0; j < 48; j++) {
            final_key = ((( concat_keys >> (56 - permuted_choice_2[j]) ) & ONE) | (final_key << 1));
        }
        keys[i] = final_key;
    }
}
#define BUFFER 1 << 21

uint64_t feistel_cipher (uint64_t& in, uint64_t& key) {
    uint64_t expan_in = 0;
    for(int i = 0; i < 48; ++i) {
        expan_in = (((in >> 32 - expansion_table[i]) & ONE) | (expan_in << 1));
    }
    expan_in ^= key;

    uint32_t s_box_output = 0;
    for(int i = 0; i < 8; ++i) {
        uint8_t part = (expan_in >> (42 - i * 6)) & 0x3F;
        uint8_t row = (((part & 0x20) >> 4) | (part & 1));
        uint8_t col = (part >> 1) & 0xF;
        s_box_output |= ( (uint64_t)s_box[i][(row << 4) | col] << (28 - i * 4));
    }    
    uint32_t out = 0;
    for(int i = 0; i < 32; ++i) {
        out = (((s_box_output >> 32 - f_permutaion[i]) & ONE) | (out << 1));
    }

    return out;
}

uint64_t mutate_data (uint64_t data, bool encrypt) {
    uint64_t permuted_data = 0;
    for(int i = 0; i < 64; ++i) {
        permuted_data = (((data >> 64 - initial_permutation[i]) & ONE) | (permuted_data << 1));
    }

    uint64_t left = permuted_data >> 32;
    uint64_t right = permuted_data & ((ONE << 32) - 1);


    for(int i = 0; i < 16; ++i) {
        uint64_t temp = right;
        int key = (encrypt) ? i : 15 - i;
        right = feistel_cipher(right, keys[key]) ^ left;
        left = temp;
    }
    uint64_t swapped = (right << 32) | left;  
    uint64_t final_out = 0;
    for(int i = 0; i < 64; ++i) {
        final_out = (((swapped >> 64 - inverse_permutation[i]) & ONE) | (final_out << 1));
    }
    return final_out;
}  



unsigned char inner_buffer[8];
int read64(uint64_t& data, FILE* file) {
    int size = fread(inner_buffer, 1, 8, file);
    data = 0;
    for (size_t i = 0; i < 8; i++) {
        data = ( data << 8 ) | (inner_buffer[i] & 0xFF);
    }
    return size;
}

void inverse(uint64_t& data) {
    uint64_t rev = 0;
    for(int i = 0; i < 8; ++i) {
        rev = (rev << 8) | (data & 0xFF);
        data = data >> 8;
    }
    data = rev;
}

void startup(const char data_location[], const char key_location[], 
    const char output_location[], const char output_hex_location[], bool encrypt) {
    FILE* keyF = fopen(key_location, "r");
    if(keyF == nullptr) {
        printf("Couldn't read key\n");
        return;
    };
    uint64_t key = 0;
    fscanf(keyF, "%lx", &key);
    fclose(keyF);

    char write_buffer[1 << 18];
    char read_buffer[1 << 12];
    generate_keys(key);

    uint64_t data_chunk = 0;
    FILE* dataF = fopen(data_location, "rb");

    if(dataF == nullptr) {
        printf("Couldn't read data\n");
        return;
    };

    FILE* outHex;
    if(encrypt) outHex = fopen(output_hex_location, "w");
    FILE* outAs = fopen(output_location, "wb");
    setvbuf(outAs, write_buffer, _IOFBF, 1 << 18);
    setvbuf(dataF, read_buffer, _IOFBF, 1 << 12);
    while(true) {
        int read_size = read64(data_chunk, dataF);
        if(read_size == 0) break;
        uint64_t res = mutate_data(data_chunk, encrypt);
        if(encrypt) fprintf(outHex, "%016lx", res);
        inverse(res);
        fwrite(&res, 1, 8, outAs);
    }
    if(encrypt) fclose(outHex);
    fclose(dataF);
}

#include <string.h>



int main(int argc, char* argv[]) {
    const char* encrypt = (argc >= 2) ? argv[1] : "encrypt";
    const char* data = (argc >= 3) ? argv[2] : "plain.txt";
    const char* key = (argc >= 4) ? argv[3] : "key.txt";
    const char encrypted_out[] = "encrypted.txt";
    const char decrypted_out[] = "decrypt.txt";
    const char hex_out[] = "hex.txt";
    bool isEncrypt = strcmp(encrypt, "encrypt") == 0;
    startup(data, key, (isEncrypt) ? encrypted_out : decrypted_out, hex_out, isEncrypt);
}
