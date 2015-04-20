﻿; Script generated by the Inno Script Studio Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "SS-Link"
#define MyAppVersion "0.2"
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
PrivilegesRequired=none

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
Source: "..\3rdparty\Qt\D3Dcompiler_47.dll"; DestDir: "{app}\Qt\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\icudt53.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\icuin53.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\icuuc53.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\libEGL.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\libGLESV2.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\opengl32sw.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5Core.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5Gui.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5Multimedia.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5MultimediaWidgets.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5Network.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5OpenGL.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5Positioning.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5PrintSupport.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5Qml.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5Quick.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5Sensors.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5Sql.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5Svg.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5WebChannel.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5WebKit.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5WebKitWidgets.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\Qt5Widgets.dll"; DestDir: "{app}\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\audio\qtaudio_windows.dll"; DestDir: "{app}\audio\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\bearer\qgenericbearer.dll"; DestDir: "{app}\bearer\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\bearer\qnativewifibearer.dll"; DestDir: "{app}\bearer\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\iconengines\qsvgicon.dll"; DestDir: "{app}\iconengines\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\imageformats\qdds.dll"; DestDir: "{app}\imageformats\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\imageformats\qgif.dll"; DestDir: "{app}\imageformats\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\imageformats\qicns.dll"; DestDir: "{app}\imageformats\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\imageformats\qico.dll"; DestDir: "{app}\imageformats\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\imageformats\qjp2.dll"; DestDir: "{app}\imageformats\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\imageformats\qjpeg.dll"; DestDir: "{app}\imageformats\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\imageformats\qmng.dll"; DestDir: "{app}\imageformats\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\imageformats\qsvg.dll"; DestDir: "{app}\imageformats\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\imageformats\qtga.dll"; DestDir: "{app}\imageformats\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\imageformats\qtiff.dll"; DestDir: "{app}\imageformats\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\imageformats\qwbmp.dll"; DestDir: "{app}\imageformats\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\imageformats\qwebp.dll"; DestDir: "{app}\imageformats\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\mediaservice\dsengine.dll"; DestDir: "{app}\mediaservice\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\mediaservice\qtmedia_audioengine.dll"; DestDir: "{app}\mediaservice\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\mediaservice\wmfengine.dll"; DestDir: "{app}\mediaservice\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\platforms\qwindows.dll"; DestDir: "{app}\platforms\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\playlistformats\qtmultimedia_m3u.dll"; DestDir: "{app}\playlistformats\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\position\qtposition_positionpoll.dll"; DestDir: "{app}\position\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\printsupport\windowsprintersupport.dll"; DestDir: "{app}\printsupport\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\sensorgestures\qtsensorgestures_plugin.dll"; DestDir: "{app}\sensorgestures\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\sensorgestures\qtsensorgestures_shakeplugin.dll"; DestDir: "{app}\sensorgestures\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\sensors\qtsensors_dummy.dll"; DestDir: "{app}\sensors\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\sensors\qtsensors_generic.dll"; DestDir: "{app}\sensors\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\sqldrivers\qsqlite.dll"; DestDir: "{app}\sqldrivers\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\sqldrivers\qsqlmysql.dll"; DestDir: "{app}\sqldrivers\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\sqldrivers\qsqlodbc.dll"; DestDir: "{app}\sqldrivers\"; Flags: restartreplace uninsrestartdelete
Source: "..\3rdparty\Qt\sqldrivers\qsqlpsql.dll"; DestDir: "{app}\sqldrivers\"; Flags: restartreplace uninsrestartdelete
         
[Registry]
Root: "HKCU"; Subkey: "Software\Q\ss-link"; ValueType: string; ValueName: "email"; ValueData: "karoyqiu@qq.com"; Flags: uninsdeletekeyifempty
Root: "HKCU"; Subkey: "Software\Q\ss-link"; ValueType: binary; ValueName: "password"; ValueData: "40 00 42 00 79 00 74 00 65 00 41 00 72 00 72 00 61 00 79 00 28 00 00 00 00 00 00 00 0c 00 78 00 9c 00 cb 00 cc 00 c9 00 2f 00 4b 00 cd 00 c8 00 cf 00 4b 00 cf 00 c9 00 cc 00 03 00 00 00 20 00 f8 00 05 00 0f 00 29 00"; Flags: uninsdeletekeyifempty
Root: "HKCU"; Subkey: "Software\Q\ss-link\polipo"; ValueType: string; ValueName: "polipo"; ValueData: "{app}\polipo.exe"; Flags: uninsdeletekeyifempty
Root: "HKCU"; Subkey: "Software\Q\ss-link\sslocal"; ValueType: string; ValueName: "sslocal"; ValueData: "{app}\sslocal.exe"; Flags: uninsdeletekeyifempty
Root: "HKCU"; Subkey: "Software\Microsoft\Windows\CurrentVersion\Run"; ValueType: string; ValueName: "SS-Link"; ValueData: "{app}\ss-link.exe"; Flags: uninsdeletevalue; Tasks: autorun

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[ThirdParty]
UseRelativePaths=True
