/*
 * GenericBuffer.h
 *
 *  Created on: Dec 6, 2016
 *      Author: root
 */

#ifndef GENERICBUFFER_H_
#define GENERICBUFFER_H_

#include <string>
#include <sstream>
#include <streambuf>
#include <memory>
#include <cstring>
#include <functional>
#include <exception>

class BufferOverflowException final : std::exception {

public:
    BufferOverflowException(std::streamsize required, std::streamsize available) {

        std::stringstream out("buffer overflow required = ");

        out << required << " available = " << available;

        this->m_message = out.str();
    }

    ~BufferOverflowException() {

    }

    const char* what() const noexcept override {

        return this->m_message.c_str();
    }

private:
    std::string m_message;
};

struct RangeCopy;

class GenericBuffer final : public std::streambuf {


public:
    friend RangeCopy;

    static const std::streamsize DEFAULT_INITIAL_CAPACITY = 1024;

    using resize_strategy_t = std::function<std::streamsize(std::streamsize, std::streamsize)>;

    static resize_strategy_t FIXED;

    static resize_strategy_t DYNAMIC_DEFAULT;

    GenericBuffer(resize_strategy_t& refStrategy = DYNAMIC_DEFAULT, std::streamsize capacity = 1024ul);

    ~GenericBuffer() {
    }

    std::streamsize showmanyc() override;

    int overflow(int c) override;

    traits_type::pos_type tellp() const;

    friend std::istream& operator>>(std::istream& in, GenericBuffer& refBuffer);

private:
    void Resize();

    resize_strategy_t m_resizeStrategy;
    std::streamsize m_capacity;
    std::unique_ptr<char> m_ptrData;
};

struct RangeCopy {

public:
    RangeCopy(GenericBuffer& refBuffer, std::streamoff offset, std::streamsize size);
    RangeCopy(GenericBuffer& refBuffer, std::streamsize size);

    ~RangeCopy();

    friend std::istream& operator>>(std::istream& in, RangeCopy ref);

private:
    std::istream& Do(std::istream& in);
    GenericBuffer& m_refBuffer;
    std::streamoff m_offset;
    std::streamsize m_size;
};

#endif /* GENERICBUFFER_H_ */
