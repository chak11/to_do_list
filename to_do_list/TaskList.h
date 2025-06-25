#ifndef MYTASKMANAGER_TASKLIST_H
#define MYTASKMANAGER_TASKLIST_H

#include "Task.h"
#include <list>
#include <fstream>

class TaskList {
public:
    explicit TaskList(std::string titolo);
    TaskList() = default;

    const std::list<Task> &getListaAttivita() const;
    const std::string &getTitolo() const;

    void setTitolo(const std::string &titolo);
    void aggiungiAttivita(const Task &attivita);
    void rimuoviAttivita(const std::string &descrizione);
    void svuota();
    void completaAttivita(const std::string &descrizione);
    void modificaAttivita(const std::string &descrizione, const std::string &nuovaDesc, const Date &nuovaData);

    void mostraTutte();
    void mostraIncompleti();

    Task &trova(const std::string &descrizione);
    int getNumeroTotale() const;
    int getIncompleti() const;

    void salvaSuFile(const std::string &nomeFile) const;
    static void caricaDaFile(const std::string &nomeFile, TaskList &lista);

private:
    Task &cerca(const std::string &parametro);

    std::list<Task> elenco;
    std::string titolo;
    int totale{0};
    int completate{0};
};

#endif
