#include "task.h"

Task::Task(const Date &data, const std::string &descrizione, bool completata)
    : scadenza(data), testo(descrizione), completata(completata) {}

std::string Task::getData() const {
    std::stringstream ss;
    if (scadenza.getGiorno() != 0)
        ss << scadenza.getGiorno() << "/" << scadenza.getMese() << "/" << scadenza.getAnno();
    return ss.str();
}

void Task::setScadenza(const Date &data) {
    scadenza = data;
}

Date Task::daStringaData(const std::string &dataStr) {
    std::istringstream iss(dataStr);
    std::string parte;
    int valori[3];
    int i = 0;
    while (std::getline(iss, parte, '/')) {
        valori[i++] = std::stoi(parte);
    }
    return Date(valori[0], valori[1], valori[2]);
}

const std::string &Task::getDescrizione() const {
    return testo;
}

void Task::setDescrizione(const std::string &desc) {
    testo = desc;
}

bool Task::èCompletata() const {
    if (subTasks.empty()) return completata;
    for (const auto& s : subTasks) {
        if (!s.isCompletato()) return false;
    }
    return true;
}

void Task::cambiaStato() {
    completata = !completata;
}

void Task::addSubTask(const SubTask& s) {
    subTasks.push_back(s);
}

const std::vector<SubTask>& Task::getSubTasks() const {
    return subTasks;
}

std::vector<SubTask>& Task::getSubTasksMutable() {
    return subTasks;
}

void Task::completaSubTask(const std::string& desc) {
    for (auto& s : subTasks) {
        if (s.getDescrizione() == desc) {
            s.setCompletato(true);
        }
    }
}

bool Task::operator==(const Task &altro) const {
    return scadenza == altro.scadenza && testo == altro.testo;
}