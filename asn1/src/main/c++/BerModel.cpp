/*
 * BerModel.cpp
 *
 *  Created on: Nov 23, 2016
 *      Author: root
 */
#include "asn1/internal/BerModel.h"



void PrimitiveBerNode::Accept(BerNodeVisitor& refVisitor) {

    refVisitor.Visit(this->shared_from_this());
}

void ContentCompositeBerNode::Accept(BerNodeVisitor& refVisitor) {

    refVisitor.Visit(this->shared_from_this());
}

void OffsetCompositeBerNode::Accept(BerNodeVisitor& refVisitor) {

    refVisitor.Visit(this->shared_from_this());
}
