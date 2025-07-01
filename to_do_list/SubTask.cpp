#include "SubTask.h"

SubTask::SubTask(const std::string& desc, bool completato)
    : descrizione(desc), completato(completato) {}


const std::string& SubTask::getDescrizione() const {
    return descrizione;
}

bool SubTask::isCompletato() const {
    return completato;
}

void SubTask::setCompletato(bool stato) {
    completato = stato;
}