@echo off
set "PREFIX=#define"
@setlocal disabledelayedexpansion
@for /f "delims=" %%F in (%~dp0\tv_all_uses.h.out) do @(
  set "LINE=%%F"
  setlocal EnableDelayedExpansion
  set "LINE=!LINE:%PREFIX%=!"
  echo !LINE! \
  endlocal
)