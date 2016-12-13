/*
 * BerStreamParser.cpp
 *
 *  Created on: Oct 14, 2016
 *      Author: root
 */

#include "asn1/BerDecoder.h"
#include "asn1/BerDecodingHandler.h"
#include "asn1/internal/IndefiniteLengthValueBuffer.h"
#include "asn1/internal/DefiniteLengthValueBuffer.h"

BerDecoder::BerDecoder(BerDecodingHandler& refHandler) :
        m_refHandler(refHandler), m_state(BerDecoder::PARSING_TAG) {
}

BerDecoder::~BerDecoder() {
}

void BerDecoder::Decode(std::istream& in) throw (std::exception) {

    if (in.bad()) {

        throw std::exception();
    }

    while (!in.eof()) {

        switch (this->m_state) {

        case BerDecoder::PARSING_TAG:

            this->OnDecodingTag(in);
            break;

        case BerDecoder::PARSING_LENGTH:

            this->OnDecodingLength(in);
            break;

        case BerDecoder::PARSING_VALUE_DEFINITE:

            this->OnDecodingDefiniteValue(in);
            break;

        case BerDecoder::PARSING_VALUE_INDEFINITE:

            this->OnDecodingIndefiniteValue(in);
            break;
        }
    }

}

void BerDecoder::OnDecodingTag(std::istream& in) {

    in >> this->m_currentTag;

    this->m_state = BerDecoder::PARSING_LENGTH;
}

void BerDecoder::OnDecodingLength(std::istream& in) {

    in >> this->m_currentLength;

    this->m_state = this->m_currentLength.Definite() ?
            PARSING_VALUE_DEFINITE : PARSING_VALUE_INDEFINITE;

}

void BerDecoder::OnDecodingDefiniteValue(std::istream& in) {

    this->m_state = PARSING_TAG;

    if (this->m_currentTag.Constructed()) {

        this->m_refHandler.HandleConstructedDefiniteValue(*this, this->m_currentTag,
                this->m_currentLength, in);
    } else {

        this->m_refHandler.HandlePrimitiveDefiniteValue(this->m_currentTag, this->m_currentLength, in);
    }
}

void BerDecoder::OnDecodingIndefiniteValue(std::istream& in) {

    this->m_state = BerDecoder::PARSING_TAG;

    if (this->m_currentTag.Constructed()) {

        this->m_refHandler.HandleConstructedIndefiniteValue(*this, this->m_currentTag, in);
    } else {

        this->m_refHandler.HandlePrimitiveIndefiniteValue(this->m_currentTag, in);
    }
}

