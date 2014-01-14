#pragma once
#include "xKernel/IxNode.h"
#include "Element.h"

class CxNode
    : public CxElement
    , public IxNode
{
public:
    typedef std::vector< CComPtr<IxNode> > NODEVEC;

public:
    CxNode();
    virtual ~CxNode();

public:
    // interface of IxNode
    HRESULT AddChild(IxNode* pNode);
    HRESULT AddChildAt(IxNode* pNode, INT nIndex);
    HRESULT RemoveChild(IxNode* pNode);
    HRESULT RemoveAllChildren();
    HRESULT ReorderChild(IxNode* pNode, INT nIndex);
    HRESULT GetChildrenCount(LPINT pnCount);
    HRESULT HasChild(LPBOOL pbHas);
    HRESULT GetChildByIndex(INT nIndex, IxNode** ppNode);
    HRESULT GetParent(IxNode** ppParent);
    HRESULT SetParent(IxNode* pParent);
    HRESULT Contains(IxNode* pNode, LPBOOL pbContain);
    HRESULT GetIndexOf(IxNode* pNode, LPINT pnIndex);

protected:
    INT _child_count() const
    {
        return static_cast<INT>(m_vecChildren.size());
    }

    virtual HRESULT _do_remove_child(IxNode* pNode);

protected:
    NODEVEC     m_vecChildren;
    IxNode*     m_pParent;
};