#ifndef SHA1_HPP
#define SHA1_HPP

/**
 * @file Sha1.hpp
 * 
 * This module represent a declaration of Sha1 functions
 * 
 * © 2024 by Hatem Nabli
 */
#include <string>
#include <stdint.h>
#include <vector>

namespace Sha1 {
    
    /**
     * This calculate the SHA-1 message digest of a given data.
     * 
     * @param[in] data
     *      This is the input data for which to calculate the SHA-1
     *      message digest.
     * @return
     *      returns the SHA1 message digest of the given data as
     *      a string of hexadicimal digits. 
     */
    std::string Sha1String(const std::string& data);

    /**
     * This calculate the SHA-1 message digest of a given data.
     * 
     * @param[in] data
     *      This is the input data for which to calculate the SHA-1
     *      message digest.
     * @return
     *      returns the SHA1 message digest of the given data as
     *      a string of hexadicimal digits. 
     */
    std::string Sha1String(const std::vector< uint8_t>& data);

    /**
     * This calculate the SHA-1 message digest of a given data.
     * 
     * @param[in] data
     *      This is the input data for which to calculate the SHA-1
     *      message digest.
     * @return
     *      returns the SHA1 message digest of the given data as
     *      as a vector of hexadicimal digits. 
     */
    std::vector< uint8_t > Sha1Bytes(const std::vector< uint8_t >& data);

        /**
     * This function computes the SHA-1 message digest of the given data.
     *
     * @param[in] data
     *     This is the data for which to compute the message digest.
     *
     * @return
     *     The SHA1 message digest of the given data is returned
     *     as a vector of bytes.
     */
    std::vector< uint8_t > Sha1Bytes(const std::string& data);

}

#endif /* SHA1_HPP */