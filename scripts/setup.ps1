New-Item -ItemType Directory -Force -Path ../libs/sqlite3
New-Item -ItemType Directory -Force -Path ../libs/webview2

Invoke-WebRequest "https://www.sqlite.org/2023/sqlite-amalgamation-3440000.zip" -OutFile ../libs/sqlite3/sqlite3.zip
Invoke-WebRequest "https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2/1.0.2151.40" -OutFile ../libs/webview2/webview2.zip

Expand-Archive ../libs/sqlite3/sqlite3.zip ../libs/sqlite3/ -Force
Expand-Archive ../libs/webview2/webview2.zip ../libs/webview2/ -Force

Copy-Item ../libs/sqlite3/sqlite-amalgamation-3440000/sqlite3.c ../libs/sqlite3/sqlite3.c -Force
Copy-Item ../libs/sqlite3/sqlite-amalgamation-3440000/sqlite3.h ../libs/sqlite3/sqlite3.h -Force

Remove-Item ../libs/sqlite3/sqlite3.zip -Force
Remove-Item ../libs/sqlite3/sqlite-amalgamation-3440000 -Force -Recurse
Remove-Item ../libs/webview2/webview2.zip -Force
