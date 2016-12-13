/*
 * GenericBuffer.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: root
 */

#include "asn1/internal/GenericBuffer.h"

GenericBuffer::resize_strategy_t GenericBuffer::FIXED =
        [&](std::streamsize required, std::streamsize old) {throw BufferOverflowException(required, old);

            return 0;
        };

GenericBuffer::resize_strategy_t GenericBuffer::DYNAMIC_DEFAULT =
        [&](std::streamsize required, std::streamsize old) {

            std::streamsize newCapacity = required * 2;

            return newCapacity;
        };

GenericBuffer::GenericBuffer(resize_strategy_t& refStrategy,
        std::streamsize capacity) :
        m_resizeStrategy(refStrategy), m_capacity(capacity), m_ptrData(
                new char[m_capacity]) {

    this->setg(this->m_ptrData.get(), this->m_ptrData.get(),
            this->m_ptrData.get() + this->m_capacity);

    this->setp(this->m_ptrData.get(), this->m_ptrData.get() + this->m_capacity);
}

inline std::streamsize GenericBuffer::showmanyc() {

    return this->m_capacity;
}

inline
int GenericBuffer::overflow(int c) {

    this->Resize();

    *this->pptr() = c;

    this->pbump(1);

    return c;
}

inline GenericBuffer::traits_type::pos_type GenericBuffer::tellp() const {

    return this->pptr() - this->pbase();
}

void GenericBuffer::Resize() {

    std::streamsize newCapacity = this->m_resizeStrategy(
            this->m_capacity + sizeof(traits_type::char_type),
            this->m_capacity);

    std::unique_ptr<char> ptrNew = std::unique_ptr<char>(new char[newCapacity]);

    int bytesToCopy = this->pptr() - this->pbase();

    if (bytesToCopy > 0) {

        traits_type::copy(ptrNew.get(), this->m_ptrData.get(), bytesToCopy);
    }

    this->m_ptrData.swap(ptrNew);

    this->setp(this->m_ptrData.get(), this->m_ptrData.get() + newCapacity);

    this->pbump(bytesToCopy);

    this->m_capacity = newCapacity;

    this->setg(this->m_ptrData.get(), this->m_ptrData.get(),
            this->m_ptrData.get() + this->m_capacity);
}

std::istream& operator>>(std::istream& in, GenericBuffer& refBuffer) {

    std::streamsize size = in.gcount();

    if (refBuffer.epptr() - refBuffer.pptr() < size) {

        refBuffer.Resize();

        in >> refBuffer; // recursion

        return in;
    }

    in.get(refBuffer.pptr(), size);

    refBuffer.pbump(size);

    return in;
}

RangeCopy::RangeCopy(GenericBuffer& refBuffer, std::streamoff offset,
        std::streamsize size) :
        m_refBuffer(refBuffer), m_offset(offset), m_size(size) {
}

RangeCopy::RangeCopy(GenericBuffer& refBuffer, std::streamsize size) :
        m_refBuffer(refBuffer), m_offset(0), m_size(size) {
}

RangeCopy::~RangeCopy() {
}

std::istream&
RangeCopy::Do(std::istream& in) {

    if (this->m_refBuffer.epptr() - this->m_refBuffer.pptr() < this->m_size) {

        this->m_refBuffer.Resize();

        return this->Do(in);
    }

    int pos = this->m_refBuffer.pptr() - this->m_refBuffer.pbase();

    in.seekg(this->m_offset);

    in.get(this->m_refBuffer.m_ptrData.get() + pos, this->m_size + 1);

    this->m_refBuffer.pbump(this->m_size);

    return in;
}

std::istream& operator>>(std::istream& in, RangeCopy ref) {

    return ref.Do(in);

}

