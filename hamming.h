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

int sum(int n);

int sumMod(int n);

int toBin(int n);

/*
 * конвертация строки с бинарным числом в size_t
 */

size_t stringToBin(string str);

/*
 * кодирование
 */

int encode(int number, int k);

/*
 * декодирование
 */

int decode(int number, int k);

size_t hammingEncode2(size_t number, int k);

const size_t mass[5] = {0x55555555, 0x66666666, 0x78787878, 0x7F807F80,
                        0x7FFF8000};

size_t hammingEncode(size_t number, int k);

size_t hammingCorrection1(size_t number, size_t k);

int hammingCheck(size_t number, int k);

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
