// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� XHOOK_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// XHOOK_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef XHOOK_EXPORTS
#define XHOOK_API __declspec(dllexport)
#else
#define XHOOK_API __declspec(dllimport)
#endif

// �����Ǵ� xHook.dll ������
// class XHOOK_API CxHook
// {
// public:
//     CxHook(void);
//     // TODO: �ڴ�������ķ�����
// };

//extern XHOOK_API int nxHook;

//XHOOK_API int fnxHook(void);

XHOOK_API BOOL SetHook(DWORD tid);
