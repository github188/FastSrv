@echo off
@echo =======================进行发布前清理
del /s /Q *.ncb
del /s /Q *.log
del /s /Q *.bak
del /s /Q *.ilk
del /s /Q *.pdb
del /s /Q *.obj
del /s /Q *.htm
del /s /Q *.o
del /s /Q *.idb
del /s /Q *.manifest
del /s /Q *.pch
del /s /Q *.dep
del /s /Q *.manifest.res
del /s /Q *.user
del /s /Q *.d
del /s /Q *.filepart
del /s /Q *.db
del /s /Q *.sdf
del /s /Q /a:h-s *.suo
@echo =======================删除 Debug 文件夹
for /f "delims=" %%a in ('dir /ad /s /b ".\" ^| "C:\Windows\System32\findstr.exe" "\Debug$"') do (
rd /s /q %%a
)
@echo =======================删除 build 文件夹
for /f "delims=" %%a in ('dir /ad /s /b ".\" ^| "C:\Windows\System32\findstr.exe" "\build$"') do (
rd /s /q %%a
)
@echo =======================删除 data 文件夹
for /f "delims=" %%a in ('dir /ad /s /b ".\" ^| "C:\Windows\System32\findstr.exe" "\data$"') do (
rd /s /q %%a
)
@echo =======================删除 log 文件夹
for /f "delims=" %%a in ('dir /ad /s /b ".\" ^| "C:\Windows\System32\findstr.exe" "\log$"') do (
rd /s /q %%a
)
@echo =======================删除 ipch 文件夹
for /f "delims=" %%a in ('dir /ad /s /b ".\" ^| "C:\Windows\System32\findstr.exe" "\ipch$"') do (
rd /s /q %%a
)
@echo =======================删除 发布的 include 和 lib 文件夹
rd /s /q .\include
rd /s /q .\lib
@echo 运行完毕
pause
