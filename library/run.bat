@echo off
del .\accounts.txt
library < test_no_db.txt
library < test_new_db.txt
pause