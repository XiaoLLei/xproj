; 该脚本使用 HM VNISEdit 脚本编辑器向导产生

; 安装程序初始定义常量
!define PRODUCT_NAME "xSearch"
!define PRODUCT_VERSION "1.0.0.1"
!define PRODUCT_PUBLISHER "Yuer Tech, Inc."
!define PRODUCT_WEB_SITE "http://www.nextxm.com"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\xSearch.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

; ------ MUI 现代界面定义 (1.67 版本以上兼容) ------
!include "MUI.nsh"

; MUI 预定义常量
!define MUI_ABORTWARNING
!define MUI_ICON "install.ico"
!define MUI_UNICON "uninstall.ico"

; 欢迎页面
!insertmacro MUI_PAGE_WELCOME
; 许可协议页面
!define MUI_LICENSEPAGE_CHECKBOX
!insertmacro MUI_PAGE_LICENSE "License.txt"
; 安装目录选择页面
!insertmacro MUI_PAGE_DIRECTORY
; 安装过程页面
!insertmacro MUI_PAGE_INSTFILES
; 安装完成页面
!define MUI_FINISHPAGE_RUN "$INSTDIR\xSearch.exe"
!insertmacro MUI_PAGE_FINISH

; 安装卸载过程页面
!insertmacro MUI_UNPAGE_INSTFILES

; 安装界面包含的语言设置
!insertmacro MUI_LANGUAGE "SimpChinese"

; 安装预释放文件
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI 现代界面定义结束 ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "xSearch_setup.exe"
InstallDir "$PROGRAMFILES\xSearch"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show
BrandingText "小鱼科技"

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  
  SetOverwrite ifnewer
  
  File "xSearch.exe"
  CreateDirectory "$SMPROGRAMS\xSearch"
  CreateShortCut "$SMPROGRAMS\xSearch\xSearch(搜鱼).lnk" "$INSTDIR\xSearch.exe"
  CreateShortCut "$DESKTOP\搜鱼.lnk" "$INSTDIR\xSearch.exe"
  File "bdxui.dll"
  File "bdxctrl.dll"
  File "bdcommon.dll"
  
  CreateDirectory "$SMPROGRAMS\xSearch\resource"
  CreateDirectory "$SMPROGRAMS\xSearch\resource\skin"
  SetOutPath "$INSTDIR\resource\skin"
  File "resource\skin\*.xml"
  File "resource\skin\*.png"
SectionEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\xSearch\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\xSearch\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\xSearch.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\xSearch.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

/******************************
 *  以下是安装程序的卸载部分  *
 ******************************/

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\bdcommon.dll"
  Delete "$INSTDIR\bdxctrl.dll"
  Delete "$INSTDIR\bdxui.dll"
  Delete "$INSTDIR\xSearch.exe"
  
  Delete "$INSTDIR\resource\skin\*.xml"
	Delete "$INSTDIR\resource\skin\*.png"
	
	RMDir  "$INSTDIR\resource\skin"
	RMDir  "$INSTDIR\resource"

  Delete "$SMPROGRAMS\xSearch\Uninstall.lnk"
  Delete "$SMPROGRAMS\xSearch\Website.lnk"
  Delete "$DESKTOP\搜鱼.lnk"
  Delete "$SMPROGRAMS\xSearch\xSearch(搜鱼).lnk"

  RMDir "$SMPROGRAMS\xSearch"

  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "您确实要完全移除 $(^Name) ，及其所有的组件？" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从您的计算机移除。"
FunctionEnd
