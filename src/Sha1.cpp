/**
 * @file Sha1.cpp
 *
 * This is the implementation of the Sha1 funcions
 *
 * © 2024 by Hatem Nabli
 */

#include <stdint.h>
#include <Sha1/Sha1.hpp>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace
{
    /**
     * This function rotates the given argument left by the given number
     * of bits.
     *
     * @param[in] arg
     *     This is the argument to rotate.
     *
     * @param[in] bits
     *     This is the number of bits to rotate the argument.
     *
     * @return
     *     The rotated argument is returned.
     */
    uint32_t Rot(uint32_t arg, size_t bits) { return ((arg << bits) | (arg >> (32 - bits))); }
}  // namespace

namespace Sha1
{
    std::string Sha1(const std::string& data) { return Sha1String(data); }
    std::string Sha1String(const std::vector<uint8_t>& data) {
        const auto digest = Sha1Bytes(data);
        std::ostringstream digestStringBuilder;
        digestStringBuilder << std::hex << std::setfill('0');
        for (auto digestByte : digest)
        { digestStringBuilder << std::setw(2) << (int)digestByte; }
        return digestStringBuilder.str();
    }

    std::string Sha1String(const std::string& data) {
        std::vector<uint8_t> dataAsVector(data.length());
        if (!dataAsVector.empty())
        { (void)memcpy(dataAsVector.data(), data.c_str(), dataAsVector.size()); }
        return Sha1String(dataAsVector);
    }

    std::vector<uint8_t> Sha1Bytes(const std::vector<uint8_t>& data) {
        uint32_t h0 = 0x67452301;
        uint32_t h1 = 0xEFCDAB89;
        uint32_t h2 = 0x98BADCFE;
        uint32_t h3 = 0x10325476;
        uint32_t h4 = 0xC3D2E1F0;
        uint8_t chunk[64];
        uint32_t words[80];
        uint64_t ml = (uint64_t)data.size() * 8;
        for (size_t offset = 0; offset < data.size() + 9; offset += 64)
        {
            if (offset + 64 <= data.size())
            {
                (void)memcpy(chunk, &data[offset], 64);
            } else
            {
                (void)memset(chunk, 0, 64);
                if (offset < data.size())
                { (void)memcpy(chunk, &data[offset], data.size() - offset); }
                if (offset <= data.size())
                { chunk[data.size() - offset] = 0x80; }
                if (offset + 64 - data.size() >= 9)
                {
                    chunk[56] = (uint8_t)(ml >> 56);
                    chunk[57] = (uint8_t)(ml >> 48);
                    chunk[58] = (uint8_t)(ml >> 40);
                    chunk[59] = (uint8_t)(ml >> 32);
                    chunk[60] = (uint8_t)(ml >> 24);
                    chunk[61] = (uint8_t)(ml >> 16);
                    chunk[62] = (uint8_t)(ml >> 8);
                    chunk[63] = (uint8_t)ml;
                }
            }
            for (size_t i = 0; i < 16; ++i)
            {
                words[i] =
                    (((uint32_t)chunk[i * 4 + 0] << 24) | ((uint32_t)chunk[i * 4 + 1] << 16) |
                     ((uint32_t)chunk[i * 4 + 2] << 8) | (uint32_t)chunk[i * 4 + 3]);
            }
            for (size_t i = 16; i < 80; ++i)
            { words[i] = Rot(words[i - 3] ^ words[i - 8] ^ words[i - 14] ^ words[i - 16], 1); }
            uint32_t a = h0;
            uint32_t b = h1;
            uint32_t c = h2;
            uint32_t d = h3;
            uint32_t e = h4;
            for (size_t i = 0; i < 80; ++i)
            {
                uint32_t f, k;
                if (i < 20)
                {
                    f = (b & c) | ((~b) & d);
                    k = 0x5A827999;
                } else if (i < 40)
                {
                    f = b ^ c ^ d;
                    k = 0x6ED9EBA1;
                } else if (i < 60)
                {
                    f = (b & c) | (b & d) | (c & d);
                    k = 0x8F1BBCDC;
                } else
                {
                    f = b ^ c ^ d;
                    k = 0xCA62C1D6;
                }
                uint32_t temp = Rot(a, 5) + f + e + k + words[i];
                e = d;
                d = c;
                c = Rot(b, 30);
                b = a;
                a = temp;
            }
            h0 += a;
            h1 += b;
            h2 += c;
            h3 += d;
            h4 += e;
        }
        return {
            (uint8_t)((h0 >> 24) & 0xff), (uint8_t)((h0 >> 16) & 0xff),
            (uint8_t)((h0 >> 8) & 0xff),  (uint8_t)(h0 & 0xff),
            (uint8_t)((h1 >> 24) & 0xff), (uint8_t)((h1 >> 16) & 0xff),
            (uint8_t)((h1 >> 8) & 0xff),  (uint8_t)(h1 & 0xff),
            (uint8_t)((h2 >> 24) & 0xff), (uint8_t)((h2 >> 16) & 0xff),
            (uint8_t)((h2 >> 8) & 0xff),  (uint8_t)(h2 & 0xff),
            (uint8_t)((h3 >> 24) & 0xff), (uint8_t)((h3 >> 16) & 0xff),
            (uint8_t)((h3 >> 8) & 0xff),  (uint8_t)(h3 & 0xff),
            (uint8_t)((h4 >> 24) & 0xff), (uint8_t)((h4 >> 16) & 0xff),
            (uint8_t)((h4 >> 8) & 0xff),  (uint8_t)(h4 & 0xff),
        };
    }

    std::vector<uint8_t> Sha1Bytes(const std::string& data) {
        std::vector<uint8_t> dataAsVector(data.length());
        if (!dataAsVector.empty())
        { (void)memcpy(dataAsVector.data(), data.c_str(), dataAsVector.size()); }
        return Sha1Bytes(dataAsVector);
    }

}  // namespace Sha1
