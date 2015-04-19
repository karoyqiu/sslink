﻿; Script generated by the Inno Script Studio Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "SS-Link"
#define MyAppVersion "0.1"
#define MyAppPublisher "Q"
#define MyAppExeName "ss-link.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{BDBB2F14-C56C-40DD-BE66-6DE6D350B312}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
OutputBaseFilename=ss-link-x64-setup
Compression=lzma
SolidCompression=yes
ShowLanguageDialog=auto
ArchitecturesInstallIn64BitMode=x64 ia64
ArchitecturesAllowed=x64 ia64
MinVersion=0,6.1
OutputDir=..\output

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "chinesesimplified"; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "autorun"; Description: "{cm:AutoStartProgram,{#MyAppName}}"; GroupDescription: "{cm:AutoStartProgramGroupDescription}"

[Files]
Source: "..\..\build-ss-link\release\ss-link.exe"; DestDir: "{app}"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\polipo-win32.exe"; DestDir: "{app}"; DestName: "polipo.exe"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\3rdparty\shadowsocks-libqss-win64.exe"; DestDir: "{app}"; DestName: "sslocal.exe"; Flags: restartreplace uninsrestartdelete

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[ThirdParty]
UseRelativePaths=True

[Registry]
Root: "HKCU"; Subkey: "Software\Q\ss-link"; ValueType: string; ValueName: "email"; ValueData: "karoyqiu@qq.com"; Flags: uninsdeletekeyifempty
Root: "HKCU"; Subkey: "Software\Q\ss-link"; ValueType: binary; ValueName: "password"; ValueData: "40 00 42 00 79 00 74 00 65 00 41 00 72 00 72 00 61 00 79 00 28 00 00 00 00 00 00 00 0c 00 78 00 9c 00 cb 00 cc 00 c9 00 2f 00 4b 00 cd 00 c8 00 cf 00 4b 00 cf 00 c9 00 cc 00 03 00 00 00 20 00 f8 00 05 00 0f 00 29 00"; Flags: uninsdeletekeyifempty
Root: "HKCU"; Subkey: "Software\Q\ss-link\polipo"; ValueType: string; ValueName: "polipo"; ValueData: "{app}\polipo.exe"; Flags: uninsdeletekeyifempty
Root: "HKCU"; Subkey: "Software\Q\ss-link\sslocal"; ValueType: string; ValueName: "sslocal"; ValueData: "{app}\sslocal.exe"; Flags: uninsdeletekeyifempty
Root: "HKCU"; Subkey: "Software\Microsoft\Windows\CurrentVersion\Run"; ValueType: string; ValueName: "SS-Link"; ValueData: "{app}\ss-link.exe"; Flags: uninsdeletevalue; Tasks: autorun