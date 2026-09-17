#ifndef LOCALE_H
#define LOCALE_H

#include <string>

// 格式化金额为美式货币字符串，例如：$123.45
std::string locale_en_us(double amount);

// 打印对齐行，例如：Subtotal      $123.45
void print_line(const std::string& label, const std::string& value);

#endif // LOCALE_H