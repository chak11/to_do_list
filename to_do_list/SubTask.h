#ifndef SUBTASK_H
#define SUBTASK_H

#include <string>

class SubTask {
public:
    SubTask(const std::string& desc, bool completato = false);

    const std::string& getDescrizione() const;
    bool isCompletato() const;
    void setCompletato(bool stato);

private:
    std::string descrizione;
    bool completato;
};

#endif