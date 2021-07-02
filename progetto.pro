TEMPLATE = app
TARGET = progetto

CONFIG += c++11
QT += widgets
INCLUDEPATH += .

HEADERS += Controller/Controller.h \
           Model/Carta.h \
           Model/CartaEffetto.h \
           Model/CartaNumero.h \
           Model/CartaPescaDue.h \
           Model/CartaPescaQuattro.h \
           Model/CartaSaltaTurno.h \
           Model/CartaColore.h \
           Model/DeepPtr.h \
           Model/Giocatore.h \
           Model/GiocatoreCPU.h \
           Model/Lista.h \
           Model/Partita.h \
           Model/Random.h \
           View/PartitaWidget.h \
           View/CartaWidget.h \
           View/GiocatoreCPUWidget.h \
           View/NuovaPartitaWidget.h \
           View/MainMenuWidget.h \
           View/CreditiWidget.h \
           View/RegoleWidget.h

SOURCES += main.cpp \
           Controller/Controller.cpp \
           Model/Carta.cpp \
           Model/CartaNumero.cpp \
           Model/CartaPescaDue.cpp \
           Model/CartaPescaQuattro.cpp \
           Model/CartaSaltaTurno.cpp \
           Model/CartaColore.cpp \
           Model/Giocatore.cpp \
           Model/GiocatoreCPU.cpp \
           Model/Partita.cpp \
           Model/Random.cpp \
           View/PartitaWidget.cpp \
           View/CartaWidget.cpp \
           View/GiocatoreCPUWidget.cpp \
	   View/NuovaPartitaWidget.cpp \
           View/MainMenuWidget.cpp \
           View/CreditiWidget.cpp \
           View/RegoleWidget.cpp
