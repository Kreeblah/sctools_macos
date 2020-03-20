
all: ../bin/$(TARGET)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LIBS)
	$(STRIP) $(PROG)

$(PROG).exe: $(PROG)
	cp $(PROG) $(PROG).exe

#$(PROG).dmg: $(PROG)
#	mkdir tmp
#	cp $(PROG) tmp
#	hdiutil create -ov -volname sctools_$(PROG) -srcfolder tmp $(PROG).dmg

#hid.o: hid_$(OS).c rawhid.h
#	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(PROG) $(PROG).exe $(PROG).dmg ../bin/$(TARGET)
	rm -rf tmp

../bin/$(TARGET): $(TARGET)
	mkdir -p ../bin
	cp $(TARGET) ../bin/$(TARGET)

