PRODOS_DSK=lib/prodos-2.0.3-boot.dsk
DISK=vi8.dsk
AC=java -jar lib/AppleCommander-ac-1.4.0.jar.java5.jar
PROGRAM=vi8
TARGET=apple2

disk: $(DISK)

$(DISK): $(PROGRAM)
	cp $(PRODOS_DSK) $@
	$(AC) -p $@ $< bin 0x803 < $< || $(RM) $@

$(PROGRAM): $(PROGRAM).s
	cl65 -t $(TARGET) -o $@ $< -C $(TARGET)-asm.cfg

clean: 
	$(RM) $(DISK) $(PROGRAM)
