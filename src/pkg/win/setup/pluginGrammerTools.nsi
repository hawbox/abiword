; Tools plugins
; This is a file for creating an installer for Abiword Plugins using NSIS 
; Based on .nsi file created by Alan Horkan <horkana@tcd.ie>
; and modified by Michael D. Pritchett <mpritchett@attglobal.net>
; modified by Kenneth J Davis <jeremyd@computer.org>

; Do a Cyclic Redundancy Check to make sure the installer 
; was not corrupted by the download.  
CRCCheck on

; The name of the installer
Name "AbiWord's Grammar Tools Plugins"

; Personal build
Icon "..\..\pkg\win\setup\setup.ico"
UninstallIcon "..\..\pkg\win\setup\setup.ico"
; Trademarked build
;Icon "..\..\pkg\win\setup\setup_tm.ico"
;UninstallIcon "..\..\pkg\win\setup\setup_tm.ico"

OutFile "AbiWord_GrammarTools_Plugins.exe"

; License Information
LicenseText "This program is Licensed under the GNU General Public License (GPL)."
LicenseData "..\AbiSuite\Copying"

; The default installation directory
InstallDir $PROGRAMFILES\AbiSuite

; Registry key to check for directory (so if you install again, it will overwrite the old one automatically)
InstallDirRegKey HKLM SOFTWARE\Abisuite "Install_Dir"

; The text to prompt the user to enter a directory
ComponentText "This will install AbiWord's Tools Plugins on your computer."

; Different installation types (usual or with a plugin specific uninstaller)
InstType "Typical (default)"
InstType "Full"

; The text to prompt the user to enter a directory
DirText "Choose the AbiSuite directory where you previously installed Abiword:"

; For NSIS 2.xx
CheckBitmap ..\..\pkg\win\setup\modern.bmp

; The stuff that must be installed
; binary, license, or whatever
;Section "Tools Plugins (required)"
Section
	SectionIn 1 2

	;;;;
	; Testing clause to abort if required AbiWord.exe DLL does not exist
	IfFileExists "$INSTDIR\AbiWord\bin\AbiWord.exe" DoInstall 0

	MessageBox MB_ICONSTOP "Quitting the install process - AbiWord.exe not found"
	Quit

	DoInstall:
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; Set output path to the installation directory.
	SetOutPath $INSTDIR\AbiWord\plugins
  
	; Write the installation path into the registry
	;;WriteRegStr HKLM SOFTWARE\Abisuite "Install_Dir" "$INSTDIR"

SectionEnd

; REQUIRED
Section "AbiLink (grammar checker) Plugin"
	SectionIn 1 2 RO

	; Testing clause to Overwrite Existing Version - if exists
	IfFileExists "$INSTDIR\AbiWord\plugins\libAbiLinkGrammar.dll" 0 DoInstall
	
	MessageBox MB_YESNO "Overwrite Existing AikSaurus Plugin?" IDYES DoInstall
	
	DetailPrint "Skipping AikSaurus Plugin (already exists)!"
	Goto End

	DoInstall:
	File "libAbiLinkGrammar.dll"
	; Add data files
	File /r linkgrammardata

	End:
SectionEnd


; OPTIONAL Create Uninstaller for Plugin
Section "Create Uninstaller for Tools Plugins"
	SectionIn 2
	; Write the uninstall keys for Windows
	; N.B. This needs to include a version number or unique identifier.  
	; More than one version of Abiword but only one Control Panel.  
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\AbiwordToolsPlugins" "DisplayName" "AbiWord's Grammar Tools Plugins (remove only)"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\AbiwordToolsPlugins" "UninstallString" '"$INSTDIR\AbiWord\plugins\UninstallAbiWordGrammarToolsPlugins.exe"'

	; New Uninstaller 
	WriteUninstaller "AbiWord\plugins\UninstallAbiWordGrammarToolsPlugins.exe"

SectionEnd


; uninstall stuff
UninstallText "This will uninstall AbiWord's Grammar Tools Plugins. Hit next to continue."

; special uninstall section.
Section "Uninstall"

	MessageBox MB_OKCANCEL "This will delete all Grammar Tools plugins and associated files & registry entries?" IDOK DoUnInstall
	
	Abort "Quitting the uninstall process"

	DoUnInstall:
	; remove registry keys
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\AbiwordGrammarToolsPlugins"
	;;DeleteRegKey HKLM SOFTWARE\Abisuite

	; remove file assoications
	;DeleteRegKey HKCR ".ext"


	; AikSaurus
	Delete "$INSTDIR\libAbiLinkGrammar.dll"
	RMDir /r "$INSTDIR\linkgrammardata"

	; remove uninstaller
	Delete /REBOOTOK "$INSTDIR\UninstallAbiWordGrammarToolsPlugins.exe"

SectionEnd

; eof
