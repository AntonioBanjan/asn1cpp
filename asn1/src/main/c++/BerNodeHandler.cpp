/*
 * BerNodeHandler.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: root
 */

#include "asn1/BerNodeHandler.h"
#include "asn1/internal/BerModel.h"
#include <memory>

void BerNodeHandler::OnPrimitiveDefiniteValue(const Tag& refTag,
        const Length& refLength, std::istream& in) {

//    std::ostream& out = this->m_ptrRootNode->DataOut();
//
//    PrimitiveBerNode::ptr ptrNewNode = std::make_shared<PrimitiveBerNode>(refTag, refLength, in, this->m_ptrCurrentNode);
//
//    this->m_ptrCurrentNode->AddChild(ptrNewNode);
}

void BerNodeHandler::OnConstructedValueBegin(const Tag& refTag,
        const Length& refLength) {

    if (this->m_ptrRootNode.get() == nullptr) {

        this->m_ptrRootNode = std::make_shared<ContentCompositeBerNode>(
                refTag, refLength);

        this->m_ptrCurrentNode = this->m_ptrRootNode;
    } else {

        OffsetCompositeBerNode::ptr ptrNewNode = std::make_shared<
                OffsetCompositeBerNode>(refTag, refLength,
                this->m_ptrCurrentNode);

        this->m_ptrCurrentNode = ptrNewNode;
    }
}

void BerNodeHandler::OnConstructedValueEnd(const Tag& refTag,
        const Length& refLength) {


}

void BerNodeHandler::OnConstructedStreamValueBegin(const Tag& refTag) {

//    if (this->m_ptrRootNode.get() == nullptr) {
//
//        this->m_ptrRootNode = std::make_shared<DynamicContentCompositeBerNode>(
//                refTag);
//    } else {
//
//    }
}

void BerNodeHandler::OnConstructedStreamValueEnd(const Tag& refTag) {


}
