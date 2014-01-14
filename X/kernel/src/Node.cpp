#include "stdafx.h"
#include "Node.h"

CxNode::CxNode()
    : m_pParent(NULL)
{}

CxNode::~CxNode()
{}

HRESULT CxNode::AddChild(IxNode* pNode)
{
    return AddChildAt(pNode, _child_count());
}

HRESULT CxNode::AddChildAt(IxNode* pNode, INT nIndex)
{
    if (!pNode) return E_POINTER;

    CComPtr<IxNode> spOldParent;
    pNode->GetParent(&spOldParent);
    if (spOldParent)
    {
        spOldParent->RemoveChild(pNode);
    }

    pNode->SetParent(GetEntity<IxNode>());

    m_vecChildren.insert(m_vecChildren.begin() + nIndex, pNode);

    return S_OK;
}

HRESULT CxNode::RemoveChild(IxNode* pNode)
{
    return _do_remove_child(pNode);
}

HRESULT CxNode::RemoveAllChildren()
{
    if (m_vecChildren.empty())
    {
        return S_FALSE;
    }

    while (!m_vecChildren.empty())
    {
        _do_remove_child(*m_vecChildren.rbegin());
    }

    return S_OK;
}

HRESULT CxNode::ReorderChild(IxNode* pNode, INT nIndex)
{
    if (nIndex < 0 || nIndex >= _child_count())
    {
        nIndex = _child_count() - 1;
    }

    if (m_vecChildren[nIndex] == pNode)
    {
        return S_FALSE;
    }

    NODEVEC::iterator iter = std::find(m_vecChildren.begin(), m_vecChildren.end(), pNode);

    if (iter == m_vecChildren.end())
    {
        return E_FAIL;
    }

    m_vecChildren.erase(iter);

    m_vecChildren.insert(m_vecChildren.begin() + nIndex, pNode);

    return S_OK;
}

HRESULT CxNode::GetChildrenCount(LPINT pnCount)
{
    if (!pnCount)   return E_POINTER;

    *pnCount = _child_count();

    return S_OK;
}

HRESULT CxNode::HasChild(LPBOOL pbHas)
{
    if (!pbHas) return E_POINTER;

    *pbHas = !m_vecChildren.empty();

    return S_OK;
}

HRESULT CxNode::GetChildByIndex(INT nIndex, IxNode** ppNode)
{
    if (!ppNode)    return E_POINTER;

    if (nIndex < 0 || nIndex >= _child_count())
    {
        return E_INVALIDARG;
    }

    return m_vecChildren[nIndex]->QueryInterface(__uuidof(IxNode), (void**)ppNode);
}

HRESULT CxNode::GetParent(IxNode** ppParent)
{
    if (!ppParent)  return E_POINTER;

    if (m_pParent)
        return m_pParent->QueryInterface(__uuidof(IxNode), (void**)ppParent);

    return E_FAIL;
}

HRESULT CxNode::SetParent(IxNode* pParent)
{
    m_pParent = pParent;
    return S_OK;
}

HRESULT CxNode::Contains(IxNode* pNode, LPBOOL pbContain)
{
    if (!pNode || !pbContain)
    {
        return E_FAIL;
    }

    *pbContain = FALSE;

    CComPtr<IxNode> spParent;
    pNode->GetParent(&spParent);
    while (spParent)
    {
        if (spParent == GetEntity<IxNode>())
        {
            *pbContain = TRUE;
            break;
        }

        CComPtr<IxNode> spNodeTmp;
        spParent->GetParent(&spNodeTmp);
        spParent = spNodeTmp;
    }

    return S_OK;
}

HRESULT CxNode::GetIndexOf(IxNode* pNode, LPINT pnIndex)
{
    if (!pNode || !pnIndex)
    {
        return E_FAIL;
    }

    *pnIndex = -1;

    NODEVEC::iterator it = std::find(m_vecChildren.begin(), m_vecChildren.end(), pNode);

    if (it != m_vecChildren.end())
    {
        *pnIndex = static_cast<INT>(it - m_vecChildren.begin());
    }

    return S_OK;
}

HRESULT CxNode::_do_remove_child(IxNode* pNode)
{
    if (!pNode) return E_FAIL;

    NODEVEC::reverse_iterator rit = std::find(m_vecChildren.rbegin(), m_vecChildren.rend(), pNode);

    if (rit != m_vecChildren.rbegin())
    {
        CComPtr<IxNode> spNode = *rit;
        if (spNode)
        {
            spNode->SetParent(GetEntity<IxNode>());
        }
        return S_OK;
    }
    else
    {
        return E_FAIL;
    }
}