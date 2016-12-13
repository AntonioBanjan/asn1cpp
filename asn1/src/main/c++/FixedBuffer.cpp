/*
 * FixedBuffer.cpp
 *
 *  Created on: Nov 30, 2016
 *      Author: root
 */

#include "asn1/internal/FixedBuffer.h"

FixedBuffer::FixedBuffer(std::streamsize const size) : m_ptrData(new char[size]), m_size(size) {

    this->setg(this->m_ptrData.get(), this->m_ptrData.get(), this->m_ptrData.get() + size);
    this->setp(this->m_ptrData.get(), this->m_ptrData.get() + size);
}

FixedBuffer::~FixedBuffer() {}

std::streamsize
FixedBuffer::showmanyc() {

    return this->m_size;
}


