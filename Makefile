PORT     = /dev/ttyUSB0
ACLI     = arduino-cli
PLATFORM = arduino:avr:uno
BAUD     = 9600
FLAGS    =
SKETCH   = MagicStaff2.ino

SOURCES = $(SKETCH) adxl.h config.h palette.h magicstaff.h magicstaff.cpp


.PHONY = all
all: compile upload

.PHONY += debug
debug: FLAGS += \
	--build-property "compiler.cpp.extra_flags=\"-DDEBUG\"" \
	--build-property "compiler.cpp.extra_flags=\"-DCONFIG_BAUD=$(BAUD)\""
debug: testbench upload

.PHONY += compile
compile: $(SOURCES)
	$(ACLI) compile --fqbn $(PLATFORM) $(FLAGS) $(SKETCH)

.PHONY += upload
upload:
	$(ACLI) upload $(TARGET) -p $(PORT) -b $(PLATFORM)

.PHONY += monitor
monitor:
	$(ACLI) monitor -p $(PORT) --config $(BAUD)
