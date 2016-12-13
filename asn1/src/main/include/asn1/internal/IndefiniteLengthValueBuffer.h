/*
 * IndefiniteValueBuffer.h
 *
 *  Created on: Nov 15, 2016
 *      Author: root
 */
#ifndef INDEFINITEVALUEBUFFER_H_
#define INDEFINITEVALUEBUFFER_H_

#include <streambuf>
#include <istream>

class IndefiniteLengthValueBuffer final : public std::streambuf {

public:
    IndefiniteLengthValueBuffer(std::istream& in) :
            m_in(*in.rdbuf()) {
    }

    int uflow() override;

    int underflow() override;

private:
    static const char END_OF_CONTENT = 0x0;
    std::streambuf& m_in;
};

#endif /* INDEFINITEVALUEBUFFER_H_ */
