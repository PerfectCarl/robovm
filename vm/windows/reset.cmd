@echo off 

SET RDR=bc
SET NAME=librobovm-%RDR%

copy /Y %NAME%.a.ori %NAME%.a 

SET RDR=core
SET NAME=librobovm-%RDR%

copy /Y %NAME%.a.ori %NAME%.a

SET RDR=rt
SET NAME=librobovm-%RDR%

copy /Y %NAME%.a.ori %NAME%.a

call replace.cmd