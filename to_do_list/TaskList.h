#ifndef TASKLIST_H
#define TASKLIST_H

#include "Task.h"
#include <list>
#include <fstream>
#include <string>

class TaskList {
public:
    explicit TaskList(const std::string& titolo);
    TaskList() = default;

    const std::list<Task>& getListaAttivita() const;
    const std::string& getTitolo() const;

    void setTitolo(const std::string& titolo);
    void aggiungiAttivita(const Task& attivita);
    void rimuoviAttivita(const std::string& descrizione);
    void svuota();
    void completaAttivita(const std::string& descrizione);
    void completaSottoTask(const std::string& descrizioneTask, const std::string& descrizioneSottoTask);
    void modificaAttivita(const std::string& descrizione, const std::string& nuovaDesc, const Date& nuovaData);

    void mostraTutte() const;
    void mostraIncompleti() const;

    Task& trova(const std::string& descrizione);
    int getNumeroTotale() const;
    int getIncompleti() const;

    void salvaSuFile(const std::string& nomeFile) const;
    static void caricaDaFile(const std::string& nomeFile, TaskList& lista);

    double calcolaPercentualeTaskCompletati() const;
    double calcolaCompletamentoMedio() const;

private:
    Task& cerca(const std::string& parametro);

    std::list<Task> elenco;
    std::string titolo;
    int totale{0};
    int completate{0};
};

#endif