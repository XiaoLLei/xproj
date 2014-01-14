#pragma once

[
    object,
    uuid("C1668841-A352-4fc8-9666-1F87D42096CC"),
    pointer_default(unique)
]
__interface IxNode : IUnknown
{
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
};