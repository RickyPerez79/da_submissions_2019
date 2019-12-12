# invoke SourceDir generated makefile for app.pem3
app.pem3: .libraries,app.pem3
.libraries,app.pem3: package/cfg/app_pem3.xdl
	$(MAKE) -f C:\Users\chris\DOCUME~1\College\CPE403\CODECO~1\1350_lab5\collector_CC1350_LAUNCHXL_tirtos_ccs/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\chris\DOCUME~1\College\CPE403\CODECO~1\1350_lab5\collector_CC1350_LAUNCHXL_tirtos_ccs/src/makefile.libs clean

