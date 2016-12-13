/*
 * Length.h
 *
 *  Created on: Oct 18, 2016
 *      Author: root
 */

#ifndef LENGTH_H_
#define LENGTH_H_

#include <ios>
#include <cstdint>
#include <istream>

struct Length {

    static Length INDEFINITE;

    Length() : m_isDefinite(false), m_size(0ul) {}

    Length(bool isDefinite, std::streamsize size) : m_isDefinite(isDefinite), m_size(size) {
    }

    ~Length() {}

    std::streamsize Size() const;

    bool Definite() const;

    friend std::istream& operator>>(std::istream& in, Length& refLength);
    friend std::ostream& operator<<(std::ostream& out, const Length& refLength);


private:
    void Size(std::streamsize size) {

        this->m_size = size;
    }

    void Definite(bool isDefinite) {

        this->m_isDefinite = isDefinite;
    }

    bool m_isDefinite;
    std::streamsize m_size;
};



#endif /* LENGTH_H_ */
