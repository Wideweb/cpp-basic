#pragma once

#include <algorithm>
#include <codecvt>
#include <locale>
#include <sstream>
#include <string>

class Utils {
  public:
    // std::string::length возвращает длину строки в байтах, однако некоторые
    // символы в этой строке могут занимать два байта в памяти. Поэтому, чтобы
    // определить длину строки в символах небюходимо от общего количества байт
    // отнять количество двухбайтовых символов.
    int static stringLength(const std::string &s) {
        const int twoBytesChars =
            std::count_if(s.begin(), s.end(), [](char c) -> bool {
                // Многобайтовые символы начинаются с 10xxxxxx в двоичном
                // формате.
                return (c & 0xC0) == 0x80;
            });

        return (s.length() - twoBytesChars);
    }
};
