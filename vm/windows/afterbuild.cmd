@echo off 

SET RDR=bc

SET NAME=librobovm-%RDR%
SET NAME=%OUTPUT_PATH%\%NAME%
copy /Y %NAME%.a %NAME%.a.ori 

SET RDR=core

SET NAME=librobovm-%RDR%
SET NAME=%OUTPUT_PATH%\%NAME%
copy /Y %NAME%.a %NAME%.a.ori 

SET RDR=rt

SET NAME=librobovm-%RDR%
SET NAME=%OUTPUT_PATH%\%NAME%
copy /Y %NAME%.a %NAME%.a.ori 

call %BASE%\patchlibs.cmd