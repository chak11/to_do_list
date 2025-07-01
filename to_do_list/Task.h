#ifndef TASK_H
#define TASK_H

#include "date.h"
#include "subTask.h"
#include <string>
#include <sstream>
#include <vector>

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
        if (subTasks.empty()) return completata;
        for (const auto& s : subTasks) {
            if (!s.isCompletato()) return false;
        }
        return true;
    }

    void cambiaStato() {
        completata = !completata;
    }

    void addSubTask(const SubTask& s) {
        subTasks.push_back(s);
    }

    const std::vector<SubTask>& getSubTasks() const {
        return subTasks;
    }

    // ✅ Metodo in più per accesso modificabile
    std::vector<SubTask>& getSubTasksMutable() {
        return subTasks;
    }

    void completaSubTask(const std::string& desc) {
        for (auto& s : subTasks) {
            if (s.getDescrizione() == desc) {
                s.setCompletato(true);
            }
        }
    }

    bool operator==(const Task &altro) const {
        return scadenza == altro.scadenza && testo == altro.testo;
    }

private:
    Date scadenza;
    std::string testo;
    bool completata;
    std::vector<SubTask> subTasks;
};

#endif
