/*
 * DefiniteLengthValueBuffer.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: root
 */
#include "asn1/internal/DefiniteLengthValueBuffer.h"

inline
int DefiniteLengthValueBuffer::underflow() {

    if (this->m_size > 0) {

        return this->m_in->sgetc();
    }

    return traits_type::eof();
}

inline
int DefiniteLengthValueBuffer::uflow() {

    if (this->underflow() != traits_type::eof()) {

        --this->m_size;

        return this->m_in->sbumpc();

    }

    return traits_type::eof();
}

inline
int DefiniteLengthValueBuffer::sync() {

    return this->m_in->pubsync();
}

inline
DefiniteLengthValueBuffer::traits_type::pos_type DefiniteLengthValueBuffer::seekoff(
        traits_type::off_type offset, std::ios_base::seekdir seekDirection,
        std::ios_base::openmode mode) {

    return this->m_in->pubseekoff(offset, seekDirection, mode);
}

inline
DefiniteLengthValueBuffer::traits_type::pos_type DefiniteLengthValueBuffer::seekpos(
        traits_type::pos_type pos,
        std::ios_base::openmode mode) {

    return this->m_in->pubseekpos(pos, mode);
}

inline
std::streamsize DefiniteLengthValueBuffer::xsgetn(char* ptr,
        std::streamsize size) {

    return this->m_in->sgetn(ptr, size);
}

