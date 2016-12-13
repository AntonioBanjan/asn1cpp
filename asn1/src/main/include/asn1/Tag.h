/*
 * Tag.h
 *
 *  Created on: Oct 18, 2016
 *      Author: root
 */

#ifndef TAG_H_
#define TAG_H_

class BerDecoder;

#include <istream>
#include <ostream>

struct Tag {

    typedef enum {

        UNIVERSAL = 0,
        APPLICATION = 1,
        CONTEXT_SPECIFIC = 2,
        PRIVATE = 3
    } tag_class_t;

    typedef enum {

        END_OF_CONTENT      = 0x0,
        BOOLEAN             = 0x01,
        INTEGER             = 0x02,
        BIT_STRING          = 0x03,
        OCTET_STRING        = 0x04,
        NULL_TYPE           = 0x05,
        OBJECT_IDENTIFIER   = 0x06,
        OBJECT_DESCRIPTOR   = 0x07,
        EXTERNAL            = 0x08,
        REAL                = 0x09,
        ENUMERATED          = 0x0A,
        EMBEDDED_PDV        = 0x0B,
        UTF_8_STRING        = 0x0C,
        RELATIVE_OID        = 0x0D,
        RESERVED_0          = 0x0E,
        RESERVED_1          = 0x0F,
        SEQUENCE            = 0x10,
        SET                 = 0x11,
        NUMERIC_STRING      = 0x12,
        PRINTABLE_STRING    = 0x13,
        T61String           = 0x14,
        VIDEO_TEX_STRING    = 0x15,
        IA5STRING           = 0x16,
        UTC_TIME            = 0x17,
        GENERALIZED_TIME    = 0x18,
        GRAPHIC_STRING      = 0x19,
        VISIBLE_STRING      = 0x1A,
        GENERAL_STRING      = 0x1B,
        UNIVERSAL_STRING    = 0x1C,
        CHARACTER_STRING    = 0x1D,
        BMP_STRING          = 0x1E
    } tag_number_t;

    Tag() : m_isConstructed(false), m_number(END_OF_CONTENT), m_class(UNIVERSAL), m_raw(0x0) {}

   Tag(bool isConstructed, int type, tag_class_t aclass, char raw) : m_isConstructed(isConstructed), m_number(type)
        , m_class(aclass), m_raw(raw) {}

    ~Tag() {}

    bool Constructed() const {

        return this->m_isConstructed;
    }

    int Number() const {

        return this->m_number;
    }

    tag_class_t Class() const {

        return this->m_class;
    }

    int Raw() const {

        return this->m_raw;
    }

    friend std::istream& operator>>(std::istream& in, Tag& refTag);
    friend std::ostream& operator<<(std::ostream& out, const Tag& refTag);

private:

    void Constructed(bool isConstructed) {

        this->m_isConstructed = isConstructed;
    }

    void Number(int type) {

        this->m_number = type;
    }

    void Class(tag_class_t aClass) {

        this->m_class = aClass;
    }

    void Raw(char raw) {

        this->m_raw = raw;
    }

    bool m_isConstructed;
    int m_number;
    tag_class_t m_class;
    char m_raw;
};



#endif /* TAG_H_ */
