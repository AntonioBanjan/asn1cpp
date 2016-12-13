/*
 * Test2.cpp
 *
 *  Created on: Apr 7, 2015
 *      Author: root
 */

#include "Test2.h"
#include "gtest/gtest.h"

Test2::Test2() : m_anInt(10) {


}

Test2::~Test2() {


}

void Test2::SetUp() {


}

void Test2::TearDown() {


}

TEST_F(Test2, TestTheInt) {

   ASSERT_EQ(10, this->m_anInt);
}


