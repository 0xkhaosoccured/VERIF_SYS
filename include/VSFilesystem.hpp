#include "include/pch.h"

// TODO: Сжатие файлов для будущего создания около-репачного метода упаковывания файлов

namespace fs = std::filesystem;


inline std::string ToHex(void const * data, size_t size) 
{
    std::stringstream ss;
    ss << std::uppercase << std::hex;
    for (size_t i = 0; i < size; ++i)
        ss << std::setfill('0') << std::setw(2) << size_t(((uint8_t const *)data)[i]);
    return ss.str();
}


inline std::string xxh3_128_hexdigest(void const * data, size_t size) 
{
    auto h = XXH3_128bits(data, size);
    std::reverse(((uint8_t*)&h) + 0, ((uint8_t*)&h) + sizeof(h));
    return ToHex(&h, sizeof(h));
}

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
        virtual void compress();
        virtual void decompress();
    };

    class Validator 
    {
        public:
        bool fileverif(std::vector<uint64_t>& hashes);
    };
}