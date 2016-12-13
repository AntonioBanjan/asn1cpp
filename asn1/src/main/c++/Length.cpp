/*
 * Length.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: root
 */

#include "asn1/Length.h"

Length Length::INDEFINITE;


bool Length::Definite() const {

    return this->m_isDefinite;
}


std::streamsize Length::Size() const {

    return this->m_size;
}

std::istream&
operator>>(std::istream& in, Length& refLength) {

    unsigned char firstLengthOctet;

    in >> firstLengthOctet;

    bool is8thBitSet = firstLengthOctet & (1 << 7);

    std::streamsize size = 0ul;

    size = firstLengthOctet & 0x7F;

    if (!is8thBitSet) {

//        value has definite short length form
        refLength.Size(size);
        refLength.Definite(true);

    } else if (is8thBitSet && size == 0) {

//        value is of indefinite length, has to parse for eoc
        refLength.Definite(false);

    } else if (is8thBitSet && size > 0) {

//        value has definite long length form
        refLength.Definite(true);

        std::streamsize noOfLengthOctets = size;

        size = 0;

        for (std::streamsize i = noOfLengthOctets; i > 0; --i) {

            unsigned char nextLengthOctet;

            in >> nextLengthOctet;

            size |= nextLengthOctet << (i - 1) * 8;
        }

        refLength.Size(size);
    }

    return in;
}

std::ostream&
operator<<(std::ostream& out, const Length& refLength) {

    return out;
}
