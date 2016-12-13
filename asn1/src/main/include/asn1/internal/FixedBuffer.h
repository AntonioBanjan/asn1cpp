/*
 * FixedBuffer.h
 *
 *  Created on: Nov 30, 2016
 *      Author: root
 */

#ifndef FIXEDBUFFER_H_
#define FIXEDBUFFER_H_

#include <streambuf>
#include <memory>

class FixedBuffer : public std::streambuf {

public:
    FixedBuffer(std::streamsize const size);
    ~FixedBuffer();
    std::streamsize showmanyc() override;

private:
    std::unique_ptr<char> m_ptrData;
    std::streamsize m_size;
};


#endif /* FIXEDBUFFER_H_ */
