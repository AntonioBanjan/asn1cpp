/*
 * DefiniteValueBuffer.h
 *
 *  Created on: Nov 17, 2016
 *      Author: root
 */

#ifndef DEFINITELENGTHVALUEBUFFER_H_
#define DEFINITELENGTHVALUEBUFFER_H_

#include <streambuf>
#include <istream>

class DefiniteLengthValueBuffer final : public std::streambuf {

public:
    DefiniteLengthValueBuffer(std::istream& in, std::streamsize size) :
            m_in(in.rdbuf()), m_size(size) {
    }

    ~DefiniteLengthValueBuffer() {}

    int sync() override;

    int uflow() override;

    int underflow() override;

    traits_type::pos_type seekoff(traits_type::off_type offset, std::ios_base::seekdir seekDirection,
            std::ios_base::openmode mode/*__mode*/ = std::ios_base::in | std::ios_base::out) override;

    traits_type::pos_type seekpos(traits_type::pos_type pos,
          std::ios_base::openmode mode /*__mode*/ = std::ios_base::in | std::ios_base::out) override;

protected:
       std::streamsize
       xsgetn(char* ptr, std::streamsize size) override;

private:
    std::streambuf* m_in;
    std::streamsize m_size;
};

#endif /* DEFINITELENGTHVALUEBUFFER_H_ */
