# BadExclusions Now With Better Opsec
BadExclusionsNWBO is an evolution from BadExclusions to identify folder custom or undocumented exclusions on AV/EDR

![Screenshot](Img/results.png)

# How it works?
BadExclusionsNWBO copies and runs Hook_Checker in all folders and subfolders of a given path. If the number of hooks is 7 or less means folder has an exclusion.

# Original idea?
Since the release of BadExclusions I've been thinkning on how to achieve the same results without creating that many noise. The solution came from another tool, https://github.com/asaurusrex/Probatorum-EDR-Userland-Hook-Checker. If you download Probatorum-EDR-Userland-Hook-Checker and you run it inside a regular folder and a folder with an exclusion you will notice a huge difference. All the information is on the Probatorum repository.
