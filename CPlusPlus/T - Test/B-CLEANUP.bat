@echo off
del "Result_Console.txt"
del "Result_Transaction.txt"
del "*cout"
del "*tout"

for /d %%d in (*) do (
	del "%%d\*.cout"
	del "%%d\*.tout"
)

cls