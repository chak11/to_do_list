#ifndef SUBTASK_H
#define SUBTASK_H

#include <string>

class SubTask {
public:
    SubTask(const std::string& desc, bool completato = false)
        : descrizione(desc), completato(completato) {}

    const std::string& getDescrizione() const {
        return descrizione;
    }

    bool isCompletato() const {
        return completato;
    }

    void setCompletato(bool stato) {
        completato = stato;
    }

private:
    std::string descrizione;
    bool completato;
};

#endif
