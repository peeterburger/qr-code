#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define QC_FORMAT_INFO 0b001011010001001

int position_element[8][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 1, 1, 1, 1, 1, 0, 1 },
    { 0, 1, 0, 0, 0, 1, 0, 1 },
    { 0, 1, 0, 0, 0, 1, 0, 1 },
    { 0, 1, 0, 0, 0, 1, 0, 1 },
    { 0, 1, 1, 1, 1, 1, 0, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
};

void print_matrix(FILE *location, int mat[][21]);
int generate_fixed_patterns(int mat[][21]);
int init_matrix(int mat[][21]);
int generate_format_information(int mat[][21]);
void encode_message(int mat[][21], char *message);

int main(int argc, char **argv) {
    FILE *input_file;
    FILE *output_file;
    char *message_to_encode;
    int qr_code_mat[21][21];

    if (argc < 2) {
        input_file = fopen("./input.txt", "r");
        message_to_encode = malloc(sizeof(char) * 255);
        fgets(message_to_encode, 255, input_file);
        fclose(input_file);
    } else {
        message_to_encode = argv[1];
    }

    init_matrix(qr_code_mat);

    generate_fixed_patterns(qr_code_mat);

    generate_format_information(qr_code_mat);

    encode_message(qr_code_mat, message_to_encode);

    output_file = fopen("./output.txt", "w");
    
    print_matrix(stdout, qr_code_mat);
    print_matrix(output_file, qr_code_mat);

    fclose(output_file);

    return EXIT_SUCCESS;
}

int init_matrix(int mat[][21]) {
    for (int i = 0; i < 21; i++)
        for (int j = 0; j < 21; j++)
            mat[i][j] = -1;
}

int generate_fixed_patterns(int mat[][21]) {
    int tr_offset_x = 21 - 8;
 
    // position elements
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            // top left
            mat[i][j] = position_element[i][j];

            // top right
            mat[21 - 8 + i][j] = position_element[i][j];

            // bottom left
            mat[i][21 - 8 + j] = position_element[i][j];

        }
    }

    // timing elements
    for (int i = 0; i < 5; i++) {
       mat[6][i + 8] = i % 2;
       mat[i + 8][6] = i % 2; 
    }

    mat[8][13] = 0;
}

int generate_format_information(int mat[][21]) {
    for (int i = 0; i < 8; i++) {
        mat[8][i] = (QC_FORMAT_INFO >> i) & 1;
        mat[8][21 - 1 - i] = (QC_FORMAT_INFO >> i + 8) & 1;
        mat[i][8] = (QC_FORMAT_INFO >> i + 8) & 1;
        mat[21 - 1 - i][8] = (QC_FORMAT_INFO >> i + 8) & 1;
    }
}

void print_matrix(FILE *location, int mat[][21]) {
    for (int y = 0; y < 21; y++) {
        for (int x = 0; x < 21; x++) {
            switch (mat[x][y]) {
            case 0:
                fprintf(location, "\u25A0 ");
                break;
            
            case 1:
                fprintf(location, "\u25A1 ");
                break;

            default:
                fprintf(location, "? ");
            }
        }

        fprintf(location, "\n");
    }
}

void encode_message(int mat[][21], char *message) {
    return;
}