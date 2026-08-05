@echo off
REM Spécifiez le chemin vers l'exécutable Python si nécessaire
set PYTHON_PATH=C:\Users\tlemair\AppData\Local\Microsoft\WindowsApps\python.exe

cd /d %~dp0\..\..

REM Exécuter le script Python avec des arguments fixes
python Doc/ConfigPrj/PythonTool_CodeGen/main.py ^
Doc\ConfigPrj\ExcelCfg\STM32H753ZI\STM32H753ZI_HwCfg.xlsx ^
Doc\ConfigPrj\ExcelCfg\Project_SoftwareCfg_V0.xlsm

echo Press any key to continue...
pause