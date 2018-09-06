#include "hamming.h"

size_t stringToBin(string str);

/*
 * вывод в двоичном виде
 */

string binToString(uint32_t n, size_t size) {
  string str = "";
  while (size--) str += 48 + ((n >> size) & 1);
  return str;
}

/*
 * вывод в двоичном виде
 */

void printBin(int n, size_t size) {
  while (size--) cout << ((n >> size) & 1);
}

/*
 * вывод в двоичном виде
 */

void printBin(int n) { printBin(n, 32); }

/*
 * суммирование
 */

uint32_t sum(uint32_t n) {
  uint32_t s = 0;
  uint32_t size = 32;
  while (size--) {
    s += ((n >> size) & 1);
  }
  return s;
}

uint32_t sumMod(uint32_t n) { return (sum(n) & 1); }

int toBin(int n) {
  int save = 0;
  for (int i = 0; n; i++) {
    save = save | ((n % 10) << i);
    n /= 10;
  }
  return save;
}

/*
 * конвертация строки с бинарным числом в size_t
 */

size_t stringToBin(string str) {
  size_t bin = 0, i = str.length() - 1;
  int check = 0;
  for (auto it = str.cbegin(); it != str.cend(); ++it, i--) {
    if ((check = (*it) - 48) > 1 || check < 0) {
      bin = -1;
      break;
    }
    if (check) bin += (check << i);
  }
  return bin;
}

/*
 * кодирование
 */

uint32_t encode(uint32_t number, int k) {
  for (uint32_t i = 1, mask = ~0; i < k;
       mask <<= i, i <<= 1)  // mask - маска накладования на число
    number = (number & (~mask)) | ((number & mask) << 1);  //накладование маски
  return number;
}

/*
 * декодирование
 */

uint32_t decode(uint32_t number, int k) {
  for (size_t i = 0, mask = ~0; i < k; mask = mask << i,
              i = (i << 1) | 1) {  // mask - маска накладования на число
    number = (number & (~mask)) |
             ((number & (mask << 1)) >> 1);  //накладование маски
  }
  return number;
}

size_t hammingEncode2(size_t number, int k) {
  for (size_t t = 1, mask = 0; t < k; t = t << 1, mask = 0) {
    for (size_t i = 0, c = (1 << t) - 1; i <= (k / (t << 2)); i++)
      mask = (mask << (t << 2)) | c;
    mask = mask << t - 1;
    number = number | ((sumMod(number & mask))
                       << t - 1);  //накладование маски и суммирование
  }
  return number;
}

uint32_t hammingEncode(uint32_t number, int k) {
  for (char i = 0; (1 << i) <= k; i++) {
    // cout << "num "
    //     << binToString(((sumMod(number & mass[i])) << (1 << i) - 1), 32)
    //     << endl;
    number |= ((sumMod(number & mass[i])) << ((1 << i) - 1));
    // cout << binToString(number, 32) << endl;
  }
  return number;
}

size_t hammingCorrection1(size_t number, size_t k) {
  size_t check = 0;
  for (size_t t = 1, x = 0, mask = 0; t < k; t = t << 1, mask = 0, x++) {
    for (size_t i = 0, c = (1 << t) - 1; i <= (k / (t << 2)); i++)
      mask = (mask << (t << 2)) | c;
    mask = mask << t - 1;
    check = check |
            ((sumMod(number & mask)) << x);  //накладование маски и суммирование
  }
  if (check) {
    size_t mask = 1 << (check - 1);
    number = (mask | number) & (~(mask & number));
  }
  return number;
}

uint16_t hammingCheck(uint16_t number, int k) {
  // k = log2(k + 1);
  uint16_t check = 0;
  for (char i = 0; (1 << i) <= k; i++)
    check |= ((sumMod(number & mass[i])) << i);
  return check;
}

uint16_t hammingCorrection(uint16_t number, size_t k) {
  size_t check = hammingCheck(number, k);
  // cout << "check = " << check << " bin = " << binToString(size_t(check), 16)
  //     << endl;
  if (check) {
    number ^= (1 << (check - 1));
  }
  return number;
}

size_t getBin(string text, string textError) {
  string str;
  cout << text;
  cin >> str;
  size_t bin = stringToBin(str);  //для хранения будем ипользовать int
  while ((bin >> 31) & 1) {
    cout << textError << text;
    cin >> str;
    bin = stringToBin(str);
  }
  return bin;
}

void printTableLine(size_t size) {
  string str = "|";
  size += 5;
  while (size--) str += char(151);
  str += "|";
  cout << str << endl;
}

void printTableCloseLine(size_t size) {
  size += 5;
  string str = " ";
  while (size--) str += char(151);
  cout << str << endl;
}

void printTableLine(string str, string str1, size_t size) {
  string spaces = "";
  size -= str.length();
  while (size--) spaces += " ";
  cout << "| " << str << spaces << " | " << str1 << " |" << endl;
}

void mytest(int k) {
  uint32_t bin = 2046;
  uint32_t error = 1 << 13;
  cout << binToString(bin, 32) << endl;
  bin = encode(bin, k);
  cout << "encode " << binToString(bin, 32) << endl;
  bin = hammingEncode(bin, k);
  cout << "hammingEncode     " << binToString(bin, 32) << endl;
  bin = (error | bin) & (~(error & bin));
  cout << "hammingError      " << binToString(bin, 32) << " " << log2(error) + 1
       << " " << binToString(error, 32) << endl;
  bin = hammingCorrection(bin, k);
  cout << "hammingCorrection " << binToString(bin, 32) << endl;
  bin = decode(bin, k);
  cout << "bin=" << bin << " " << binToString(bin, 32) << endl;
}

void test(int k) {
  cout << "Test start" << endl;
  uint32_t bin = 0;
  for (uint32_t error = 1; error < 16384; error <<= 1)
    for (uint32_t i = 0; i < 2048; i++) {
      bin = i;
      // cout << "i " << binToString(bin, 32) << endl;
      bin = encode(bin, k);
      // cout << "encode " << binToString(bin, 32) << endl;
      bin = hammingEncode(bin, k);
      // cout << "hammingEncode     " << binToString(bin, 32) << endl;
      bin = (error | bin) & (~(error & bin));
      // cout << "hammingError      " << binToString(bin, 30) << " "
      //     << log2(error) + 1 << " " << binToString(error, 30) << endl;
      bin = hammingCorrection(bin, k);
      // cout << "hammingCorrection " << binToString(bin, 30) << endl<<endl;
      bin = decode(bin, k);
      if (bin != i) {
        cout << "bin=" << bin << ", i=" << i << endl;
        cout << "ошибка : " << binToString(bin, 32) << " " << binToString(i, 32)
             << endl
             << endl;
      }
    }
  cout << "Test end" << endl;
}

size_t* correctedCode(size_t bin, size_t k, size_t i, size_t* line) {
  size_t* mass = new size_t[k];
  size_t* amount = new size_t[k];
  size_t* errors = new size_t[k];
  size_t end = 1 << k;
  for (size_t t = 0; t < k; t++) {
    mass[t] = 0;
    amount[t] = 0;
    errors[t] = 0;
  }
  for (size_t error = 1, temp = 0, check = 0; error < end; error++) {
    check = sum(error) - 1;
    amount[check]++;
    temp = bin ^ error;
    if (hammingCheck(temp, k) > 0) errors[check]++;
    if (hammingCorrection(temp, k) == bin) mass[check]++;
  }
  cout << "|  i | Cn^i |  No  | Nk | Ck |" << endl;
  for (size_t t = 0; t < k; t++) {
    cout << "|" << setw(3) << t + 1 << " |" << setw(5) << amount[t] << " |"
         << setw(5) << errors[t] << " |" << setw(3) << mass[t] << " |"
         << setw(3) << mass[t] / amount[t] << " |" << endl;
  }
  if (i == 0) i++;
  line[0] = i--;
  line[1] = amount[i];
  line[2] = mass[i];
  line[3] = mass[i] / amount[i];
  line[4] = errors[i];
  delete[] mass;
  delete[] amount;
  delete[] errors;
  return line;
}
/*
 * аналог setw
 */
string setw(int n, size_t size) {
  std::stringstream temp_stream;
  temp_stream << n;
  string number = temp_stream.str();
  string str = "";
  size -= number.size();
  for (size_t i = 0; i < size; i++) str.push_back(' ');
  return str + number;
}

int cat() {
  setlocale(LC_ALL, "Russian");
  int k = 15, sizeLine = 45;

  test(k);

  size_t bin = getBin("Исходная последовательность: ", "ошибка ввода!");
  size_t error = getBin("Ошибка: ", "ошибка ввода!");
  cout << endl;

  int i = sum(error);
  cout << "i (кратность ошибки) = " << i << endl;
  cout << endl;

  size_t line[5];
  correctedCode(hammingEncode(encode(bin, k), k), k, i, line);
  cout << endl;

  printTableCloseLine(sizeLine + k);
  // printTableLine("Исходная последовательность", binToString(bin, k),
  // sizeLine);
  printTableLine(sizeLine + k);

  bin = encode(bin, k);
  bin = hammingEncode(bin, k);

  // printTableLine("Закодированная последовательность", binToString(bin, k),
  //               sizeLine);
  printTableLine(sizeLine + k);

  // printTableLine("Введенная ошибка", binToString(error, k), sizeLine);
  printTableLine(sizeLine + k);

  // bin = (error | bin) & (~(error&bin)); //
  bin ^= error;

  // printTableLine("Последовательность c ошибкой", binToString(bin, k),
  // sizeLine);
  printTableLine(sizeLine + k);

  int check = hammingCheck(bin, k);

  printTableLine("Разряд ошибки", setw(check, k), sizeLine);
  printTableLine(sizeLine + k);

  bin = hammingCorrection(bin, k);

  // printTableLine("Исправленная последовательность", binToString(bin, k),
  //               sizeLine);
  printTableLine(sizeLine + k);

  bin = decode(bin, k);

  // printTableLine("Декодированная последовательность", binToString(bin, k),
  //               sizeLine);
  printTableLine(sizeLine + k);

  printTableLine("Ci^n Общее число ошибок данной кратности", setw(line[1], k),
                 sizeLine);
  printTableLine(sizeLine + k);

  printTableLine("No Число найденных ошибок", setw(line[4], k), sizeLine);
  printTableLine(sizeLine + k);

  printTableLine("Nk Число исправленных ошибок", setw(line[2], k), sizeLine);
  printTableLine(sizeLine + k);

  printTableLine("Ck Корректирующая способность кода", setw(line[3], k),
                 sizeLine);
  printTableCloseLine(sizeLine + k);

  cout << endl;

  // system("pause");
  return 0;
}
