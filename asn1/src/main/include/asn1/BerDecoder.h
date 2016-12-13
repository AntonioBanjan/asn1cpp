/*
 * BerStreamParser.h
 *
 *  Created on: Oct 14, 2016
 *      Author: root
 */

#ifndef BERSTREAMPARSER_H_
#define BERSTREAMPARSER_H_

#include <istream>
#include <streambuf>
#include "asn1/Tag.h"
#include "asn1/Length.h"

struct BerDecodingHandler;

class BerDecoder {

    using octet_t = unsigned char;

    typedef enum {

        PARSING_TAG = 0,
        PARSING_LENGTH,
        PARSING_VALUE_DEFINITE,
        PARSING_VALUE_INDEFINITE
    } State;

public:
    BerDecoder(BerDecodingHandler& refHandler);
    ~BerDecoder();
    void Decode(std::istream& in) throw (std::exception);

private:
    void OnDecodingTag(std::istream& in);
    void OnDecodingLength(std::istream& in);
    void OnDecodingDefiniteValue(std::istream& in);
    void OnDecodingIndefiniteValue(std::istream& in);

private:
    BerDecodingHandler& m_refHandler;
    State m_state;
    Tag m_currentTag;
    Length m_currentLength;
};



#endif /* BERSTREAMPARSER_H_ */
