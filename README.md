# Ugno

**Progetto in C++ e Qt realizzato per il corso di Programmazione a Oggetti da Giovanni Cocco e Matteo Noro.**


<img src="https://i.vgy.me/LIFigb.png" width="432.25" height="196.75">

## Il seguente progetto di Programmazione ad oggetti si propone di sviluppare un piccolo gioco di carte di nome **UGNO**, dove l’utente può giocare contro un numero arbitrario di avversari comandati dal computer.

Il gioco che quindi si va a creare prende forma e spunto dalle logiche del famoso gioco di carte *UNO*, dal quale ne prende ispirazione principalmente per struttura e regole, nonostante alcune sostanziali differenze da quest’ultime per facilitarne l’accessibilità.

All’inizio della partita, l’utente giocatore può scegliere sia il numero di avversari contro cui giocare sia il numero di carte iniziali.

<img align="right" width="300" height="150" src="https://i.vgy.me/ecdq67.png">

Le tipologie di carta sono due: 
- le *Carte Numero* 
- le *Carte Effetto*, quali:
  - Carta *Salta Turno* 
  - Carta *Pesca* 
  - Carta *Random*.

Lo scopo è, come nella versione originale del gioco, di finire tutte le carte nella propria mano.
Quando la partita inizia, ci sarà già una carta casuale al centro del tavolo. 
Il giocatore ad ogni turno dovrà tentare di buttare più carte possibili, purché, ovviamente, siano sempre compatibili con l’ultima presente nella pila centrale.
Se nessuna carta viene gettata, alla mano ne sarà aggiunta una nuova casuale, pescata dal mazzo. 

## Screenshots della GUI
<img src="https://i.vgy.me/GJK2DF.png" width="22%"></img> <img 
src="https://i.vgy.me/6lQR5c.png" width="25%"></img> <img 
src="https://i.vgy.me/s39D5s.png" width="25%"></img> <img 
src="https://i.vgy.me/cRquoC.png" width="25%"></img> 

## Istruzioni per l'avvio

Per compilare il programma si richiede l’uso del file 
``` 
progetto.pro 
``` 
fornito nella cartella con tutti i file necessari.

Al fine della compilazione quindi, si invocano da terminale i comandi:
```
qmake; make
```
Previa corretta installazione di QT nella macchina. 

In caso non sia presente nel sistema si può installare dal sito proprietario, anche utilizzando un software Open Source, o tramite comando:
```
sudo apt-get install qt5-default.
```

Al fine dell’esecuzione del progetto, una volta compilato, si invoca da terminale il comando:
```
./progetto
```
