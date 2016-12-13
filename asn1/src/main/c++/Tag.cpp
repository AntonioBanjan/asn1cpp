/*
 * Tag.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: root
 */

#include "asn1/Tag.h"

std::istream&
operator>>(std::istream& in, Tag& refTag) {

    unsigned char firstTagOctet;

    in >> firstTagOctet;

    int tagClass = (firstTagOctet & 0xC0) >> 6;

    int tagNumber = firstTagOctet & 0x1F;

    bool isConstructed = firstTagOctet & (1 << 5);

    if (Tag::UNIVERSAL > static_cast<Tag::tag_class_t>(tagClass)
            && tagNumber > Tag::tag_number_t::BMP_STRING) {

        unsigned char nextTagOctet;

        tagNumber = 0;

        do {

            in >> nextTagOctet;

            tagNumber |= nextTagOctet & 0x0F;

        } while ((nextTagOctet & (1 << 8)));
    }

    refTag.Constructed(isConstructed);
    refTag.Class(static_cast<Tag::tag_class_t>(tagClass));
    refTag.Number(tagNumber);
    refTag.Raw(firstTagOctet);

    return in;
}

std::ostream&
operator<<(std::ostream& out, const Tag& refTag) {

    return out;
}
