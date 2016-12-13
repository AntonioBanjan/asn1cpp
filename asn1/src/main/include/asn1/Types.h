/*
 * Types.h
 *
 *  Created on: Oct 11, 2016
 *      Author: root
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <memory>
#include <istream>
#include <ostream>
#include <map>
#include <cstdint>
#include "asn1/Tag.h"
#include "asn1/Length.h"

namespace asn1 {

struct Type {

    using ptr_t = std::shared_ptr<Type>;

    Type() {
    }

    virtual ~Type() {
    }

    const Tag& GetTag() const {

        return this->m_tag;
    }

    const Length& GetLength() const {

        return this->m_length;
    }

    void SetTag(Tag&& rTag) {

        this->m_tag = rTag;
    }

    void SetLength(Length&& rLength) {

        this->m_length = rLength;
    }

    friend std::ostream& operator<<(std::ostream& out, const Type& refType) {

        refType.Serialize(out);

        return out;
    }

    friend std::ostream& operator<<(std::ostream& out, Type::ptr_t ptrType) {

        ptrType->Serialize(out);

        return out;
    }

    friend std::istream& operator>>(std::istream& in, Type::ptr_t ptrType) {

        ptrType->Deserialize(in);

        return in;
    }

    friend std::istream& operator>>(std::istream& in, Type& refType) {

        refType.Deserialize(in);

        return in;
    }

protected:
    virtual void Serialize(std::ostream&) const = 0;
    virtual void Deserialize(std::istream&) = 0;

protected:
    Tag m_tag;
    Length m_length;
};

class GenericType : public Type {

public:
    using ptr_t = std::shared_ptr<GenericType>;

    GenericType() : m_data(nullptr) {
    }


    ~GenericType() {

        delete[] this->m_data;
        this->m_data = nullptr;
    }

private:
    void Serialize(std::ostream& out) const override {


    }

    void Deserialize(std::istream& in) override {

        this->m_data = new char[this->m_length.Size()];

        in.get(this->m_data, this->m_length.Size());
    }

    char* m_data;
};

class Sequence: public Type {

public:

    struct NamedParam {

        NamedParam(const std::string& name, Type::ptr_t ptrParam)
            : m_name(name), m_ptrParam(ptrParam) {

        }

        ~NamedParam() {}

        const std::string& Name() const {

            return this->m_name;
        }

        Type::ptr_t Param() const {

            return this->m_ptrParam;
        }

        void Deserialize(std::istream& in) {

            in >> this->m_ptrParam;
        }

    private:
        std::string m_name;
        Type::ptr_t m_ptrParam;
    };

    Sequence(std::map<std::uint32_t, NamedParam> elements) :
        m_iter(m_objElements.begin()), m_objElements(elements) {

    }

    ~Sequence() {
    }

protected:
    void Deserialize(std::istream& in) override {

        auto& item = *(this->m_iter++);

        item.second.Deserialize(in);
    }

    void Serialize(std::ostream& out) const override {

    }

private:
    std::map<std::uint32_t, NamedParam>::iterator m_iter;
    std::map<std::uint32_t, NamedParam> m_objElements;
};

}

#endif /* TYPES_H_ */
