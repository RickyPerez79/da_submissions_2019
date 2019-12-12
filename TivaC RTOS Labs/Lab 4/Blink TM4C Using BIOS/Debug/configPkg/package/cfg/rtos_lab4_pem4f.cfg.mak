# invoke SourceDir generated makefile for rtos_lab4.pem4f
rtos_lab4.pem4f: .libraries,rtos_lab4.pem4f
.libraries,rtos_lab4.pem4f: package/cfg/rtos_lab4_pem4f.xdl
	$(MAKE) -f C:\Users\perez\WORKSP~1\BLINKT~1/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\perez\WORKSP~1\BLINKT~1/src/makefile.libs clean

