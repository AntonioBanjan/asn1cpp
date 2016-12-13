/*
 * BerDecodingHandler.cpp
 *
 *  Created on: Nov 23, 2016
 *      Author: root
 */

#include "asn1/BerDecodingHandler.h"
#include "asn1/BerDecoder.h"
#include "asn1/internal/DefiniteLengthValueBuffer.h"
#include "asn1/internal/IndefiniteLengthValueBuffer.h"
#include "asn1/Length.h"
#include "asn1/Tag.h"

void BerDecodingHandler::HandleConstructedDefiniteValue(BerDecoder& refDecoder,
        Tag objTag, Length objLength, std::istream& in) {

    this->OnConstructedValueBegin(objTag, objLength);

    DefiniteLengthValueBuffer objBuffer(in, objLength.Size());

    std::istream inValue(&objBuffer);

    refDecoder.Decode(inValue);

    this->OnConstructedValueEnd(objTag, objLength);
}

void BerDecodingHandler::HandlePrimitiveDefiniteValue(const Tag& refTag,
        const Length& refLength, std::istream& in) {

    if (!in.eof() && refLength.Size() > 0) {

        std::istream::pos_type pos = in.tellg();

        DefiniteLengthValueBuffer objBuffer(in, refLength.Size());

        std::istream objInValue(&objBuffer);

        this->OnPrimitiveDefiniteValue(refTag, refLength, objInValue);

        std::istream::pos_type posAfterHandling = in.tellg();

        std::streamsize currentLength = refLength.Size() > 0 ? refLength.Size() : 1;

        if (posAfterHandling - pos < currentLength) {

            std::istream::pos_type posDiff = pos + currentLength
                    - posAfterHandling;

            in.seekg(pos + posDiff);
        }
    }
}

void BerDecodingHandler::HandlePrimitiveIndefiniteValue(const Tag& refTag,
        std::istream& in) {

    if (!in.eof()) {

        IndefiniteLengthValueBuffer objBuffer(in);

        std::istream objInValue(&objBuffer);

        this->OnPrimitiveStreamValue(refTag, objInValue);

        while (in.get() != -1) {

            //consumes the stream until eof...
        }
    }
}

void BerDecodingHandler::HandleConstructedIndefiniteValue(
        BerDecoder& refDecoder, Tag objTag, std::istream& in) {

    this->OnConstructedStreamValueBegin(objTag);

    IndefiniteLengthValueBuffer objBuffer(in);

    std::istream inValue(&objBuffer);

    refDecoder.Decode(inValue);

    this->OnConstructedStreamValueEnd(objTag);
}

