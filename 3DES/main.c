#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>


FILE* key_file, * input_file, * output_file;

#define DES_KEY_SIZE 8


// таблица перестановки битов для расширенного ключа
int initial_key_permutaion[] = { 57, 49,  41, 33,  25,  17,  9,
                                 1, 58,  50, 42,  34,  26, 18,
                                10,  2,  59, 51,  43,  35, 27,
                                19, 11,   3, 60,  52,  44, 36,
                                63, 55,  47, 39,  31,  23, 15,
                                 7, 62,  54, 46,  38,  30, 22,
                                14,  6,  61, 53,  45,  37, 29,
                                21, 13,   5, 28,  20,  12,  4 };

// начальная перестановка битов исходного блока строки
int initial_message_permutation[] = { 58, 50, 42, 34, 26, 18, 10, 2,
                                        60, 52, 44, 36, 28, 20, 12, 4,
                                        62, 54, 46, 38, 30, 22, 14, 6,
                                        64, 56, 48, 40, 32, 24, 16, 8,
                                        57, 49, 41, 33, 25, 17,  9, 1,
                                        59, 51, 43, 35, 27, 19, 11, 3,
                                        61, 53, 45, 37, 29, 21, 13, 5,
                                        63, 55, 47, 39, 31, 23, 15, 7 };

//массив кол-ва позиций, на которые будут происходить левые циклические сдвиги левой и правой половины ключа
int key_shift_sizes[] = { -1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

//таблица выбора битов из расширенного ключа или перестановки битов предыдущего ключа, из которых состоит следующий ключ
int sub_key_permutation[] = { 14, 17, 11, 24,  1,  5,
                                 3, 28, 15,  6, 21, 10,
                                23, 19, 12,  4, 26,  8,
                                16,  7, 27, 20, 13,  2,
                                41, 52, 31, 37, 47, 55,
                                30, 40, 51, 45, 33, 48,
                                44, 49, 39, 56, 34, 53,
                                46, 42, 50, 36, 29, 32 };

//таблица порядка блоков правой части в блоке расширения
int message_expansion[] = { 32,  1,  2,  3,  4,  5,
                             4,  5,  6,  7,  8,  9,
                             8,  9, 10, 11, 12, 13,
                            12, 13, 14, 15, 16, 17,
                            16, 17, 18, 19, 20, 21,
                            20, 21, 22, 23, 24, 25,
                            24, 25, 26, 27, 28, 29,
                            28, 29, 30, 31, 32,  1 };

// таблицы перестановок каждого из восьми блоков(первые два бита блока в 10й системе счисления - номер строки,
// остальные 4 бита в 10й системе счисления - столбец, элемент которого в переводе в двоичную систему счисления и является получившимся
//блоком, состоящим из 4х бит
int S1[] = { 14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
             0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
             4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
            15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13 };

int S2[] = { 15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
             3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
             0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
            13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9 };

int S3[] = { 10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
            13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
            13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
             1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12 };

int S4[] = { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
            13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
            10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
             3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14 };

int S5[] = { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
            14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
             4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
            11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3 };

int S6[] = { 12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
            10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
             9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
             4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13 };

int S7[] = { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
            13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
             1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
             6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12 };

int S8[] = { 13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
             1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
             7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
             2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11 };

// таблица перестановок правой половины блока
int right_sub_message_permutation[] = { 16,  7, 20, 21,
                                    29, 12, 28, 17,
                                     1, 15, 23, 26,
                                     5, 18, 31, 10,
                                     2,  8, 24, 14,
                                    32, 27,  3,  9,
                                    19, 13, 30,  6,
                                    22, 11,  4, 25 };

//таблица конечных(обратных начальным) перестановок текущего блока, состоящего из 64 бит
int final_message_permutation[] = { 40,  8, 48, 16, 56, 24, 64, 32,
                                    39,  7, 47, 15, 55, 23, 63, 31,
                                    38,  6, 46, 14, 54, 22, 62, 30,
                                    37,  5, 45, 13, 53, 21, 61, 29,
                                    36,  4, 44, 12, 52, 20, 60, 28,
                                    35,  3, 43, 11, 51, 19, 59, 27,
                                    34,  2, 42, 10, 50, 18, 58, 26,
                                    33,  1, 41,  9, 49, 17, 57, 25 };


typedef struct {
    unsigned char k[8];
    unsigned char c[4];
    unsigned char d[4];
} key_set;

unsigned char* generate_key(unsigned char* key);
key_set* generate_sub_keys(unsigned char* main_key, key_set* key_sets);
unsigned char* process_message(unsigned char* message_piece, unsigned char* processed_piece, key_set* key_sets, int operation);

int main() {
    unsigned long file_size;
    unsigned short int padding;

    setlocale(LC_ALL, "Rus");

    printf("ПРОГРАММА \"Шифрование/дешифрование текстового файла алгоритмом 3DES\"\n");

    //выбор операции
    int operation;//операция, которую выбирает пользователь
    printf("Введите операцию:\n");
    printf("1. Шифрование исходного файла\n");
    printf("2. Дешифрование исходного файла\n");
    printf("3. Генерация ключей шифрования/дешифрования\n\n");
    scanf("%d", &operation);
    if ((operation != 1) && (operation != 2) && (operation != 3))
    {
        operation = 3;
        printf("Ошибка ввода. Будет производиться операция по умолчанию  - 3. Генерация ключей шифрования/дешифрования\n");
    }
    else
        printf("Будет производиться операция под номером: %d\n", operation);


    if (operation == 3)
    {
        //открываем файл для записи ключа
        if ((key_file = fopen("key.txt", "wb")) == NULL)
        {
            printf("\nОшибка открытия файла для записи ключей шифрования/дешифрования\n");
            return -1;
        }


        unsigned int iseed = (unsigned int)time(NULL);
        srand(iseed);

        short int bytes_written;
        unsigned char* des_key = (unsigned char*)malloc(8 * sizeof(char) * 3);//выделяем динамическую память для строки размером 8 байт
        des_key = generate_key(des_key);
        bytes_written = fwrite(des_key, 1, DES_KEY_SIZE * 3, key_file);//количество записанных в файл с ключом байтов
        if (bytes_written != DES_KEY_SIZE * 3) {
            printf("Ошибка при записи ключей в файл \"key.txt\"");
            fclose(key_file);
            free(des_key);//освобождаем место в памяти
            return -2;
        }
        else printf("Ключи успешно записаны и равны: ");
        for (int i = 0; i < DES_KEY_SIZE * 3; i++)
            printf("%c", des_key[i]);


        free(des_key);
        fclose(key_file);
        return 0;
    }
    else
    {
        key_file = fopen("key.txt", "rb");
        if (!key_file) {
            printf("Ошибка открытия файла с ключом шифрования/дешифрования для чтения");
            return -3;
        }

        fseek(key_file, 0L, SEEK_END);//сдвигаем курсор в конец файла с ключами
        file_size = ftell(key_file);//кол-во байт во входном файле с ключами
        fseek(key_file, 0, SEEK_SET);//сдвигаем курсор в текущее положение файла с ключами

        char des_key1[8 * sizeof(char)];
        char des_key2[8 * sizeof(char)];
        char des_key3[8 * sizeof(char)];
        fgets(des_key1, DES_KEY_SIZE, key_file);
        fgets(des_key2, DES_KEY_SIZE, key_file);
        fgets(des_key3, DES_KEY_SIZE, key_file);

        if ((des_key1 == NULL) || (des_key2 == NULL) || (des_key3 == NULL) || (file_size != DES_KEY_SIZE * 3)) {
            printf("Ключи в файле \"key.txt\" не имеют нужного размера.\nСгенерируйте ключи или сами напишите в файл 3 ключа из 8-ми символов");
            fclose(key_file);
            return -4;
        }
        fclose(key_file);
        if (operation == 1) {
            input_file = fopen("input.txt", "rb");
        }
        else {
            input_file = fopen("output.txt", "rb");
        }

        if (!input_file) {
            printf("Ошибка открытия входного файла на чтение");
            return -5;
        }

        if (operation == 1) {
            output_file = fopen("output.txt", "wb");
        }
        else {
            output_file = fopen("input.txt", "wb");
        }

        if (!output_file) {
            printf("Ошибка открытия выходного файла на запись");
            fclose(input_file);
            return -6;
        }


        short int bytes_written = 0;//кол-во записанных байтов
        unsigned long block_count = 0;//кол-во считанных блоков
        unsigned long number_of_blocks;//кол-во блоков, на которое будет разделен входной файл
        
        unsigned char* processed_block = (unsigned char*)malloc(8 * sizeof(char));
        key_set key_sets1[17];
        key_set key_sets2[17];
        key_set key_sets3[17];

        key_set* ptr1 = key_sets1;
        key_set* ptr2 = key_sets2;
        key_set* ptr3 = key_sets3;

        ptr1 = generate_sub_keys(des_key1, ptr1);
        ptr2 = generate_sub_keys(des_key2, ptr2);
        ptr3 = generate_sub_keys(des_key3, ptr3);

        fseek(input_file, 0L, SEEK_END);//сдвигаем курсор в конец входного файла

        file_size = ftell(input_file);//кол-во байт во входном файле
        fseek(input_file, 0, SEEK_SET);//сдвигаем курсор в текущее положение входного файла

        number_of_blocks = file_size / 8 + ((file_size % 8) ? 1 : 0);


        while (!feof(input_file)) {
            char data_block[8];
            fgets(data_block, 8, input_file);
            block_count++;
            if (block_count == number_of_blocks) {//все блоки прочитаны
                if (operation == 1) {
                    padding = 8 - file_size % 8;
                    if (padding < 8) {
                        memset((data_block + 8 - padding), (unsigned char)padding, padding);
                    }

                    processed_block = process_message(data_block, processed_block, ptr1, operation);
                    processed_block = process_message(data_block, processed_block, ptr2, operation);
                    processed_block = process_message(data_block, processed_block, ptr3, operation);
                    bytes_written = fwrite(processed_block, 1, 8, output_file);

                    if (padding == 8) {
                        memset(data_block, (unsigned char)padding, 8);
                        processed_block = process_message(data_block, processed_block, ptr1, operation);
                        processed_block = process_message(data_block, processed_block, ptr2, operation);
                        processed_block = process_message(data_block, processed_block, ptr3, operation);
                        bytes_written = fwrite(processed_block, 1, 8, output_file);
                    }
                }
                else {
                    processed_block = process_message(data_block, processed_block, ptr1, operation);
                    processed_block = process_message(data_block, processed_block, ptr2, operation);
                    processed_block = process_message(data_block, processed_block, ptr3, operation);
                    padding = processed_block[7];

                    if (padding < 8) {
                        bytes_written = fwrite(processed_block, 1, 8 - padding, output_file);
                    }
                }
            }
            else {
                processed_block = process_message(data_block, processed_block, ptr1, operation);
                processed_block = process_message(data_block, processed_block, ptr2, operation);
                processed_block = process_message(data_block, processed_block, ptr3, operation);
                bytes_written = fwrite(processed_block, 1, 8, output_file);
            }
            memset(data_block, 0, 8);
        }


        fclose(input_file);
        fclose(output_file);

        if (number_of_blocks == 0) printf("\nТекстовый файл пуст\n");
        else
        {
            if (operation == 1) printf("\nТекстовый файл \"input.txt\" зашифрован успешно\n");
            else printf("\nТекстовый файл \"output.txt\" дешифрован успешно\n");
        }
        return 0;
    }
}


unsigned char* generate_key(unsigned char* key) {
    int i;
    for (i = 0; i < 8 * 3; i++) {
        key[i] = rand() % 255;
    }
    return key;
}



key_set* generate_sub_keys(unsigned char* main_key, key_set* key_sets) {
    int i, j;
    int shift_size;
    unsigned char shift_byte, first_shift_bits, second_shift_bits, third_shift_bits, fourth_shift_bits;

    //элементы 0-го ключа, получающегося с помощью расширения начального ключа, заполняем символми ' '
    for (i = 0; i < 8; i++) {
        key_sets[0].k[i] = ' ';
    }

    //преобразуем 0-й ключ согласно таблице перестановки битов для расширенного ключа
    for (i = 0; i < 56; i++) {
        shift_size = initial_key_permutaion[i];
        shift_byte = 0x80 >> ((shift_size - 1) % 8);
        shift_byte &= main_key[(shift_size - 1) / 8];
        shift_byte <<= ((shift_size - 1) % 8);

        key_sets[0].k[i / 8] |= (shift_byte >> i % 8);
    }

    //левая половина расширенного ключа
    for (i = 0; i < 3; i++) {
        key_sets[0].c[i] = key_sets[0].k[i];
    }

    key_sets[0].c[3] = key_sets[0].k[3] & 0xF0;

    //правая половина расширенного ключа
    for (i = 0; i < 3; i++) {
        key_sets[0].d[i] = (key_sets[0].k[i + 3] & 0x0F) << 4;
        key_sets[0].d[i] |= (key_sets[0].k[i + 4] & 0xF0) >> 4;
    }

    key_sets[0].d[3] = (key_sets[0].k[6] & 0x0F) << 4;

    //i-й ключ для каждого цикла шифрования/дешифрования
    for (i = 1; i < 17; i++) {
        //начальные значения левых и правых частей i-го ключа = соотв. значениям предыдущего ключа
        for (j = 0; j < 4; j++) {
            key_sets[i].c[j] = key_sets[i - 1].c[j];
            key_sets[i].d[j] = key_sets[i - 1].d[j];
        }

        //кол-во позиций, на которые будут происходить левые циклические сдвиги левой и правой половины текущего ключа
        shift_size = key_shift_sizes[i];
        if (shift_size == 1) {
            shift_byte = 0x80;
        }
        else {
            shift_byte = 0xC0;
        }

        //устанавливаем биты для каждого символа левой половины ключа
        first_shift_bits = shift_byte & key_sets[i].c[0];
        second_shift_bits = shift_byte & key_sets[i].c[1];
        third_shift_bits = shift_byte & key_sets[i].c[2];
        fourth_shift_bits = shift_byte & key_sets[i].c[3];

        //производим побитовый сдвиг на shift_size позиций каждого символа левой половины ключа
        key_sets[i].c[0] <<= shift_size;
        key_sets[i].c[0] |= (second_shift_bits >> (8 - shift_size));

        key_sets[i].c[1] <<= shift_size;
        key_sets[i].c[1] |= (third_shift_bits >> (8 - shift_size));

        key_sets[i].c[2] <<= shift_size;
        key_sets[i].c[2] |= (fourth_shift_bits >> (8 - shift_size));

        key_sets[i].c[3] <<= shift_size;
        key_sets[i].c[3] |= (first_shift_bits >> (4 - shift_size));

        //устанавливаем биты для каждого символа правой половины ключа
        first_shift_bits = shift_byte & key_sets[i].d[0];
        second_shift_bits = shift_byte & key_sets[i].d[1];
        third_shift_bits = shift_byte & key_sets[i].d[2];
        fourth_shift_bits = shift_byte & key_sets[i].d[3];

        //производим побитовый сдвиг на shift_size позиций каждого символа правой половины ключа
        key_sets[i].d[0] <<= shift_size;
        key_sets[i].d[0] |= (second_shift_bits >> (8 - shift_size));

        key_sets[i].d[1] <<= shift_size;
        key_sets[i].d[1] |= (third_shift_bits >> (8 - shift_size));

        key_sets[i].d[2] <<= shift_size;
        key_sets[i].d[2] |= (fourth_shift_bits >> (8 - shift_size));

        key_sets[i].d[3] <<= shift_size;
        key_sets[i].d[3] |= (first_shift_bits >> (4 - shift_size));

        //выбираем биты конечного i-го ключа из правой и левой частей согласно таблице
        for (j = 0; j < 48; j++) {
            shift_size = sub_key_permutation[j];
            if (shift_size <= 28) {//текущий бит i-го ключа выбираем из преобразованной левой части
                shift_byte = 0x80 >> ((shift_size - 1) % 8);
                shift_byte &= key_sets[i].c[(shift_size - 1) / 8];
                shift_byte <<= ((shift_size - 1) % 8);
            }
            else {//текущий бит i-го ключа выбираем из преобразованной правой части
                shift_byte = 0x80 >> ((shift_size - 29) % 8);
                shift_byte &= key_sets[i].d[(shift_size - 29) / 8];
                shift_byte <<= ((shift_size - 29) % 8);
            }

            //добавляем 8 бит в виде одного символа в i-й ключ
            key_sets[i].k[j / 8] |= (shift_byte >> j % 8);
        }
    }
    return key_sets;
}

unsigned char* process_message(unsigned char* message_piece, unsigned char* processed_piece, key_set* key_sets, int operation) {
    int i, k;
    int shift_size;
    unsigned char shift_byte;


    unsigned char initial_permutation[8];
    memset(initial_permutation, 0, 8);
    memset(processed_piece, 0, 8);

    //переводим текущий блок, сотоящий из 8-ми символов, в битовый вид, и переставляем биты текущего блока
    //по таблице начальной перестановки битов
    for (i = 0; i < 64; i++) {
        shift_size = initial_message_permutation[i];
        shift_byte = 0x80 >> ((shift_size - 1) % 8);
        shift_byte &= message_piece[(shift_size - 1) / 8];
        shift_byte <<= ((shift_size - 1) % 8);

        initial_permutation[i / 8] |= (shift_byte >> i % 8);
    }

    unsigned char l[4], r[4];//левая и правая части блока, получившегося в результате
                             //перестановок битов исходного блока
    for (i = 0; i < 4; i++) {
        l[i] = initial_permutation[i];
        r[i] = initial_permutation[i + 4];
    }

    unsigned char ln[4], rn[4], er[6], ser[4];

    int key_index;
    // преобразуем исходный блок 16 раз
    for (k = 1; k <= 16; k++) {
        memcpy(ln, r, 4);//в левую часть блока копируем элементы из правой части предыдущего блока

        memset(er, 0, 6);//заполняем символами с кодом 0 правую часть блока,
        //которая получится в результате побитового
        //сложения i-го ключа и расширенной по таблице правой части

        //расширяем 32-битовую правую часть блока до 48 битов согласно таблице расширения
        for (i = 0; i < 48; i++) {
            shift_size = message_expansion[i];
            shift_byte = 0x80 >> ((shift_size - 1) % 8);
            shift_byte &= r[(shift_size - 1) / 8];
            shift_byte <<= ((shift_size - 1) % 8);

            er[i / 8] |= (shift_byte >> i % 8);
        }

        //при дешифровании меняем порядок ключей на обратный
        if (operation == 2) {
            key_index = 17 - k;
        }
        else {
            key_index = k;
        }

        //побитово складываем ключ и преобразованную правую часть блока
        for (i = 0; i < 6; i++) {
            er[i] ^= key_sets[key_index].k[i];
        }

        unsigned char row, col;//столбец и строка таблицы перестановки k-го блока

        //6-ти битовый блок er преобразуем 4-х битовый
        //текущие значения битов получившегося блока устанавливаем равными нулю
        for (i = 0; i < 4; i++) {
            ser[i] = 0;
        }

        row = 0;
        row |= ((er[0] & 0x80) >> 6);
        row |= ((er[0] & 0x04) >> 2);

        col = 0;
        col |= ((er[0] & 0x78) >> 3);

        ser[0] |= ((unsigned char)S1[row * 16 + col] << 4);

        row = 0;
        row |= (er[0] & 0x02);
        row |= ((er[1] & 0x10) >> 4);

        col = 0;
        col |= ((er[0] & 0x01) << 3);
        col |= ((er[1] & 0xE0) >> 5);

        ser[0] |= (unsigned char)S2[row * 16 + col];

        row = 0;
        row |= ((er[1] & 0x08) >> 2);
        row |= ((er[2] & 0x40) >> 6);

        col = 0;
        col |= ((er[1] & 0x07) << 1);
        col |= ((er[2] & 0x80) >> 7);

        ser[1] |= ((unsigned char)S3[row * 16 + col] << 4);

        row = 0;
        row |= ((er[2] & 0x20) >> 4);
        row |= (er[2] & 0x01);

        col = 0;
        col |= ((er[2] & 0x1E) >> 1);

        ser[1] |= (unsigned char)S4[row * 16 + col];


        row = 0;
        row |= ((er[3] & 0x80) >> 6);
        row |= ((er[3] & 0x04) >> 2);

        col = 0;
        col |= ((er[3] & 0x78) >> 3);

        ser[2] |= ((unsigned char)S5[row * 16 + col] << 4);

        row = 0;
        row |= (er[3] & 0x02);
        row |= ((er[4] & 0x10) >> 4);

        col = 0;
        col |= ((er[3] & 0x01) << 3);
        col |= ((er[4] & 0xE0) >> 5);

        ser[2] |= (unsigned char)S6[row * 16 + col];


        row = 0;
        row |= ((er[4] & 0x08) >> 2);
        row |= ((er[5] & 0x40) >> 6);

        col = 0;
        col |= ((er[4] & 0x07) << 1);
        col |= ((er[5] & 0x80) >> 7);

        ser[3] |= ((unsigned char)S7[row * 16 + col] << 4);

        row = 0;
        row |= ((er[5] & 0x20) >> 4);
        row |= (er[5] & 0x01);

        col = 0;
        col |= ((er[5] & 0x1E) >> 1);

        ser[3] |= (unsigned char)S8[row * 16 + col];

        //элементы получившейся правой части ключа приравниваем 0
        for (i = 0; i < 4; i++) {
            rn[i] = 0;
        }

        //переставляем биты в получившейся правой части ключа по таблице перестановок
        for (i = 0; i < 32; i++) {
            shift_size = right_sub_message_permutation[i];
            shift_byte = 0x80 >> ((shift_size - 1) % 8);
            shift_byte &= ser[(shift_size - 1) / 8];
            shift_byte <<= ((shift_size - 1) % 8);
            //каждые 8 битов записывем как 1 символ в получающийся блок
            rn[i / 8] |= (shift_byte >> i % 8);
        }

        //проводим сложение по модулю 2 получившейся правой части и начальной левой
        //и результат записываем в правую часть
        for (i = 0; i < 4; i++) {
            rn[i] ^= l[i];
        }

        //текущая левая часть блока принимает значения преобразованной левой части
        //текущая правая часть блока принимает значения преобразованной правой части
        for (i = 0; i < 4; i++) {
            l[i] = ln[i];
            r[i] = rn[i];
        }
    }

    //объединяем левую и правую части в один символьный блок
    unsigned char pre_end_permutation[8];
    for (i = 0; i < 4; i++) {
        pre_end_permutation[i] = r[i];
        pre_end_permutation[4 + i] = l[i];
    }

    //переставляем биты получившегося блока по таблице конечных перестановок
    for (i = 0; i < 64; i++) {
        shift_size = final_message_permutation[i];
        shift_byte = 0x80 >> ((shift_size - 1) % 8);
        shift_byte &= pre_end_permutation[(shift_size - 1) / 8];
        shift_byte <<= ((shift_size - 1) % 8);

        //в символьном виде записываем каждые 8 бит в выходной блок
        processed_piece[i / 8] |= (shift_byte >> i % 8);
    }
    return processed_piece;
}


