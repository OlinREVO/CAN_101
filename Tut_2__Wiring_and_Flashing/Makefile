TARGET=$(build)

CC=avr-gcc
MCU=atmega16m1
PROGRAMMER=avrispmkII
PORT=usb
AVRDUDE=avrdude
OBJCOPY=avr-objcopy

##############
#  Src Vars  #
##############
SRCDIR=src
LIBDIR=lib
OBJDIR=obj
BUIDIR=build

SRCLIBS=$(wildcard $(LIBDIR)/*.c)
INTLIBS=$(wildcard $(LIBDIR)/*.h)
OBJLIBS=$(patsubst $(LIBDIR)/%.c,$(LIBDIR)/%.o,$(SRCLIBS))

SRCS=$(wildcard $(SRCDIR)/$(TARGET)/*.c)
OBJS=$(patsubst $(SRCDIR)/$(TARGET)/%.c, $(OBJDIR)/%.o, $(SRCS))

################
#  Build Vars  #
################
CFLAGS+=-mmcu=$(MCU) -g -Os -Wall -Wunused -I$(LIBDIR)/
LDFLAGS=-mmcu=$(MCU) -Wl,-Map=$(BUIDIR)/$(TARGET).map -lm
AVRFLAGS=-p $(MCU) -v -c $(PROGRAMMER) -P $(PORT)

#############
#  Recipes  #
#############

all: $(OBJLIBS) $(BUIDIR)/$(TARGET).elf $(BUIDIR)/$(TARGET).hex $(BUIDIR)/$(TARGET).srec

$(LIBDIR)/%.o: $(LIBDIR)/%.c $(LIBDIR)/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/$(TARGET)/%.c 
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUIDIR)/%.elf: $(OBJS) $(OBJLIBS)
	$(CC) $^ $(LDFLAGS) -o $@

$(BUIDIR)/%.srec: $(BUIDIR)/%.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

$(BUIDIR)/%.hex: $(BUIDIR)/%.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@


$(OBJS): | $(OBJDIR)
$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(BUIDIR)

.PHONY: flash
flash: $(BUIDIR)/$(TARGET).hex
	$(AVRDUDE) $(AVRFLAGS) -U flash:w:$<

.PHONY: verify
verify: $(BUIDIR)/$(TARGET).hex
	$(AVRDUDE) $(AVRFLAGS) -U flash:v:$<

.PHONY: clean
clean: 
	rm -rf $(BUIDIR) $(OBJDIR) $(OBJLIBS)
