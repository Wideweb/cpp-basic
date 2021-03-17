#include <algorithm>
#include <fstream>
#include <iostream>

const uint64_t c_MemoryLimitBytes = 6;

void merge(std::ifstream &chunk1, std::ifstream &chunk2, std::ofstream &out);

int main() {
    std::filesystem::create_directory("tmp");

    const size_t bufferSize = c_MemoryLimitBytes / 2;
    uint16_t buffer[bufferSize];

    std::ifstream in("data.txt", std::ios::binary | std::ios::in);

    size_t chunks = 0;
    while (!in.eof()) {
        std::ofstream chunk("tmp/chunk" + std::to_string(chunks) + ".txt",
                            std::ios::binary | std::ios::out | std::ios::trunc);

        size_t readSize = 0;
        while (readSize < bufferSize && !in.eof()) {
            in >> buffer[readSize];
            readSize++;
        }

        std::sort(buffer, buffer + readSize);

        for (size_t i = 0; i < readSize; i++) {
            chunk << buffer[i];
            if (i < readSize - 1) {
                chunk << " ";
            }
        }

        chunks++;
    }

    bool bufferFlag = true;
    for (size_t i = 0; i < chunks; i++) {
        std::ifstream chunk1("tmp/chunk" + std::to_string(i) + ".txt",
                             std::ios::binary | std::ios::in);
        std::ifstream chunk2(bufferFlag ? "tmp/merge0.txt" : "tmp/merge1.txt",
                             std::ios::binary | std::ios::in);
        std::ofstream mergeOut(bufferFlag ? "tmp/merge1.txt" : "tmp/merge0.txt",
                               std::ios::binary | std::ios::out |
                                   std::ios::trunc);

        merge(chunk1, chunk2, mergeOut);

        bufferFlag = !bufferFlag;
    }

    std::ifstream merge(bufferFlag ? "tmp/merge0.txt" : "tmp/merge1.txt",
                        std::ios::binary | std::ios::in);
    std::ofstream out("result.txt",
                      std::ios::binary | std::ios::out | std::ios::trunc);

    out << merge.rdbuf();

    merge.close();
    out.close();

    std::filesystem::remove_all("tmp");
}

void merge(std::ifstream &chunk1, std::ifstream &chunk2, std::ofstream &out) {
    if (!chunk1 || chunk1.eof()) {
        out << chunk2.rdbuf();
        return;
    }

    if (!chunk2 || chunk2.eof()) {
        out << chunk1.rdbuf();
        return;
    }

    uint16_t chunk1Value, chunk2Value;
    chunk1 >> chunk1Value;
    chunk2 >> chunk2Value;

    while (!chunk1.eof() || !chunk2.eof()) {
        if (chunk1Value <= chunk2Value) {
            if (chunk1.eof()) {
                break;
            }

            out << chunk1Value << " ";
            chunk1 >> chunk1Value;
        }

        if (chunk2Value <= chunk1Value) {
            if (chunk2.eof()) {
                break;
            }

            out << chunk2Value << " ";
            chunk2 >> chunk2Value;
        }
    }

    if (chunk2Value < chunk1Value) {
        out << chunk2Value << " ";
        out << chunk1Value;
    } else {
        out << chunk1Value << " ";
        out << chunk2Value;
    }

    if (!chunk1.eof()) {
        out << chunk1.rdbuf();
    }

    if (!chunk2.eof()) {
        out << chunk2.rdbuf();
    }
}