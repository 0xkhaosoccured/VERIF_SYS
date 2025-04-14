#include "include/pch.h"

// TODO: Сжатие файлов для будущего создания около-репачного метода упаковывания файлов

namespace VSFilesystem
{
    class Header
    {
        uint64_t fileC;
        std::vector<uint64_t> hashes = {};
    };

    class Core
    {
        virtual void compress();
        virtual void decompress();
    };

    class Validator 
    {
        public:
        bool fileverif(std::vector<uint64_t>& hashes);
    }
}