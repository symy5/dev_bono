cd common_qt
call _clean.bat
cd ..
cd lib_qt_node_editor
call _clean.bat
cd ..
cd main
call _clean.bat
cd ..
rmdir /Q /S Debug
rmdir /Q /S Release
rmdir /Q /S GeneratedFiles
del QtCore4.dll
del QtGui4.dll
del /A *.suo
del *.ncb
del dev_bonobon.exe
del dev_bonobon.ilk
del dev_bonobon.pdb
