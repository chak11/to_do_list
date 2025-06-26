//
// Created by chaki on 23/06/2025.
//

#include "date.h"
#include <stdexcept>

Date::Date(int giorno, int mese, int anno) {
    if (!isValida(giorno, mese, anno))
        throw std::out_of_range("Data non valida!");
    this->giorno = giorno;
    this->mese = mese;
    this->anno = anno;
}

int Date::getGiorno() const {
    return giorno;
}

int Date::getMese() const {
    return mese;
}

int Date::getAnno() const {
    return anno;
}

void Date::setGiorno(int giorno) {
    if (giornoValido(giorno, this->mese, this->anno))
        this->giorno = giorno;
    else
        throw std::out_of_range("Giorno non valido!");
}

void Date::setMese(int mese) {
    if (meseValido(mese)) {
        if (giornoValido(this->giorno, mese, this->anno))
            this->mese = mese;
        else
            throw std::out_of_range("Giorno non valido per il nuovo mese!");
    } else
        throw std::out_of_range("Mese non valido!");
}

void Date::setAnno(int anno) {
    if (annoValido(anno)) {
        if (giornoValido(this->giorno, this->mese, anno))
            this->anno = anno;
        else
            throw std::out_of_range("Giorno non valido per il nuovo anno!");
    } else
        throw std::out_of_range("Anno non valido!");
}

bool Date::operator==(const Date &d) const {
    return giorno == d.giorno && mese == d.mese && anno == d.anno;
}

bool Date::isValida(int giorno, int mese, int anno) {
    return giornoValido(giorno, mese, anno) && meseValido(mese) && annoValido(anno);
}

bool Date::giornoValido(int giorno, int mese, int anno) const {
    int max = giorniNelMese(mese, anno);
    return giorno > 0 && giorno <= max;
}

bool Date::meseValido(int mese) {
    return mese >= 1 && mese <= 12;
}

bool Date::annoValido(int anno) {
    return anno >= 1900 && anno <= 2100;
}

int Date::giorniNelMese(int mese, int anno) const {
    switch (mese) {
        case 2:
            return isBisestile(anno) ? 29 : 28;
        case 4: case 6: case 9: case 11:
            return 30;
        default:
            return 31;
    }
}

bool Date::isBisestile(int anno) const {
    return (anno % 4 == 0 && (anno % 100 != 0 || anno % 400 == 0));
}

