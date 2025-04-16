/**
 * @file Sha1.cpp
 *
 * This is module contains tests for the Sha1 funcions
 *
 * © 2024 by Hatem Nabli
 */

#include <gtest/gtest.h>
#include <Sha1/Sha1.hpp>
#include <sstream>

TEST(Sha1Tests, Sha1Tests_HashTestVector_Test) {
    struct TestVector
    {
        std::string input;
        std::string output;
    };

    const std::vector<TestVector> testVectors{
        {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
         "84983e441c3bd26ebaae4aa1f95129e5e54670f1"},
        {"abc", "a9993e364706816aba3e25717850c26c9cd0d89d"},
        {"", "da39a3ee5e6b4b0d3255bfef95601890afd80709"},
    };
    for (const auto& test : testVectors)
    { EXPECT_EQ(test.output, Sha1::Sha1String(test.input)); }
}

#ifdef INCLUDE_SHA1_TEST_LONG_VECTOR
TEST(Sha1Tests, Sha1Tests_HashLongTestVector_Test) {
    struct TestVector
    {
        std::string input;
        std::string output;
    };
    std::ostringstream builder;
    TestVector test{"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno",
                    "7789f0c9ef7bfc40d93311143dfbe69e2017f592"};
    for (size_t i = 0; i < 16777216; ++i)
    { builder << test.input; }
    EXPECT_EQ(test.output, Sha1::Sha1String(builder.str()));
}

#endif /* INCLUDE_SHA1_TEST_LONG_VECTOR */

TEST(Sha1Tests, HashToByteVector) {
    EXPECT_EQ(
        (std::vector<uint8_t>{0xa9, 0x99, 0x3e, 0x36, 0x47, 0x06, 0x81, 0x6a, 0xba, 0x3e, 0x25,
                              0x71, 0x78, 0x50, 0xc2, 0x6c, 0x9c, 0xd0, 0xd8, 0x9d

        }),
        Sha1::Sha1Bytes("abc"));
}
