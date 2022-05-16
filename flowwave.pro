include($$PWD/../../plugins.pri)
include($$PWD/common/common.pri)

TARGET = $$PLUGINS_PREFIX/Visual/flowwave

HEADERS += flowwave.h \
           visualflowwavefactory.h

SOURCES += flowwave.cpp \
           visualflowwavefactory.cpp

unix{
    target.path = $$PLUGIN_DIR/Visual
    INSTALLS += target
}
