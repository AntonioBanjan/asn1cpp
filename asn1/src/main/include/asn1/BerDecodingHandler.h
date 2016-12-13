/*
 * BerDecodingHandler.h
 *
 *  Created on: Nov 8, 2016
 *      Author: root
 */

#ifndef BERDECODINGHANDLER_H_
#define BERDECODINGHANDLER_H_

#include <istream>

class Tag;
class Length;
class BerDecoder;

struct BerDecodingHandler {

    BerDecodingHandler() {}
    virtual ~BerDecodingHandler() {}


    void HandleConstructedDefiniteValue(BerDecoder& refDecoder, Tag objTag, Length objLength, std::istream& in);
    void HandleConstructedIndefiniteValue(BerDecoder& refDecoder, Tag objTag, std::istream& in);
    void HandlePrimitiveIndefiniteValue(const Tag& refTag, std::istream& in);
    void HandlePrimitiveDefiniteValue(const Tag& refTag, const Length& refLength, std::istream& in);

private:
    virtual void OnPrimitiveDefiniteValue(const Tag& refTag, const Length& refLength, std::istream& in) = 0;
    virtual void OnConstructedValueBegin(const Tag& refTag, const Length& refLength) = 0;
    virtual void OnConstructedValueEnd(const Tag& refTag, const Length& refLength) = 0;
    virtual void OnConstructedStreamValueBegin(const Tag& refTag) = 0;
    virtual void OnConstructedStreamValueEnd(const Tag& refTag) = 0;
    virtual void OnPrimitiveStreamValue(const Tag& refTag, std::istream& in) = 0;
};


#endif /* BERDECODINGHANDLER_H_ */
