/*
 * CppStreamTest.cpp
 *
 *  Created on: Nov 7, 2016
 *      Author: root
 */
#include "gtest/gtest.h"
#include <sstream>
#include "asn1/internal/IndefiniteLengthValueBuffer.h"
#include "asn1/internal/DefiniteLengthValueBuffer.h"
#include "asn1/internal/GenericBuffer.h"
#include <iostream>

TEST(CppStreamTest, TestDefiniteLengthValueBuffer) {

    std::string str("Hello World");

    std::stringstream in(str);

    DefiniteLengthValueBuffer objBuffer(in, 5ul);

    std::istream in1(&objBuffer);

    char c = 0x0;

    int i = 0;

    while (!in1.eof()) {

        in1 >> c;

        if (in1.eof()) {

            break;
        }

        EXPECT_EQ(str[i++], c);

        std::cout << "Character := " << c << std::endl;
    }
}

TEST(CppStreamTest, TestFixedBuffer) {

    GenericBuffer objBuffer(GenericBuffer::FIXED, 11);

    char data[] = "Hello World";

    objBuffer.sputn(data, strlen(data));

    std::stringstream strIn;

    strIn << &objBuffer;

    std::string str(strIn.str());

    EXPECT_STREQ("Hello World", str.c_str());

}

TEST(CppStreamTest, TestDynamicBuffer) {

    GenericBuffer objBuffer(GenericBuffer::DYNAMIC_DEFAULT, 2);

    char data[] = "Hello World & Hello World2 & Hello World3 & Hello World4";

    objBuffer.sputn(data, strlen(data) + 1);

    std::stringstream strIn;

    strIn << &objBuffer;

    std::string str(strIn.str());

    EXPECT_STREQ(data, str.c_str());
}

TEST(CppStreamTest, TestRangeCopyingFromStream) {

    GenericBuffer objBuffer(GenericBuffer::DYNAMIC_DEFAULT, 2);

    std::stringstream strIn("Hello World & Hello World2 & Hello World3 & Hello World4");

    strIn >> RangeCopy(objBuffer, 5) >> RangeCopy(objBuffer, 20, 6);

    char str[12];

    objBuffer.sgetn(str, 12);

    str[11] = 0x00;

    EXPECT_STREQ("HelloWorld2", str);
}

