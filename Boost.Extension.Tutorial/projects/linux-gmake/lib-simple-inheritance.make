# GNU Make project makefile autogenerated by Premake
ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifeq ($(config),debug)
  OBJDIR     = bin/obj/Debug/lib-simple-inheritance
  TARGETDIR  = bin/debug
  TARGET     = $(TARGETDIR)/liblib-simple-inheritance.so
  DEFINES   += -DLIN -DDEBUG
  INCLUDES  += -I/opt/local/include -I/usr/include -I/usr/local/include -I../../libs
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -fPIC
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -shared -L/opt/local/lib -L/usr/lib -L/usr/local/lib
  LIBS      += -ldl -lboost_regex -lboost_system -lboost_thread
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = bin/obj/Release/lib-simple-inheritance
  TARGETDIR  = bin/release
  TARGET     = $(TARGETDIR)/liblib-simple-inheritance.so
  DEFINES   += -DLIN -DNDEBUG
  INCLUDES  += -I/opt/local/include -I/usr/include -I/usr/local/include -I../../libs
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O2 -fPIC
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -s -shared -L/opt/local/lib -L/usr/lib -L/usr/local/lib
  LIBS      += -ldl -lboost_regex -lboost_system -lboost_thread
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug32)
  OBJDIR     = bin/obj/x32/Debug/lib-simple-inheritance
  TARGETDIR  = bin/debug
  TARGET     = $(TARGETDIR)/liblib-simple-inheritance.so
  DEFINES   += -DLIN -DDEBUG
  INCLUDES  += -I/opt/local/include -I/usr/include -I/usr/local/include -I../../libs
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -m32 -fPIC
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -shared -m32 -L/usr/lib32 -L/opt/local/lib -L/usr/lib -L/usr/local/lib
  LIBS      += -ldl -lboost_regex -lboost_system -lboost_thread
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release32)
  OBJDIR     = bin/obj/x32/Release/lib-simple-inheritance
  TARGETDIR  = bin/release
  TARGET     = $(TARGETDIR)/liblib-simple-inheritance.so
  DEFINES   += -DLIN -DNDEBUG
  INCLUDES  += -I/opt/local/include -I/usr/include -I/usr/local/include -I../../libs
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O2 -m32 -fPIC
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -s -shared -m32 -L/usr/lib32 -L/opt/local/lib -L/usr/lib -L/usr/local/lib
  LIBS      += -ldl -lboost_regex -lboost_system -lboost_thread
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/animals.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking lib-simple-inheritance
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning lib-simple-inheritance
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/animals.o: ../../src/lib-simple-inheritance/animals.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
