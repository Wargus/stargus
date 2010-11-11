;
;    stargus.nsi - Windows NSIS Installer for Stargus
;    Copyright (C) 2010  Pali Rohár <pali.rohar@gmail.com>
;
;    This program is free software: you can redistribute it and/or modify
;    it under the terms of the GNU General Public License as published by
;    the Free Software Foundation, either version 2 of the License, or
;    (at your option) any later version.
;
;    This program is distributed in the hope that it will be useful,
;    but WITHOUT ANY WARRANTY; without even the implied warranty of
;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;    GNU General Public License for more details.
;
;    You should have received a copy of the GNU General Public License
;    along with this program.  If not, see <http://www.gnu.org/licenses/>.
;
;

!include "MUI2.nsh"

;--------------------------------

!define NAME "Stargus"
!define VERSION "2.2.5.4"
!define VIVERSION "${VERSION}"
!define HOMEPAGE "https://launchpad.net/stargus"
!define LICENSE "GPL v2"
!define COPYRIGHT "Copyright (c) 1998-2010 by The Stratagus Project and Pali Rohar"
!define STRATAGUS_NAME "Stratagus"
!define STRATAGUS_HOMEPAGE "https://launchpad.net/stratagus"

;--------------------------------

!define ICON "contrib/stargus.ico"
!define STARGUS "stargus.exe"
!define STARTOOL "startool.exe"
!define MPQLIST "mpqlist.txt"
!define UNINSTALL "uninstall.exe"
!define INSTALLER "${NAME}-${VERSION}.exe"
!define INSTALLDIR "$PROGRAMFILES\${NAME}\"
!define LANGUAGE "English"

!ifdef AMD64
!undef INSTALLER
!define INSTALLER "${NAME}-${VERSION}-x86_64.exe"
!undef INSTALLDIR
!define INSTALLDIR "$PROGRAMFILES64\${NAME}\"
!undef NAME
!define NAME "Stargus (64 bit)"
!undef STRATAGUS_NAME
!define STRATAGUS_NAME "Stratagus (64 bit)"
!endif

!define REGKEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}"
!define STRATAGUS_REGKEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${STRATAGUS_NAME}"

;--------------------------------

LangString INSTALLER_RUNNING ${LANG_ENGLISH} "${NAME} Installer is already running."
LangString NO_STRATAGUS ${LANG_ENGLISH} "${STRATAGUS_NAME} is not installed.$\nYou need ${STRATAGUS_NAME} to run ${NAME}!$\nFirst install ${STRATAGUS_NAME} from ${STRATAGUS_HOMEPAGE}"

LangString REMOVEPREVIOUS ${LANG_ENGLISH} "Removing previous installation"
LangString REMOVECONFIGURATION ${LANG_ENGLISH} "Removing configuration and data files:"

LangString EXTRACTDATA_FILES ${LANG_ENGLISH} "Extracting Starcraft data files..."
LangString EXTRACTDATA_FILES_FAILED ${LANG_ENGLISH} "Extracting Starcraft data files failed."

LangString EXTRACTDATA_PAGE_HEADER_TEXT ${LANG_ENGLISH} "Choose Starcraft Location"
LangString EXTRACTDATA_PAGE_HEADER_SUBTEXT ${LANG_ENGLISH} "Choose the folder in which are Starcraft data files."
LangString EXTRACTDATA_PAGE_TEXT_TOP ${LANG_ENGLISH} "Setup will extract Starcraft data files from the following folder. You can specify location of CD or install location of Starcraft data files. Note that you need the original Starcraft CD to extract the game data files."
LangString EXTRACTDATA_PAGE_TEXT_DESTINATION ${LANG_ENGLISH} "Source Folder"
LangString EXTRACTDATA_PAGE_NOT_VALID ${LANG_ENGLISH} "This is not valid Starcraft data directory. File $DATADIRstardat.mpq does not exist."

LangString DESC_REMOVEEXE ${LANG_ENGLISH} "Remove ${NAME} binary executables"
LangString DESC_REMOVECONF ${LANG_ENGLISH} "Remove all other configuration and extracted data files and directories in ${NAME} install directory created by user or ${NAME}"

!ifdef AMD64
LangString AMD64ONLY ${LANG_ENGLISH} "This version is for 64 bits computers only."
!endif

;--------------------------------

!ifndef NO_DOWNLOAD
!system "wget http://nsis.sourceforge.net/mediawiki/images/0/0f/ExecDos.zip -O ExecDos.zip"
!system "unzip -j -o ExecDos.zip Plugins/ExecDos.dll"
!endif

!addplugindir .

;--------------------------------

SetCompressor lzma

Var STARTMENUDIR
Var DATADIR
Var EXTRACTNEEDED

!define MUI_ICON "${ICON}"
!define MUI_UNICON "${ICON}"

!define MUI_ABORTWARNING
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_FINISHPAGE_NOREBOOTSUPPORT
!define MUI_FINISHPAGE_RUN "$INSTDIR\${STARGUS}"
!define MUI_UNFINISHPAGE_NOAUTOCLOSE
!define MUI_UNFINISHPAGE_NOREBOOTSUPPORT
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKLM"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${REGKEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "StartMenu"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "COPYING"
!insertmacro MUI_PAGE_DIRECTORY

!define MUI_PAGE_HEADER_TEXT "$(EXTRACTDATA_PAGE_HEADER_TEXT)"
!define MUI_PAGE_HEADER_SUBTEXT "$(EXTRACTDATA_PAGE_HEADER_SUBTEXT)"
!define MUI_DIRECTORYPAGE_TEXT_TOP "$(EXTRACTDATA_PAGE_TEXT_TOP)"
!define MUI_DIRECTORYPAGE_TEXT_DESTINATION "$(EXTRACTDATA_PAGE_TEXT_DESTINATION)"
!define MUI_DIRECTORYPAGE_VARIABLE $DATADIR
!define MUI_DIRECTORYPAGE_VERIFYONLEAVE
!define MUI_PAGE_CUSTOMFUNCTION_PRE PageExtractDataPre
!define MUI_PAGE_CUSTOMFUNCTION_SHOW PageExtractDataShow
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE PageExtractDataLeave
!insertmacro MUI_PAGE_DIRECTORY

!insertmacro MUI_PAGE_STARTMENU Application $STARTMENUDIR
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_COMPONENTS
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "${LANGUAGE}"

;--------------------------------

Name "${NAME}"
Icon "${ICON}"
OutFile "${INSTALLER}"
InstallDir "${INSTALLDIR}"
InstallDirRegKey HKLM "${REGKEY}" "InstallLocation"

VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "${NAME} Installer"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${VERSION}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "InternalName" "${NAME} Installer"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "${COPYRIGHT}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "License" "${LICENSE}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "Homepage" "${HOMEPAGE}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "OriginalFilename" "${INSTALLER}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "${NAME} Installer"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductVersion" "${VERSION}"
VIProductVersion "${VIVERSION}"

BrandingText "${NAME} - ${VERSION}  ${HOMEPAGE}"
ShowInstDetails Show
ShowUnInstDetails Show
XPStyle on
RequestExecutionLevel admin

ReserveFile "${STARTOOL}"

;--------------------------------

Function .onInit

	System::Call 'kernel32::CreateMutexA(i 0, i 0, t "${NAME}") i .r1 ?e'
	Pop $0
	StrCmp $0 0 +3

	MessageBox MB_OK|MB_ICONEXCLAMATION "$(INSTALLER_RUNNING)"
	Abort

!ifdef AMD64

	System::Call "kernel32::GetCurrentProcess() i .s"
	System::Call "kernel32::IsWow64Process(i s, *i .r0)"
	IntCmp $0 0 0 0 +3

	MessageBox MB_OK|MB_ICONSTOP "$(AMD64ONLY)"
	Abort

!endif

	ReadRegStr $0 HKLM "${STRATAGUS_REGKEY}" "DisplayVersion"
	StrCmp $0 "" 0 +3

	MessageBox MB_OK|MB_ICONSTOP "$(NO_STRATAGUS)"
	Abort

	ReadRegStr $DATADIR HKLM "${REGKEY}" "DataDir"
	StrCmp $DATADIR "" 0 +2

	StrCpy $DATADIR "D:\"

FunctionEnd

;--------------------------------

Function PageExtractDataPre

	StrCpy $EXTRACTNEEDED "yes"

FunctionEnd

Function PageExtractDataShow

	FindWindow $0 "#32770" "" $HWNDPARENT
	GetDlgItem $1 $0 1023
	ShowWindow $1 0
	GetDlgItem $1 $0 1024
	ShowWindow $1 0

FunctionEnd

Function PageExtractDataLeave

	IfFileExists "$DATADIR\stardat.mpq" +3

	MessageBox MB_OK|MB_ICONSTOP "$(EXTRACTDATA_PAGE_NOT_VALID)"
	Abort

FunctionEnd

;--------------------------------

Section "-${NAME}" UninstallPrevious

        SectionIn RO

	ReadRegStr $0 HKLM "${REGKEY}" "InstallLocation"
	StrCmp $0 "" +7

	DetailPrint "$(REMOVEPREVIOUS)"
	SetDetailsPrint none
	ExecWait "$0\${UNINSTALL} /S _?=$0"
	Delete "$0\${UNINSTALL}"
	RMDir $0
	SetDetailsPrint lastused

SectionEnd

Section "${NAME}"

	SectionIn RO

	SetOutPath "$INSTDIR"
	File "${STARGUS}"
	File "${STARTOOL}"
	File "${MPQLIST}"

	SetOutPath "$INSTDIR\scripts"
	File /r /x .svn "scripts\"
	SetOutPath "$INSTDIR"

	CreateDirectory "$INSTDIR\graphics"
	CreateDirectory "$INSTDIR\graphics\tilesets"
	File "/oname=graphics\tilesets\fog.png" "contrib\fog.png"

	!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
	CreateDirectory "$SMPROGRAMS\$STARTMENUDIR"
	CreateShortCut "$SMPROGRAMS\$STARTMENUDIR\${NAME}.lnk" "$INSTDIR\${STARGUS}"
	CreateShortCut "$SMPROGRAMS\$STARTMENUDIR\Uninstall.lnk" "$INSTDIR\${UNINSTALL}"
	CreateShortcut "$DESKTOP\${NAME}.lnk" "$INSTDIR\${STARGUS}"
	!insertmacro MUI_STARTMENU_WRITE_END

	WriteRegStr HKLM "${REGKEY}" "DisplayName" "${NAME}"
	WriteRegStr HKLM "${REGKEY}" "UninstallString" "$\"$INSTDIR\${UNINSTALL}$\""
	WriteRegStr HKLM "${REGKEY}" "QuietUninstallString" "$\"$INSTDIR\${UNINSTALL}$\" /S"
	WriteRegStr HKLM "${REGKEY}" "InstallLocation" "$INSTDIR"
	WriteRegStr HKLM "${REGKEY}" "DisplayIcon" "$\"$INSTDIR\${STARGUS}$\",0"
	WriteRegStr HKLM "${REGKEY}" "DisplayVersion" "${VERSION}"
	WriteRegStr HKLM "${REGKEY}" "HelpLink" "${HOMEPAGE}"
	WriteRegStr HKLM "${REGKEY}" "URLUpdateInfo" "${HOMEPAGE}"
	WriteRegStr HKLM "${REGKEY}" "URLInfoAbout" "${HOMEPAGE}"
	WriteRegDWORD HKLM "${REGKEY}" "NoModify" 1
	WriteRegDWORD HKLM "${REGKEY}" "NoRepair" 1
	WriteRegStr HKLM "${REGKEY}" "DataDir" "$DATADIR"
	WriteRegStr HKLM "${STRATAGUS_REGKEY}\Games" "${NAME}" "${VERSION}"

	WriteUninstaller "$INSTDIR\${UNINSTALL}"

SectionEnd

Section "${NAME}" ExtractData

	StrCmp "$EXTRACTNEEDED" "no" end

	AddSize 542920

	DetailPrint ""
	DetailPrint "$(EXTRACTDATA_FILES)"
	ExecDos::exec /DETAILED "$\"$INSTDIR\${STARTOOL}$\" $\"$DATADIR\data$\" $\"$INSTDIR$\""
	Pop $0
	IntCmp $0 0 +3

	MessageBox MB_OK|MB_ICONSTOP "$(EXTRACTDATA_FILES_FAILED)"
	Abort

	SetOutPath "$INSTDIR"

end:

SectionEnd

;--------------------------------

Section "un.${NAME}" Executable

	SectionIn RO

	Delete "$INSTDIR\${STARGUS}"
	Delete "$INSTDIR\${STARTOOL}"
	Delete "$INSTDIR\${MPQLIST}"
	Delete "$INSTDIR\graphics\tilesets\fog.png"
	RMDir "$INSTDIR\graphics\tilesets"
	RMDir "$INSTDIR\graphics"
	RMDir /r "$INSTDIR\scripts"
	RMDir "$INSTDIR"

	!insertmacro MUI_STARTMENU_GETFOLDER Application $STARTMENUDIR
	Delete "$SMPROGRAMS\$STARTMENUDIR\${NAME}.lnk"
	Delete "$SMPROGRAMS\$STARTMENUDIR\Uninstall.lnk"
	RMDir "$SMPROGRAMS\$STARTMENUDIR"
	Delete "$DESKTOP\${NAME}.lnk"

	DeleteRegKey HKLM "${REGKEY}"
	DeleteRegValue HKLM "${STRATAGUS_REGKEY}\Games" "${NAME}"

	ClearErrors
	EnumRegValue $0 HKLM "${REGKEY}\Games" 0
	IfErrors +2

	DeleteRegKey /ifempty HKLM "${STRATAGUS_REGKEY}\Games"

SectionEnd

Section /o "un.Configuration" Configuration

	DetailPrint "$(REMOVECONFIGURATION)"
	RMDir /r "$INSTDIR"

SectionEnd

!insertmacro MUI_UNFUNCTION_DESCRIPTION_BEGIN
!insertmacro MUI_DESCRIPTION_TEXT "${Executable}" "$(DESC_REMOVEEXE)"
!insertmacro MUI_DESCRIPTION_TEXT "${Configuration}" "$(DESC_REMOVECONF)"
!insertmacro MUI_UNFUNCTION_DESCRIPTION_END

;--------------------------------

!packhdr "exehead.tmp" "upx -9 exehead.tmp"
;!finalize "gpg --armor --sign --detach-sig %1"

;--------------------------------

!ifndef NO_DOWNLOAD
!delfile "ExecDos.dll"
!delfile "ExecDos.zip"
!endif

;--------------------------------
