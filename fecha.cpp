#include "../include/fecha.h"

struct rep_fecha {
    nat dia, mes, anio;
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    TFecha nuevaFecha = NULL;

    nuevaFecha = new rep_fecha;

    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;

    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {

    delete fecha;
    fecha = NULL;

}
void imprimirTFecha(TFecha fecha) {
    printf("%d/%d/%d", fecha->dia,fecha->mes,fecha->anio);
    printf("\n");
}

nat diasMes(nat mes, nat anio) {
    int days = 31;

   if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        days = 30;
    }

    if (mes == 2 && anio % 4 == 0 && (anio % 400 == 0 || anio % 100 != 0)) {
        days = 29;
    } else if (mes == 2 && anio % 4 != 0) {
        days = 28;
    }
    return days;
}


void aumentarTFecha(TFecha &fecha, nat dias) {
    fecha->dia += dias;
    while (fecha->dia > diasMes(fecha->mes, fecha->anio)) {
        fecha->dia -= diasMes(fecha->mes, fecha->anio);

        fecha->mes++;
        if (fecha->mes > 12) {
            fecha->mes = 1;
            fecha->anio++;
        }
    }
}

int compararTFechas(TFecha fecha1, TFecha fecha2) {
    int res = 0;

    if (fecha1->anio > fecha2->anio) {
        res = 1;
    } else if (fecha1->anio < fecha2->anio) {
        res = -1;
    } else if (fecha1->anio == fecha2->anio && fecha1->mes > fecha2->mes) {
        res = 1;
    } else if (fecha1->anio == fecha2->anio && fecha1->mes < fecha2->mes) {
        res = -1;
    } else if (fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia > fecha2->dia) {
        res = 1;
    } else if (fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia < fecha2->dia) {
        res = -1;
    } else if (fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia == fecha2->dia) {
        res = 0;
    }
    
    return res;
}
