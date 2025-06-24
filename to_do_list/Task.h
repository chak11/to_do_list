//
// Created by chaki on 23/06/2025.
//

#ifndef TASK_H
#define TASK_H




#include "Date.h"
#include <string>
#include <sstream>

class Task {
public:
    Task(const Date &data, const std::string &descrizione, bool completata = false)
        : scadenza(data), testo(descrizione), completata(completata) {}

    std::string getData() const {
        std::stringstream ss;
        if (scadenza.getGiorno() != 0)
            ss << scadenza.getGiorno() << "/" << scadenza.getMese() << "/" << scadenza.getAnno();
        return ss.str();
    }

    void setScadenza(const Date &data) {
        scadenza = data;
    }

    static Date daStringaData(const std::string &dataStr) {
        std::istringstream iss(dataStr);
        std::string parte;
        int valori[3];
        int i = 0;

        while (std::getline(iss, parte, '/')) {
            valori[i++] = std::stoi(parte);
        }

        return Date(valori[0], valori[1], valori[2]);
    }

    const std::string &getDescrizione() const {
        return testo;
    }

    void setDescrizione(const std::string &desc) {
        testo = desc;
    }

    bool èCompletata() const {
        return completata;
    }

    void cambiaStato() {
        completata = !completata;
    }

    bool operator==(const Task &altro) const {
        return scadenza == altro.scadenza && testo == altro.testo;
    }

private:
    Date scadenza;
    std::string testo;
    bool completata;
};




#endif //TASK_H
