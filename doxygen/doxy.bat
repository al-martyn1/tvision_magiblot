@call %~dp0\tv_all_uses_doxcfg.bat
@call %~dp0\tv_all_uses_sort.bat
@copy /A /Y %~dp0\doxygen_common.cfg+%~dp0\doxygen_html.cfg+%~dp0\tv_all_uses.cfg   %~dp0\doxygen.cfg
@doxygen %~dp0\doxygen.cfg > %~dp0\doxygen_html.log 2>&1