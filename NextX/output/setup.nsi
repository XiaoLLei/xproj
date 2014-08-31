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
Section "基础功能"

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

Section "创建桌面快捷方式"

	CreateShortCut "$DESKTOP\桌面助手.lnk" "$INSTDIR\xSearch.exe" "" "$INSTDIR\xSearch.exe" 0

SectionEnd

; Optional section (can be disabled by the user)
Section "创建开始菜单"

  ; 创建快捷方式
  CreateDirectory "$SMPROGRAMS\Yuer\xSearch"
  CreateShortCut "$SMPROGRAMS\Yuer\xSearch\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\Yuer\xSearch\xSearch(桌面助手).lnk" "$INSTDIR\xSearch.exe" "" "$INSTDIR\xSearch.exe" 0
  
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
  
  ; 移除快捷方式
  Delete "$DESKTOP\桌面助手.lnk"
  
  ; 移除开始菜单
  Delete "$SMPROGRAMS\Yuer\xSearch\*.*"
  RMDir "$SMPROGRAMS\Yuer\xSearch"

SectionEnd
