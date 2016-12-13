/*
 * BerModel.h
 *
 *  Created on: Nov 22, 2016
 *      Author: root
 */

#ifndef BERMODEL_H_
#define BERMODEL_H_

#include "asn1/Tag.h"
#include "asn1/Length.h"
#include <memory>
#include <vector>
#include <istream>
#include "asn1/internal/GenericBuffer.h"

struct BerNodeVisitor;

struct BerNode {

    using ptr = std::shared_ptr<BerNode>;

    BerNode() {}
    BerNode(const Tag& refTag, const Length& refLength, BerNode::ptr ptrParent = nullptr)
        : m_objTag(refTag), m_objLength(refLength), m_ptrParent(ptrParent)  {}
    virtual ~BerNode() {}

    const Tag& GetTag() const {

        return this->m_objTag;
    }

    const Length& GetLength() const {

        return this->m_objLength;
    }

    BerNode::ptr Parent() const {

        return this->m_ptrParent;
    }

    bool HasParent() const {

        return this->m_ptrParent.get() != nullptr;
    }

    virtual void Accept(BerNodeVisitor& refVisitor) = 0;


private:
    Tag m_objTag;
    Length m_objLength;
    BerNode::ptr m_ptrParent;
};


class PrimitiveBerNode
        : public BerNode
          , public std::enable_shared_from_this<PrimitiveBerNode> {

public:
    using ptr = std::shared_ptr<PrimitiveBerNode>;

    PrimitiveBerNode(const Tag& refTag, const Length& refLength, std::istream& in
            , std::streampos pos, BerNode::ptr ptrParent = nullptr) : BerNode(refTag, refLength, ptrParent)
    , m_pos(pos) {
    }

    ~PrimitiveBerNode() { }

    void Accept(BerNodeVisitor& refVisitor) override;

private:
    std::streampos m_pos;
};

class CompositeBerNode : public BerNode {

public:
    using ptr = std::shared_ptr<CompositeBerNode>;

    CompositeBerNode(const Tag& refTag, const Length& refLength, BerNode::ptr ptrParent = nullptr) : BerNode(refTag, refLength, ptrParent) {}
    virtual ~CompositeBerNode() {}

    void AddChild(BerNode::ptr ptrNode) {

        this->m_objSubNodes.push_back(ptrNode);
    }

    const std::vector<BerNode::ptr>& Children() const {

        return this->m_objSubNodes;
    }

    std::vector<BerNode::ptr>& Children() {

        return this->m_objSubNodes;
    }

    virtual void Accept(BerNodeVisitor& refVisitor) = 0;

private:
    std::vector<BerNode::ptr> m_objSubNodes;
};

class ContentCompositeBerNode final :
        public CompositeBerNode
        , public std::enable_shared_from_this<ContentCompositeBerNode> {

public:
    using ptr = std::shared_ptr<ContentCompositeBerNode>;

    ContentCompositeBerNode(const Tag& refTag, const Length& refLength) :
    CompositeBerNode(refTag, refLength, nullptr)
        , m_objBuffer(refLength.Definite() ? GenericBuffer::FIXED : GenericBuffer::DYNAMIC_DEFAULT
                , refLength.Definite() ? refLength.Size() : GenericBuffer::DEFAULT_INITIAL_CAPACITY)
                , m_stream(&m_objBuffer) {
    }

    ~ContentCompositeBerNode() {}

    std::istream& DataIn() {

        return this->m_stream;
    }

    std::ostream& DataOut() {

        return this->m_stream;
    }

    void Accept(BerNodeVisitor& refVisitor) override;

private:
    GenericBuffer m_objBuffer;
    std::iostream m_stream;
};

class OffsetCompositeBerNode final
    : public CompositeBerNode
      , public std::enable_shared_from_this<OffsetCompositeBerNode> {

public:
    using ptr = std::shared_ptr<OffsetCompositeBerNode>;

    OffsetCompositeBerNode(const Tag& refTag, const Length& refLength, BerNode::ptr ptrParent = nullptr)
        : CompositeBerNode(refTag, refLength, ptrParent) {

    }

    ~OffsetCompositeBerNode() {}

    void Accept(BerNodeVisitor& refVisitor) override;
};

struct BerNodeVisitor {

    virtual ~BerNodeVisitor() {}
    virtual void Visit(PrimitiveBerNode::ptr ptrPrimitiveBerNode) = 0;
    virtual void Visit(ContentCompositeBerNode::ptr ptrContentCompositeBerNode) = 0;
    virtual void Visit(OffsetCompositeBerNode::ptr ptrOffsetCompositeBerNode) = 0;
};



#endif /* BERMODEL_H_ */
