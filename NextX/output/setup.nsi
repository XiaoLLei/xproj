; The name of the installer
Name "xSearch"

; The file to write
OutFile "xSearch_setup.exe"

; The default installation directory
InstallDir "$PROGRAMFILES\Yuer\xSearch"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages
Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "��������"

  SectionIn RO

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File bdcommon.dll
  File bdxctrl.dll
  File bdxui.dll
  File xSearch.exe
  
  CreateDirectory $INSTDIR\resource
  CreateDirectory $INSTDIR\resource\skin
  SetOutPath $INSTDIR\resource\skin
  File /nonfatal ".\resource\skin\*.xml"
  File /nonfatal ".\resource\skin\*.png"
  
  WriteUninstaller "uninstall.exe"
  
SectionEnd ; end the section

Section "���������ݷ�ʽ"

	CreateShortCut "$DESKTOP\��������.lnk" "$INSTDIR\xSearch.exe" "" "$INSTDIR\xSearch.exe" 0

SectionEnd

; Optional section (can be disabled by the user)
Section "������ʼ�˵�"

  ; ������ݷ�ʽ
  CreateDirectory "$SMPROGRAMS\Yuer\xSearch"
  CreateShortCut "$SMPROGRAMS\Yuer\xSearch\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\Yuer\xSearch\xSearch(��������).lnk" "$INSTDIR\xSearch.exe" "" "$INSTDIR\xSearch.exe" 0
  
SectionEnd

; Uninstall
Section "Uninstall"

  ; Remove files and uninstaller
  Delete $INSTDIR\uninstall.exe
  Delete $INSTDIR\bdcommon.dll
  Delete $INSTDIR\bdxctrl.dll
  Delete $INSTDIR\bdxui.dll
  Delete $INSTDIR\xSearch.exe
  Delete $INSTDIR\resource\skin\*.xml
  Delete $INSTDIR\resource\skin\*.png
  
  ; Remove directories used
  RMDir "$INSTDIR\resource\skin"
  RMDir "$INSTDIR\resource"
  RMDir "$INSTDIR"
  RMDir "$PROGRAMFILES\Yuer"
  
  ; �Ƴ���ݷ�ʽ
  Delete "$DESKTOP\��������.lnk"
  
  ; �Ƴ���ʼ�˵�
  Delete "$SMPROGRAMS\Yuer\xSearch\*.*"
  RMDir "$SMPROGRAMS\Yuer\xSearch"

SectionEnd
