#include "list/list.h"

#ifndef HASH_TABLE_H_INCLUDED
#define HASH_TABLE_H_INCLUDED

const int MAX_WORD_LENGTH = 32;
const int HASH_TABLE_SIZE = 4001;

struct hash_table_t {
    list_t *table;
    int table_size;
};

struct hash_function_t {
    unsigned long long (*func)(const char *str);
    const char *hash_name;
};

extern "C" { int MyStrlen(const char *str); };

hash_table_t CreateHashTable(int table_size);
int CheckIfStringIsInTableCellAndInsertIt(hash_table_t *hash_table, int cell_index, const char *compare_string);
int CheckIfStringIsInTableCell(hash_table_t *hash_table, int cell_index, const char *compare_string);
int CheckIfStringIsInHashTable(hash_table_t *hash_table, const char *compare_string);
int CheckIfStringIsInTableCell_optimized(hash_table_t *hash_table, int cell_index, const char *compare_string);

int PrintHashFuncs();
hash_table_t CreateHashTableBasedOnDefaultFile(const hash_function_t curr_hash_func);

unsigned long long CountHash(const char *str);
unsigned long long ZeroHash(const char *str);
unsigned long long FirstLetterHash(const char *str);
unsigned long long WordLenHash(const char *str);
unsigned long long AsciiSumHash(const char *str);
unsigned long long RolHash(const char *str);
unsigned long long RorHash(const char *str);
unsigned long long DJB2Hash(const char *str);
unsigned long long CRC32Hash(const char *str);
unsigned long long Crc32Hash_optimized(const char *str);

const hash_function_t HASH_FUNCS_ARRAY[] = {{ZeroHash, "Zero-hash"}, 
                                            {FirstLetterHash, "Hash-FirstLetterASCIICode"}, 
                                            {WordLenHash, "Hash-LenOfWord"}, 
                                            {AsciiSumHash, "Hash-AsciiSumOfLetters"}, 
                                            {RolHash, "ROL-hash"}, 
                                            {RorHash, "ROR-hash"}, 
                                            {DJB2Hash, "DJB2"}, 
                                            {CRC32Hash, "CRC-32"}};
const int HASH_FUNCS_COUNT = sizeof(HASH_FUNCS_ARRAY) / sizeof(hash_function_t);

int DrawHashTableDump(hash_table_t *hash_table, const char *file_name, const char *function_name, int line_number);
int PrintHashCellsSizes(hash_table_t *hash_table);

void HashTableDtor(hash_table_t *hash_table);

unsigned long long RolFunc(unsigned long long number); // Машинный код превращает это в rol
unsigned long long RorFunc(unsigned long long number); // Машинный код превращает это в ror

char *MyStrDup(const char *str);

#endif


