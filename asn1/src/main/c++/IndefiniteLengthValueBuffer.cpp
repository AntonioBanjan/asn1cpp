/*
 * IndefiniteLengthValueBuffer.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: root
 */

#include "asn1/internal/IndefiniteLengthValueBuffer.h"

inline
int IndefiniteLengthValueBuffer::uflow() {

    int c = 0;

    if ((c = this->underflow()) != traits_type::eof()) {

        this->m_in.sbumpc();

        return c;
    }

    return traits_type::eof();
}

inline
int IndefiniteLengthValueBuffer::underflow() {

    int c = this->m_in.sgetc();

    if ((c & 0xFF) == END_OF_CONTENT) {

        return traits_type::eof();
    }

    return c;
}
