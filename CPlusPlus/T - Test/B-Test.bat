@echo off
cls
call "B-CLEANUP.bat"
setlocal EnableDelayedExpansion

for /d %%d in (*) do (
	echo ##### %%d>> "Result_Console.txt"
	echo ##### %%d>> "Result_Transaction.txt"

	for %%f in ("%%d\*.inp") do (
		echo %%f
		Project1.exe < %%f > "%%d\%%~nf.cout"
		
		rename "TransactionFile.txt" "%%~nf.tout"
		move "%%~nf.tout" %%d
		
		echo ===============================%%~nf===============================>> "Result_Console.txt"
		fc /n "%%d\%%~nf.bto" "%%d\%%~nf.cout" >> "Result_Console.txt"
		echo ===============================%%~nf===============================>> "Result_Transaction.txt"
		fc /n "%%d\%%~nf.etf" "%%d\%%~nf.tout" >> "Result_Transaction.txt"
	)
)