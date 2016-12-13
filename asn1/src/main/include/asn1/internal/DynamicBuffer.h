/*
 * DynamicBuffer.h
 *
 *  Created on: Dec 1, 2016
 *      Author: root
 */

#ifndef DYNAMICBUFFER_H_
#define DYNAMICBUFFER_H_

#include <streambuf>
#include <memory>
#include <cstring>

class DynamicBuffer: public std::streambuf {

public:
    DynamicBuffer(std::streamsize capacity = 1024ul) :
            m_capacity(capacity), m_ptrData(new char[m_capacity]) {

        this->setg(this->m_ptrData.get(), this->m_ptrData.get(),
                this->m_ptrData.get() + this->m_capacity);
        this->setp(this->m_ptrData.get(),
                this->m_ptrData.get() + this->m_capacity);
    }

    ~DynamicBuffer() {
    }

    std::streamsize showmanyc() override {

        return this->m_capacity;
    }

    int overflow(int c) override {

        this->Resize();

        *this->pptr() = c;

        this->pbump(1);

        return c;
    }

private:
    void Resize() {

        std::unique_ptr<char> ptrNew = std::unique_ptr<char>(
                new char[this->m_capacity * 2]);

        traits_type::copy(ptrNew.get(), this->m_ptrData.get(), this->m_capacity);

        this->m_ptrData.swap(ptrNew);

        this->setp(this->m_ptrData.get(), this->m_ptrData.get() + this->m_capacity * 2);

        this->pbump(this->m_capacity);

        this->m_capacity *= 2;

        this->setg(this->m_ptrData.get(), this->m_ptrData.get(), this->m_ptrData.get() + this->m_capacity);
    }

    std::streamsize m_capacity;
    std::unique_ptr<char> m_ptrData;
};

#endif /* DYNAMICBUFFER_H_ */
