# invoke SourceDir generated makefile for tiva_tirtos.pem4f
tiva_tirtos.pem4f: .libraries,tiva_tirtos.pem4f
.libraries,tiva_tirtos.pem4f: package/cfg/tiva_tirtos_pem4f.xdl
	$(MAKE) -f C:\Users\perez\workspace_v9\tivac_tirtos/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\perez\workspace_v9\tivac_tirtos/src/makefile.libs clean

