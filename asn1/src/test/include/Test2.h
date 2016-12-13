/*
 * Test2.h
 *
 *  Created on: Apr 7, 2015
 *      Author: root
 */

#ifndef TEST2_H_
#define TEST2_H_

#include "gtest/gtest.h"

class Test2 : public testing::Test {

public:
    Test2();
    virtual ~Test2();

    void SetUp();
    void TearDown();

protected:
    int m_anInt;
};

#endif /* TEST2_H_ */
