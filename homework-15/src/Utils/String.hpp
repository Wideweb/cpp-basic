#pragma once

#include <algorithm>
#include <sstream>
#include <string>

class Utils {
  public:
    // std::string::length возвращает длину строки в байтах, однако некоторые
    // символы в этой строке могут занимать два байта в памяти. Поэтому, чтобы
    // определить длину строки в символах небюходимо от общего количества байт
    // отнять количество двухбайтовых символов.
    size_t static stringLength(const std::string &s) {
        const size_t twoBytesChars =
            std::count_if(s.cbegin(), s.cend(), [](char c) -> bool {
                // Многобайтовые символы начинаются с 10xxxxxx в двоичном
                // формате.
                return (c & 0xC0) == 0x80;
            });

        return (s.length() - twoBytesChars);
    }

    template <typename T> std::string static toString(T value) {
        std::ostringstream ss;
        ss << value;
        std::string str(ss.str());
        return str;
    }
};
