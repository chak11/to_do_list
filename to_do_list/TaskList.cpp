#include <iostream>
#include <utility>
#include "TaskList.h"

TaskList::TaskList(std::string titolo) : titolo(std::move(titolo)) {}

const std::list<Task> &TaskList::getListaAttivita() const {
    return elenco;
}

const std::string &TaskList::getTitolo() const {
    return titolo;
}

void TaskList::setTitolo(const std::string &nuovoTitolo) {
    titolo = nuovoTitolo;
}

void TaskList::aggiungiAttivita(const Task &attivita) {
    elenco.push_back(attivita);
    totale++;
    mostraTutte();
}

void TaskList::rimuoviAttivita(const std::string &descrizione) {
    Task daRimuovere = cerca(descrizione);
    if (!daRimuovere.getDescrizione().empty() || !daRimuovere.getData().empty()) {
        elenco.remove(daRimuovere);
        totale--;
        if (daRimuovere.èCompletata())
            completate--;
        mostraTutte();
    } else {
        std::cout << "Nessuna attività trovata con descrizione: " << descrizione << std::endl;
    }
}

void TaskList::svuota() {
    elenco.clear();
    totale = 0;
    completate = 0;
}

void TaskList::completaAttivita(const std::string &descrizione) {
    Task &attivita = trova(descrizione);
    if (!attivita.èCompletata()) {
        attivita.cambiaStato();
        completate++;
    }
    mostraTutte();
}

void TaskList::modificaAttivita(const std::string &descrizione, const std::string &nuovaDesc, const Date &nuovaData) {
    Task &attivita = trova(descrizione);
    if (!attivita.getDescrizione().empty() || !attivita.getData().empty()) {
        if (!nuovaDesc.empty())
            attivita.setDescrizione(nuovaDesc);
        else if (!(nuovaData == Date()))
            attivita.setScadenza(nuovaData);
        else
            attivita.cambiaStato();

        mostraTutte();
    } else {
        std::cout << "Attività non trovata: " << descrizione << std::endl;
    }
}

void TaskList::mostraTutte() {
    std::cout << "\nElenco completo: " << titolo << std::endl;
    for (const auto &a : elenco) {
        std::cout << "- " << a.getDescrizione() << " | ";
        if (!a.èCompletata())
            std::cout << "Da fare entro " << a.getData() << std::endl;
        else
            std::cout << "Completata" << std::endl;
    }
    if (totale == 0)
        std::cout << "\nNessuna attività presente." << std::endl;
    else
        std::cout << "\nTotali: " << totale << ", da completare: " << (totale - completate) << std::endl;
}

void TaskList::mostraIncompleti() {
    std::cout << "\nAttività da completare:" << std::endl;
    for (const auto &a : elenco) {
        if (!a.èCompletata())
            std::cout << "- " << a.getDescrizione() << " | " << a.getData() << std::endl;
    }
    int daFare = totale - completate;
    if (daFare == 0)
        std::cout << "\nTutte le attività sono completate." << std::endl;
    else
        std::cout << "\nRimangono " << daFare << " attività da fare." << std::endl;
}

void TaskList::salvaSuFile(const std::string &nomeFile) const {
    std::ofstream file(nomeFile);
    if (file.is_open()) {
        file << titolo << std::endl;
        for (const auto &a : elenco) {
            file << a.getDescrizione() << " - " << a.getData() << " - ";
            file << (a.èCompletata() ? "completata" : "non completata") << std::endl;
        }
        file.close();
    } else {
        throw std::runtime_error("Errore nel salvataggio su file.");
    }
}

void TaskList::caricaDaFile(const std::string &nomeFile, TaskList &lista) {
    std::ifstream file(nomeFile);
    if (file.is_open()) {
        std::string linea;
        std::getline(file, lista.titolo);
        while (std::getline(file, linea)) {
            std::stringstream ss(linea);
            std::string desc, dataStr, stato;
            std::getline(ss, desc, '-');
            std::getline(ss, dataStr, '-');
            std::getline(ss, stato);
            bool completato = (stato.find("completata") != std::string::npos);
            Date d = Task::daStringaData(dataStr);
            lista.elenco.emplace_back(d, desc, completato);
        }
        file.close();
    } else {
        throw std::runtime_error("File non trovato.");
    }
}

Task &TaskList::trova(const std::string &parametro) {
    return cerca(parametro);
}

int TaskList::getNumeroTotale() const {
    return totale;
}

int TaskList::getIncompleti() const {
    return totale - completate;
}

Task &TaskList::cerca(const std::string &parametro) {
    static Task vuota(Date(), "");
    for (auto &a : elenco) {
        if (a.getDescrizione() == parametro || a.getData() == parametro)
            return a;
    }
    return vuota;
}