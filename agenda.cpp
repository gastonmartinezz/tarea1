#include "../include/agenda.h"

struct rep_agenda {
    TEvento evento[MAX_EVENTOS];
    int tope;
};

TAgenda crearTAgenda() {
    TAgenda nuevaAgenda = NULL;

    nuevaAgenda = new rep_agenda;
    nuevaAgenda->tope = 0;

    return nuevaAgenda;
}

void agregarEnAgenda(TAgenda &agenda, TEvento evento) {

    if (agenda->tope < MAX_EVENTOS) {
        int i = agenda->tope - 1;

        while (i >= 0 && (compararTFechas(fechaTEvento(agenda->evento[i]), fechaTEvento(evento)) == 1 || (compararTFechas(fechaTEvento(agenda->evento[i]), fechaTEvento(evento)) == 0 && (idTEvento(agenda->evento[i]) < idTEvento(evento))))) {
            agenda->evento[i+1] = agenda->evento[i];
            i--;
        }
        agenda->evento[i+1] = evento;
        agenda->tope++;
    }
}

void liberarTAgenda(TAgenda &agenda) {
    for (int i=0; i < agenda->tope; i++) {
        liberarTEvento(agenda->evento[i]);
    }
    delete agenda;
    agenda = NULL;
}

void imprimirTAgenda(TAgenda agenda) {
    if (agenda->tope != 0) {
        for (int i = 0; i < agenda->tope; i++) {
            imprimirTEvento(agenda->evento[i]);
        }
    }
}

bool estaEnAgenda(TAgenda agenda, int id) {
    bool res = false;

    for (int i = 0; i < agenda->tope; i++) {
        if (idTEvento(agenda->evento[i]) == id) {
            res = true;
        }
    }
    return res;
}

TEvento obtenerDeAgenda(TAgenda agenda, int id) {
    TEvento res = NULL;

    for (int i = 0; i < agenda->tope; i++) {
        if (idTEvento(agenda->evento[i]) == id) {
            res = agenda->evento[i];
        } 
    }
    return res;
}

void posponerEnAgenda(TAgenda &agenda, int id, nat n) {

    TEvento eve = obtenerDeAgenda(agenda, id);
    posponerTEvento(eve, n);

    for (int i = 0; i < agenda->tope-1; i++) {
      for (int j = 0; (j < agenda->tope-1-i) ; j++) {
        if (compararTFechas(fechaTEvento(agenda->evento[j]), fechaTEvento(agenda->evento[j+1])) == 1){
            TEvento swap = agenda->evento[j];
            agenda->evento[j] = agenda->evento[j+1];
            agenda->evento[j+1] = swap;
        }
      }
    }  
}   

void imprimirEventosFecha(TAgenda agenda, TFecha fecha) {

    for (int i = 0; i < agenda->tope; i++) {
        if (compararTFechas(fechaTEvento(agenda->evento[i]), fecha) == 0) {
            imprimirTEvento(agenda->evento[i]);
        }
    }
}

bool hayEventosFecha(TAgenda agenda, TFecha fecha) {
    bool res = false;

    int lefty = 0;
    int righty = agenda->tope - 1;
    while (lefty <= righty) {

        int mitte = (lefty+righty) / 2;

        if (compararTFechas(fecha, fechaTEvento(agenda->evento[mitte])) == 0) {
            res = true;
        }

        if (compararTFechas(fecha, fechaTEvento(agenda->evento[mitte])) == 1) {
            lefty = mitte + 1;
        } else {
            righty = mitte - 1;
        }
    }
    return res;
}

void removerDeAgenda(TAgenda &agenda, int id) {

    int j = 0;
    while ((j < agenda->tope) && idTEvento(agenda->evento[j]) != id) {
        j++;
    }

    TEvento save = agenda->evento[j];
    liberarTEvento(save);

    for (int k = j; k < agenda->tope; k++) {
        agenda->evento[k] = agenda->evento[k+1];
    }
    agenda->tope--;
}

