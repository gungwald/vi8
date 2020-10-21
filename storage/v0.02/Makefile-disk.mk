# TODO: Correct this URL for the 2.0.3 version of ProDOS.
PRODOS_URL=https://mirrors.apple2.org.za/ftp.apple.asimov.net/images/masters/prodos/ProDOS_2_4_1.dsk
PRODOS_DSK=lib/prodos-2.0.3-boot.dsk
DISK=vi8.dsk
AC=java -jar lib/AppleCommander-ac-1.4.0.jar.java5.jar

disk: $(DISK)

$(DISK): $(PROGRAM)
	cp $(PRODOS_DSK) $@
	$(AC) -as $@ vi8 < $(PROGRAM) || $(RM) $(DISK)

#$(PRODOS_DSK):
#	#curl -o $(PRODOS_DSK) $(PRODOS_URL)

diskclean: clean
	$(RM) $(DISK)
