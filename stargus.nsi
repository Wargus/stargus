!include "MUI.nsh"

;*** edit these defines to point to their correct locations ***;
!define STRATEXE "stratagus.exe"
!define SDLDLL "..\stratagus\SDL.dll"
!define STARINSTEXE "starinstall.exe"
!define SCMCONVERTEXE "scmconvert.exe"
!define MPQLIST "mpqlist.txt"
!define MANIFEST "Microsoft.VC80.CRT.manifest"
!define MSVCPDLL "msvcp80.dll"
!define MSVCRDLL "msvcr80.dll"

!define NAME "Stargus"
!define SGTMP "stargustemp"

Name "${NAME}"
OutFile "Stargus-0.1.exe"

;!define MUI_ICON "stratagus.ico"
;!define MUI_UNICON "stratagus.ico"

InstallDir "$PROGRAMFILES\${NAME}"
InstallDirRegKey HKCU "Software\${NAME}" ""

Var MUI_TEMP
Var STARTMENU_FOLDER

; pre-compilation tasks
!system "echo CVS>exc.txt"
!system "rmdir /Q /S ${SGTMP}"
!system "mkdir ${SGTMP}"
!system "mkdir ${SGTMP}\scripts"
!system "mkdir ${SGTMP}\contrib"
!system "xcopy /E scripts ${SGTMP}\scripts /EXCLUDE:exc.txt"
!system "xcopy /E contrib ${SGTMP}\contrib /EXCLUDE:exc.txt"
!system "rmdir /S /Q ${SGTMP}\scripts\.svn"
!system "rmdir /S /Q ${SGTMP}\scripts\ai\.svn"
!system "rmdir /S /Q ${SGTMP}\scripts\menus\.svn"
!system "rmdir /S /Q ${SGTMP}\scripts\neutral\.svn"
!system "rmdir /S /Q ${SGTMP}\scripts\terran\.svn"
!system "rmdir /S /Q ${SGTMP}\scripts\tilesets\.svn"
!system "rmdir /S /Q ${SGTMP}\contrib\.svn"
!system "erase exc.txt"


!define MUI_ABORTWARNING

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY

!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\${NAME}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
!insertmacro MUI_PAGE_STARTMENU Application $STARTMENU_FOLDER

!insertmacro MUI_PAGE_INSTFILES

!define MUI_FINISHPAGE_TEXT "Setup now needs to extract the data from Starcraft.\r\n\r\nNote: You will not be able to play Stargus until this is complete."
!define MUI_FINISHPAGE_RUN "$INSTDIR\starinstall.exe"
!define MUI_FINISHPAGE_RUN_TEXT "Extract Starcraft data now"
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"


Section "${NAME}" SecDummy
  SectionIn RO
  SetOutPath "$INSTDIR"
  File /r "${SGTMP}\*.*"
  File "${STRATEXE}"
  File "${SDLDLL}"
  File "${STARINSTEXE}"
  File "${SCMCONVERTEXE}"
  File "${MPQLIST}"
  File "${MANIFEST}"
  File "${MSVCPDLL}"
  File "${MSVCRDLL}"
  WriteRegStr HKCU "Software\${NAME}" "" $INSTDIR
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
    CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\${NAME}.lnk" "$INSTDIR\stratagus.exe"
    CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Extract Starcraft Data.lnk" "$INSTDIR\starinstall.exe"
    CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall.lnk" "$INSTDIR\uninstall.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
  WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd


Section "Uninstall"
  RMDir /r "$INSTDIR"

  !insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP

  Delete "$SMPROGRAMS\$MUI_TEMP\${NAME}.lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\Extract Starcraft Data.lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\Uninstall.lnk"
  RMDir "$SMPROGRAMS\$MUI_TEMP"

  DeleteRegKey /ifempty HKCU "Software\${NAME}"
SectionEnd

!system "rmdir /Q /S ${SGTMP}"
