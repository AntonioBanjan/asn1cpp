/*
 * BerNodeHandler.h
 *
 *  Created on: Nov 22, 2016
 *      Author: root
 */

#ifndef BERNODEHANDLER_H_
#define BERNODEHANDLER_H_

#include "asn1/BerDecodingHandler.h"
#include "asn1/internal/BerModel.h"

class BerNodeHandler : public BerDecodingHandler {

public:
    BerNodeHandler() : m_ptrCurrentNode(nullptr), m_ptrRootNode(nullptr) {}
    virtual ~BerNodeHandler() {}

    virtual void OnPduCreated(BerNode::ptr ptrTree) = 0;

    void OnConstructedValueBegin(const Tag& refTag, const Length& refLength) override;
    void OnConstructedValueEnd(const Tag& refTag, const Length& refLength) override;
    void OnConstructedStreamValueBegin(const Tag& refTag) override;
    void OnConstructedStreamValueEnd(const Tag& refTag) override;
    void OnPrimitiveDefiniteValue(const Tag& refTag, const Length& refLength, std::istream& in) override;
    void OnPrimitiveStreamValue(const Tag& refTag, std::istream& in) override;

private:
    CompositeBerNode::ptr m_ptrCurrentNode;
    ContentCompositeBerNode::ptr m_ptrRootNode;
};



#endif /* BERNODEHANDLER_H_ */
