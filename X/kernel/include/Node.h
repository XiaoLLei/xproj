#pragma once
#include "xKernel/IxReceiveMessage.h"
#include "xKernel/IxNode.h"
#include "Element.h"

class CxNode
    : public CxElement
    , public IxNode
    , public IxReceiveMessage
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
    HRESULT GetDepth(LPINT pnDepth);

    // interface of IxReceiveMessage
    HRESULT OnMessage(LPEVENTPARAM params, LPBOOL pbHandled);

protected:
    INT _child_count() const
    {
        return static_cast<INT>(m_vecChildren.size());
    }

    virtual HRESULT _do_remove_child(IxNode* pNode);

    HRESULT _depth_change(EVENTPARAM& params);

protected:
    NODEVEC     m_vecChildren;
    IxNode*     m_pParent;
    INT         m_nDepth;
};