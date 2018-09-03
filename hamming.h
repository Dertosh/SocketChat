#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/*
 * вывод в двоичном виде
 */

string binToString(int n, size_t size);

/*
 * вывод в двоичном виде
 */

void printBin(int n, size_t size);

/*
 * вывод в двоичном виде
 */

void printBin(int n);

/*
 * суммирование
 */

uint32_t sum(uint32_t n);

uint32_t sumMod(uint32_t n);

int toBin(int n);

/*
 * конвертация строки с бинарным числом в size_t
 */

size_t stringToBin(string str);

/*
 * кодирование
 */

uint32_t encode(uint32_t number, int k);

/*
 * декодирование
 */

uint32_t decode(uint32_t number, int k);

size_t hammingEncode2(size_t number, int k);

const uint16_t mass[5] = {0x55555555, 0x66666666, 0x78787878, 0x7F807F80,
                          0x7FFF8000};

uint32_t hammingEncode(uint32_t number, int k);

size_t hammingCorrection1(size_t number, size_t k);

uint16_t hammingCheck(uint16_t number, int k);

size_t hammingCorrection(size_t number, size_t k);

size_t getBin(string text, string textError);

void printTableLine(size_t size);

void printTableCloseLine(size_t size);

void printTableLine(string str, string str1, size_t size);

void test(int k);

size_t* correctedCode(size_t bin, size_t k, size_t i = 0, size_t* line = NULL);
/*
 * аналог setw
 */
string setw(int n, size_t size);
