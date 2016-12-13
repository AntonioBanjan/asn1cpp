/*
 * BerStreamParser.cpp
 *
 *  Created on: Oct 14, 2016
 *      Author: root
 */
#include "gtest/gtest.h"
#include "asn1/BerDecoder.h"
#include "asn1/BerDecodingHandler.h"
#include "asn1/Types.h"
#include <fstream>
#include <iostream>

using namespace asn1;

struct BerDecoderTestHandler: public BerDecodingHandler {

    ~BerDecoderTestHandler() {
    }

    void OnPrimitiveDefiniteValue(const Tag& refTag, const Length& refLength,
            std::istream& in) override {

        std::cout << "Tag --> constructed = " << refTag.Constructed()
                << " type = " << refTag.Number() << " class = "
                << refTag.Class() << " size = " << refLength.Size()
                << std::endl;
    }

    void OnPrimitiveStreamValue(const Tag& refTag, std::istream& in) override {

    }

    void OnConstructedValueBegin(const Tag& refTag, const Length& refLength)
            override {

        std::cout << "Tag-Begin --> constructed = " << refTag.Constructed()
                << " type = " << refTag.Number() << " class = "
                << refTag.Class() << " size = " << refLength.Size()
                << std::endl;
    }

    void OnConstructedValueEnd(const Tag& refTag, const Length& refLength)
            override {

        std::cout << "Tag-End --> constructed = " << refTag.Constructed()
                << " type = " << refTag.Number() << " class = "
                << refTag.Class() << std::endl;
    }

    void OnConstructedStreamValueBegin(const Tag& refTag) override {

        std::cout << "Tag-Begin --> constructed = " << refTag.Constructed()
                << " type = " << refTag.Number() << " class = "
                << refTag.Class() << " size = Indefinite" << std::endl;
    }

    void OnConstructedStreamValueEnd(const Tag& refTag) override {

        std::cout << "Tag-End --> constructed = " << refTag.Constructed()
                << " type = " << refTag.Number() << " class = "
                << refTag.Class() << " size = Indefinite" << std::endl;
    }
};

TEST(BerDecoderTest, TestParsingTag) {

    std::ifstream in("test.0");

    BerDecoderTestHandler objHandler;

    BerDecoder objDecoder(objHandler);

    objDecoder.Decode(in);

    in.close();
}

struct BerDecoderOIDTestHandler: public BerDecodingHandler {

    ~BerDecoderOIDTestHandler() {
    }

    void OnPrimitiveDefiniteValue(const Tag& refTag, const Length& refLength,
            std::istream& in) override {

        std::cout << "Tag --> constructed = " << refTag.Constructed()
                << " type = " << refTag.Number() << " class = "
                << refTag.Class() << " size = " << refLength.Size()
                << std::endl;

        if (refTag.Number() == Tag::OBJECT_IDENTIFIER) {

            std::string oid;

            in >> oid;

            std::cout << "OID := " << oid << std::endl;
        }
    }

    void OnPrimitiveStreamValue(const Tag& refTag, std::istream& in) override {

    }

    void OnConstructedValueBegin(const Tag& refTag, const Length& refLength)
            override {

        std::cout << "Tag-Begin --> constructed = " << refTag.Constructed()
                << " type = " << refTag.Number() << " class = "
                << refTag.Class() << " size = " << refLength.Size()
                << std::endl;
    }

    void OnConstructedValueEnd(const Tag& refTag, const Length& refLength)
            override {

        std::cout << "Tag-End --> constructed = " << refTag.Constructed()
                << " type = " << refTag.Number() << " class = "
                << refTag.Class() << " size = " << refLength.Size()
                << std::endl;
    }

    void OnConstructedStreamValueBegin(const Tag& refTag) override {

        std::cout << "Tag-Begin --> constructed = " << refTag.Constructed()
                << " type = " << refTag.Number() << " class = "
                << refTag.Class() << std::endl;
    }

    void OnConstructedStreamValueEnd(const Tag& refTag) override {

        std::cout << "Tag-End --> constructed = " << refTag.Constructed()
                << " type = " << refTag.Number() << " class = "
                << refTag.Class() << std::endl;
    }

};

TEST(BerDecoderTest, TestParsingOID) {

    std::ifstream in("test.0");

    BerDecoderOIDTestHandler objHandler;

    BerDecoder objDecoder(objHandler);

    objDecoder.Decode(in);

    in.close();
}

struct BerDecoderTestHandler2: public BerDecodingHandler {

    BerDecoderTestHandler2() :
            m_count(0ul) {
    }
    ~BerDecoderTestHandler2() {
    }

    void OnPrimitiveDefiniteValue(const Tag& refTag, const Length& refLength,
            std::istream& in) override {

        std::cout << this->m_count++ << ". Tag --> " << std::hex << "("
                << refTag.Raw() << ") constructed = " << refTag.Constructed()
                << " number = " << refTag.Number() << " class = "
                << refTag.Class() << " size = " << refLength.Size()
                << " data = ";

        if (refLength.Size() == 0ul) {

            std::cout << "Null-Value" << std::endl;
        } else {

            int c = 0;

            while ((c = in.get()) != -1) {

                std::cout << std::hex << c;
            }

            std::cout << std::endl;
        }
    }

    void OnConstructedValueBegin(const Tag& refTag, const Length& refLength)
            override {

//        if (refTag.Type() == Tag::SEQUENCE && refTag.Class() == Tag::UNIVERSAL) {

        std::cout << this->m_count++ << ". Tag-Begin --> " << std::hex << "("
                << refTag.Raw() << ") constructed = " << refTag.Constructed()
                << " number = " << std::dec << refTag.Number() << " class = "
                << refTag.Class() << " size = " << refLength.Size()
                << std::endl;
//        }
    }

    void OnConstructedValueEnd(const Tag& refTag, const Length& refLength)
            override {

        std::cout << this->m_count++ << ". Tag-End --> " << std::hex << "("
                << refTag.Raw() << ") constructed = " << refTag.Constructed()
                << " number = " << std::dec << refTag.Number() << " class = "
                << refTag.Class() << " size = " << refLength.Size()
                << std::endl;
    }

    void OnConstructedStreamValueBegin(const Tag& refTag) override {

        std::cout << this->m_count++ << ". Tag-Begin --> " << std::hex << "("
                << refTag.Raw() << ") constructed = " << refTag.Constructed()
                << " number = " << std::dec << refTag.Number() << " class = "
                << refTag.Class() << " size = Indefinite" << std::endl;
    }

    void OnConstructedStreamValueEnd(const Tag& refTag) override {

        std::cout << this->m_count++ << ". Tag-End --> " << std::hex << "("
                << refTag.Raw() << ") constructed = " << refTag.Constructed()
                << " number = " << std::dec << refTag.Number() << " class = "
                << refTag.Class() << " size = Indefinite" << std::endl;
    }

    void OnPrimitiveStreamValue(const Tag& refTag, std::istream& in) override {

        std::cout << this->m_count++ << ". Tag-Begin --> " << std::hex << "("
                << refTag.Raw() << ") constructed = " << refTag.Constructed()
                << " number = " << std::dec << refTag.Number() << " class = "
                << refTag.Class() << " size = Indefinite" << " data = ";
        int c = 0;

        while ((c = in.get()) != -1) {

            std::cout << std::hex << c;
        }

        std::cout << std::endl;

    }

private:
    std::size_t m_count;
};

TEST(BerDecoderTest, TestParsingAnotherFile) {

    std::ifstream in("RawStream");

    BerDecoderTestHandler2 objHandler;

    BerDecoder objDecoder(objHandler);

    objDecoder.Decode(in);

    in.close();
}

//class SequenceHandler: public BerDecodingHandler {
//
//public:
//    struct Activator {
//
//        using Criterion = std::function<bool(const Tag&, const Length&, std::istream&)>;
//
//        Activator(Sequence::ptr_t ptrSequence, Criterion& objCriterion) :
//                m_ptrSequence(ptrSequence), m_criterion(objCriterion) {
//        }
//
//        bool DoActivate() {
//
//        }
//
//    private:
//        Sequence::ptr_t m_ptrSequence;
//        Criterion m_criterion;
//    };
//
//    SequenceHandler(Sequence::ptr_t ptrSequence,
//            Activator::Criterion objCriterion) :
//            m_objActivator(ptrSequence, objCriterion) {
//
//    }
//
//    ~SequenceHandler() {
//    }
//
//    void OnPrimitiveValue(const Tag& refTag, const Length& refLength,
//            std::istream& in) override {
//
//        if (this->m_objActivator.DoActivate()) {
//
//        }
//    }
//
//    void OnConstructedValue(const Tag& refTag, const Length& refLength)
//            override {
//
//    }
//
//    void OnIndefiniteValue(const Tag& refTag, std::istream& in) override {
//
//    }
//
//private:
//    Activator m_objActivator;
//};
//
//TEST(BerDecoderTest, TestParsingSequence) {
//
//    std::ifstream in("RawStream");
//
//    SequenceHandler objHandler;
//
//    BerDecoder objDecoder(objHandler);
//
//    objDecoder.Decode(in);
//
//    in.close();
//}

