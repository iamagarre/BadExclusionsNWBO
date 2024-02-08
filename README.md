# BadExclusions Now With Better Opsec
BadExclusionsNWBO is an evolution from BadExclusions to identify folder custom or undocumented exclusions on AV/EDR,

# How it works?
BadExclusionsNWBO copies and runs Hook_Checker.exe in all folders and subfolders of a given path. You need to have Hook_Checker.exe on the same folder of BadExclusionsNWBO.exe. 

Hook_Checker.exe returns the number of EDR hooks.  If the number of hooks is 7 or less means folder has an exclusion otherwise the folder is not excluded.

# Original idea?
Since the release of BadExclusions I've been thinking on how to achieve the same results without creating that many noise. The solution came from another tool, https://github.com/asaurusrex/Probatorum-EDR-Userland-Hook-Checker. 

If you download Probatorum-EDR-Userland-Hook-Checker and you run it inside a regular folder and on folder with an specific type of exclusion you will notice a huge difference. All the information is on the Probatorum repository.

# Requirements
Each vendor apply exclusions on a different way. In order to get the list of folder exclusions an specific type of exclusion should be made. Not all types of exclusion and not all the vendors remove the hooks when they exclude a folder.

The user who runs BadExclusionsNWBO needs write permissions on the excluded folder in order to write Hook_Checker file and get the results.

# EDR Demo
https://github.com/iamagarre/BadExclusionsNWBO/assets/89855208/46982975-f4a5-4894-b78d-8d6ed9b1c8c4

