#author zengpw 2015-07-31
#last modify zengpw 2015-08-06

CXX = g++
CXX_FLAGS = -g -O3 -fpic -ftemplate-depth-64 -m64

LINK_LIB_PATH += -L /usr/local/lib

DEST = $(PROJECT_NAME)

ifeq "$(PROJECT_TYPE)" "SO"
	CXX_FLAGS += -shared
	DEST = lib$(PROJECT_NAME).so
endif

COMPILE_SOURCE ?= $(SOURCE)
COMPILE_CPP += $(addsuffix .o,$(basename $(filter %.cpp,$(COMPILE_SOURCE))))
COMPILE_CC += $(addsuffix .o,$(basename $(filter %.cc,$(COMPILE_SOURCE))))

.PHONY: all create install clean

all: create $(DEST)

create:
	$(shell mkdir -p -m 755 $(OUTPUT_TEMP)/$(PROJECT_NAME))
	$(shell mkdir -p -m 755 $(OUTPUT))

$(DEST): $(COMPILE_CPP) $(COMPILE_CC)
	$(CXX) $(CXX_FLAGS) -o $(OUTPUT)/$(DEST) $(addprefix $(OUTPUT_TEMP)/$(PROJECT_NAME)/,$(COMPILE_CPP)) $(addprefix $(OUTPUT_TEMP)/$(PROJECT_NAME)/,$(COMPILE_CC))

$(COMPILE_CPP): %.o: %.cpp
	$(CXX) $(CXX_FLAGS) $(SOURCE_INCLUDE) -c $< -o $(OUTPUT_TEMP)/$(PROJECT_NAME)/$@ $(LINK_LIB_PATH) $(LINK_LIB)

$(COMPILE_CC): %.o: %.cc
	$(CXX) $(CXX_FLAGS) $(SOURCE_INCLUDE) -c $< -o $(OUTPUT_TEMP)/$(PROJECT_NAME)/$@ $(LINK_LIB_PATH) $(LINK_LIB)

install:
	$(shell mkdir -p -m 755 $(INSTALL_PATH)
	cp -rpf $(INSTALL_FILE) $(INSTALL_PATH)

clean:
	-rm -rf $(OUTPUT)/$(DEST)
	-rm -rf $(OUTPUT_TEMP)/$(PROJECT_NAME)