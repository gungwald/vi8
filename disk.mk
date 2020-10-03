
PRODOS_DSK=prodos-2.4.1.dsk
PRODOS_URL=https://mirrors.apple2.org.za/ftp.apple.asimov.net/images/masters/prodos/ProDOS_2_4_1.dsk
DISK=vi8.dsk
AC=java -jar lib/AppleCommander-ac-1.4.0.jar.java5.jar

disk: $(DISK)


$(DISK): $(PRODOS_DSK)
	cp $(PRODOS_DSK) $@
	$(AC) -as $@ $(PROGRAM) BIN < $(PROGRAM)

$(PRODOS_DSK):
	curl -o $(PRODOS_DSK) $(PRODOS_URL)

