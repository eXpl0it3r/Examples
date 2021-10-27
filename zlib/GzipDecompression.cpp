#define ZLIB_CONST
#include <zlib.h>
#include <zconf.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool gzip_inflate(const std::string& compressed_bytes, std::string& uncompressed_bytes)
{
    if (compressed_bytes.size() == 0)
    {
        uncompressed_bytes = compressed_bytes;
        return true;
    }

    uncompressed_bytes.clear();

    auto full_length = compressed_bytes.size();

    auto uncompressed = std::vector<char>(full_length, 0);

    auto strm = z_stream{};
    strm.next_in = reinterpret_cast<z_const Bytef*>(compressed_bytes.data());
    strm.avail_in = compressed_bytes.size();
    strm.total_out = 0;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;

    if (inflateInit2(&strm, (16 + MAX_WBITS)) != Z_OK)
    {
	    return false;
    }

    auto result = Z_OK;

    while (result == Z_OK)
    {
        // If the output buffer is too small
        if (strm.total_out >= uncompressed.size())
        {
            uncompressed.resize((uncompressed.size() * 3) / 2 + 1, 0);
        }

        strm.next_out = reinterpret_cast<Bytef*>(uncompressed.data() + strm.total_out);
        strm.avail_out = uncompressed.size() - strm.total_out;

        // Inflate another chunk.
        result = inflate(&strm, Z_SYNC_FLUSH);
    }

    if (inflateEnd(&strm) != Z_OK)
    {
	    return false;
    }

    for (auto i = std::size_t{ 0 }; i < strm.total_out; ++i)
    {
        uncompressed_bytes += uncompressed[i];
    }

    return true;
}

// Reads a file into memory
bool load_binary_file(const std::string& filename, std::string& contents)
{
    // Open the gzip file in binary mode
    auto file = std::fstream{ filename, std::ios::binary | std::ios::in };

    if (!file.is_open())
    {
	    return false;
    }

    contents.clear();

    // Read all the bytes in the file
    char buffer[1024] = {0};

    while (file.read(buffer, 1024))
    {
        contents.append(buffer, file.gcount());
    }

    return true;
}

int main()
{
    // Read the gzip file data into memory
    auto file_data = std::string{};
    if (!load_binary_file("test.gz", file_data))
    {
        std::cout << "Error loading input file." << std::endl;
        return 1;
    }

    // Uncompress the file data
    auto data = std::string{};
    if (!gzip_inflate(file_data, data))
    {
        std::cout << "Error decompressing file." << std::endl;
        return 1;
    }

    // Print the data
    for (auto i = std::size_t{ 0 }; i < data.size(); ++i)
    {
        std::cout << data[i];
    }
}
