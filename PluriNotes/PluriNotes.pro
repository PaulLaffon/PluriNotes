QT += widgets
QT += xml
QT += multimediawidgets
QT += multimedia

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += main.cpp\
        mainwindow.cpp \
    note.cpp \
    versionnote.cpp \
    notemanager.cpp \
    affichagenote.cpp \
    partiecentrale.cpp \
    partiegauche.cpp \
    relation.cpp \
    couple.cpp \
    relationmanager.cpp \
    creationrelation.cpp \
    partiedroite.cpp \
    creationcouple.cpp \
    reference.cpp \
    gestionrelation.cpp \
    versionmultimedia.cpp \
    affichagemultimedia.cpp \
    preferences.cpp


HEADERS  += mainwindow.h \
    note.h \
    versionnote.h \
    notemanager.h \
    affichagenote.h \
    partiecentrale.h \
    partiegauche.h \
    relation.h \
    couple.h \
    relationmanager.h \
    creationrelation.h \
    partiedroite.h \
    creationcouple.h \
    reference.h \
    gestionrelation.h \
    versionmultimedia.h \
    affichagemultimedia.h \
    preferences.h

