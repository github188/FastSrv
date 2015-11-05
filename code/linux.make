#last modify zengpw 2015-10-23
#author zengpw 2015-07-31

CXX = g++
CXX_FLAGS = -g -Wall -O2 -ftemplate-depth-64 -m64

LINK_LIB_PATH += -L /usr/local/lib

DEST = $(PROJECT_NAME)

ifeq "$(PROJECT_TYPE)" "SO"
	CXX_FLAGS += -fPIC -shared
	DEST = lib$(PROJECT_NAME).so
endif

INSTALL_PATH ?= $(OUTPUT)
COMPILE_SOURCE ?= $(SOURCE)
COMPILE_CPP += $(addsuffix .o,$(basename $(filter %.cpp,$(COMPILE_SOURCE))))
COMPILE_CC += $(addsuffix .o,$(basename $(filter %.cc,$(COMPILE_SOURCE))))

.PHONY: all create install clean clean_all cm cmi

all: create $(DEST)

create:
	$(shell mkdir -p -m 755 $(OUTPUT_TEMP)/$(PROJECT_NAME))
	$(shell mkdir -p -m 755 $(OUTPUT))

$(DEST): $(COMPILE_CPP) $(COMPILE_CC)
	$(CXX) $(CXX_FLAGS) -o $(OUTPUT)/$(DEST) $(addprefix $(OUTPUT_TEMP)/$(PROJECT_NAME)/,$(COMPILE_CPP)) $(addprefix $(OUTPUT_TEMP)/$(PROJECT_NAME)/,$(COMPILE_CC)) $(LINK_LIB_PATH) $(LINK_LIB)

$(COMPILE_CPP): %.o: %.cpp
	$(CXX) $(CXX_FLAGS) $(SOURCE_INCLUDE) -c $< -o $(OUTPUT_TEMP)/$(PROJECT_NAME)/$@

$(COMPILE_CC): %.o: %.cc
	$(CXX) $(CXX_FLAGS) $(SOURCE_INCLUDE) -c $< -o $(OUTPUT_TEMP)/$(PROJECT_NAME)/$@

install:
	$(shell mkdir -p -m 755 $(INSTALL_PATH))
	cp -rpf $(INSTALL_FILE) $(INSTALL_PATH)
	chmod 755 $(INSTALL_PATH)/$(INSTALL_FILE)

clean:
	-rm -rf $(OUTPUT)/$(DEST)
	-rm -rf $(OUTPUT_TEMP)/$(PROJECT_NAME)

clean_all:
	-rm -rf $(OUTPUT)/$(DEST)
	-rm -rf $(OUTPUT_TEMP)/$(PROJECT_NAME)
	-rm -rf $(addprefix $(INSTALL_PATH)/,$(INSTALL_FILE))

cm: clean all
cmi: clean_all all install