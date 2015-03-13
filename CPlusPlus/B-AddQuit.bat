@echo off
cls
setlocal EnableDelayedExpansion

for /d %%d in (*) do (
	for %%f in ("%%d\*.inp") do (
		echo \nquit>> "%%f"
	)
)