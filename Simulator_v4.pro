QT       += core gui network widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Control/altitude.cpp \
    Control/compass.cpp \
    Control/hyrohorizont.cpp \
    Control/vma.cpp \
    main.cpp \
    mainwidget.cpp \
    Contours_SU/marsh_contour.cpp \
    Contours_SU/depth_contour.cpp \
    Contours_SU/kurs_contour.cpp \
    Contours_charts/chartformdepth.cpp \
    Contours_charts/chartformkurs.cpp \
    Contours_charts/chartformmarsh.cpp \
    debug_form.cpp \
    protocols/protocol_instructor.cpp \
    protocols/protocol_simulator.cpp \
    common/configdata.cpp \
    common/crc32checksum.cpp \
    Contours_charts/mapform.cpp \

HEADERS += \
    Control/altitude.h \
    Control/compass.h \
    Control/hyrohorizont.h \
    Control/vma.h \
    common/defines.h \
    common/header.h \
    mainwidget.h \
    Contours_SU/marsh_contour.h \
    Contours_SU/depth_contour.h \
    Contours_SU/kurs_contour.h \
    Contours_charts/chartformdepth.h \
    Contours_charts/chartformkurs.h \
    Contours_charts/chartformmarsh.h \
    debug_form.h \
    common/exchange_structures.h \
    protocols/protocol_instructor.h \
    protocols/protocol_simulator.h \
    structures/instructor_structure.h \
    structures/simulator_structure.h \
    common/configdata.h \
    common/crc32checksum.h \
    structures/targeting_structures.h \
    Contours_charts/mapform.h \

FORMS += \
    Control/altitude.ui \
    Control/compass.ui \
    Control/hyrohorizont.ui \
    Control/vma.ui \
    mainwidget.ui \
    Contours_charts/chartformdepth.ui \
    Contours_charts/chartformkurs.ui \
    Contours_charts/chartformmarsh.ui \
    debug_form.ui \
    Contours_charts/mapform.ui \

OTHER_FILES += \
    config/protocols.conf

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourses.qrc
