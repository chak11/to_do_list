#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "TaskList.h"

TaskList::TaskList(const std::string& titolo) : titolo(titolo) {}

const std::list<Task>& TaskList::getListaAttivita() const {
    return elenco;
}

const std::string& TaskList::getTitolo() const {
    return titolo;
}

void TaskList::setTitolo(const std::string& nuovoTitolo) {
    titolo = nuovoTitolo;
}

void TaskList::aggiungiAttivita(const Task& attivita) {
    elenco.push_back(attivita);
    totale++;
    mostraTutte();
}

void TaskList::rimuoviAttivita(const std::string& descrizione) {
    auto it = elenco.begin();
    while (it != elenco.end()) {
        if (it->getDescrizione() == descrizione || it->getData() == descrizione) {
            if (it->èCompletata()) completate--;
            it = elenco.erase(it);
            totale--;
        } else {
            ++it;
        }
    }
    mostraTutte();
}

void TaskList::svuota() {
    elenco.clear();
    totale = 0;
    completate = 0;
}

void TaskList::completaAttivita(const std::string& descrizione) {
    Task& attivita = trova(descrizione);
    if (!attivita.èCompletata()) {
        attivita.cambiaStato();
        completate++;
    }
    mostraTutte();
}

void TaskList::modificaAttivita(const std::string& descrizione, const std::string& nuovaDesc, const Date& nuovaData) {
    Task& attivita = trova(descrizione);
    if (!attivita.getDescrizione().empty() || !attivita.getData().empty()) {
        if (!nuovaDesc.empty())
            attivita.setDescrizione(nuovaDesc);
        else if (!(nuovaData == Date()))
            attivita.setScadenza(nuovaData);
        else
            attivita.cambiaStato();

        mostraTutte();
    } else {
        std::cout << "Attivita non trovata: " << descrizione << std::endl;
    }
}

void TaskList::mostraTutte() const {
    std::cout << "\nElenco completo: " << titolo << std::endl;
    if (elenco.empty()) {
        std::cout << "Nessuna attivita presente." << std::endl;
        return;
    }

    for (const auto& a : elenco) {
        std::cout << "- " << a.getDescrizione();
        if (!a.èCompletata())
            std::cout << " | Da fare entro " << a.getData() << std::endl;
        else
            std::cout << " | Completata" << std::endl;

        for (const auto& s : a.getSubTasks()) {
            std::string pulita = s.getDescrizione();
            pulita.erase(
                std::remove_if(pulita.begin(), pulita.end(),
                               [](unsigned char c) { return !isprint(c); }),
                pulita.end()
            );

            if (s.isCompletato())
                std::cout << "    - " << pulita << " [COMPLETATA]" << std::endl;
            else
                std::cout << "    - " << pulita << " [DA FARE]" << std::endl;
        }
    }

    std::cout << "\nTotali: " << totale << ", da completare: " << getIncompleti() << std::endl;
}

void TaskList::mostraIncompleti() const {
    std::cout << "\nAttivita da completare:" << std::endl;
    bool trovato = false;
    for (const auto& a : elenco) {
        if (!a.èCompletata()) {
            trovato = true;
            std::cout << "- " << a.getDescrizione() << " | " << a.getData() << std::endl;
            for (const auto& s : a.getSubTasks()) {
                if (!s.isCompletato()) {
                    std::string pulita = s.getDescrizione();
                    pulita.erase(
                        std::remove_if(pulita.begin(), pulita.end(),
                                       [](unsigned char c) { return !isprint(c); }),
                        pulita.end()
                    );
                    std::cout << "    - " << pulita << " [DA FARE]" << std::endl;
                }
            }
        }
    }
    if (!trovato) {
        std::cout << "Tutte le attivita sono completate." << std::endl;
    }
}

void TaskList::completaSottoTask(const std::string& descrizioneTask, const std::string& descrizioneSottoTask) {
    for (auto& task : elenco) {
        if (task.getDescrizione() == descrizioneTask) {
            for (auto& s : task.getSubTasksMutable()) {
                std::string pulita = s.getDescrizione();
                pulita.erase(
                    std::remove_if(pulita.begin(), pulita.end(),
                                   [](unsigned char c) { return !isprint(c); }),
                    pulita.end()
                );

                if (pulita == descrizioneSottoTask && !s.isCompletato()) {
                    s.setCompletato(true);
                    std::cout << "Sotto-task '" << pulita << "' marcato come completato." << std::endl;
                    return;
                }
            }
            std::cout << "Sotto-task non trovato o già completato." << std::endl;
            return;
        }
    }
    std::cout << "Task non trovato." << std::endl;
}

void TaskList::salvaSuFile(const std::string& nomeFile) const {
    std::ofstream file(nomeFile);
    if (!file.is_open()) throw std::runtime_error("Errore nel salvataggio su file.");

    file << titolo << std::endl;
    for (const auto& a : elenco) {
        file << a.getDescrizione() << " - " << a.getData() << " - ";
        file << (a.èCompletata() ? "completata" : "non completata") << std::endl;

        for (const auto& s : a.getSubTasks()) {
            std::string pulita = s.getDescrizione();
            pulita.erase(
                std::remove_if(pulita.begin(), pulita.end(),
                               [](unsigned char c) { return !isprint(c); }),
                pulita.end()
            );

            file << "> " << pulita << " - ";
            file << (s.isCompletato() ? "completato" : "non completato") << std::endl;
        }
    }
}

void TaskList::caricaDaFile(const std::string& nomeFile, TaskList& lista) {
    std::ifstream file(nomeFile);
    if (!file.is_open()) throw std::runtime_error("File non trovato.");

    lista.svuota();
    std::string linea;
    std::getline(file, lista.titolo);

    Task* currentTask = nullptr;

    while (std::getline(file, linea)) {
        if (linea.substr(0, 2) == "> ") {
            if (currentTask) {
                std::stringstream ss(linea.substr(2));
                std::string desc, stato;
                std::getline(ss, desc, '-');
                std::getline(ss, stato);

                bool completato = stato.find("completato") != std::string::npos;
                desc = desc.substr(0, desc.find_last_not_of(" ") + 1);
                SubTask s(desc, completato);
                currentTask->addSubTask(s);
            }
        } else {
            std::stringstream ss(linea);
            std::string desc, dataStr, stato;
            std::getline(ss, desc, '-');
            std::getline(ss, dataStr, '-');
            std::getline(ss, stato);

            desc = desc.substr(0, desc.find_last_not_of(" ") + 1);
            dataStr = dataStr.substr(dataStr.find_first_not_of(" "));

            bool completato = stato.find("completata") != std::string::npos;
            Date d = Task::daStringaData(dataStr);

            lista.elenco.emplace_back(d, desc, completato);
            currentTask = &lista.elenco.back();
        }
    }

    lista.totale = lista.elenco.size();
    lista.completate = 0;
    for (const auto& t : lista.elenco) {
        if (t.èCompletata()) lista.completate++;
    }
}

Task& TaskList::trova(const std::string& parametro) {
    return cerca(parametro);
}

int TaskList::getNumeroTotale() const {
    return totale;
}

int TaskList::getIncompleti() const {
    return totale - completate;
}

Task& TaskList::cerca(const std::string& parametro) {
    for (auto& a : elenco) {
        if (a.getDescrizione() == parametro || a.getData() == parametro)
            return a;
    }
    static Task vuota(Date(), "");
    return vuota;
}

double TaskList::calcolaPercentualeTaskCompletati() const {
    int totaleSottoTask = 0;
    int sottoTaskCompletati = 0;

    for (const auto& t : elenco) {
        for (const auto& s : t.getSubTasks()) {
            totaleSottoTask++;
            if (s.isCompletato()) sottoTaskCompletati++;
        }
    }

    if (totaleSottoTask == 0) return 0.0;

    return (static_cast<double>(sottoTaskCompletati) / totaleSottoTask) * 100.0;
}

double TaskList::calcolaCompletamentoMedio() const {
    if (elenco.empty()) return 0.0;
    double somma = 0.0;
    int count = 0;

    for (const auto& task : elenco) {
        if (task.getSubTasks().empty()) continue;
        int tot = task.getSubTasks().size();
        int completati = 0;
        for (const auto& s : task.getSubTasks()) {
            if (s.isCompletato()) completati++;
        }
        somma += (static_cast<double>(completati) / tot) * 100.0;
        count++;
    }

    if (count == 0) return 0.0;
    return somma / count;
}
