#pragma once
#include "Shift.h"
namespace fs = std::filesystem;
using namespace std;
class FileCryptor {
    int shift = 20;
public:
    void cryptDirectory(const fs::path& dir);
    void decryptDirectory(const fs::path& dir);
    void crypt(const fs::path& file);
    void decrypt(fs::path cryptedFile);
};