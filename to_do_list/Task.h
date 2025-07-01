#ifndef TASK_H
#define TASK_H

#include "Date.h"
#include "SubTask.h"
#include <string>
#include <sstream>
#include <vector>

class Task {
public:
    Task(const Date &data, const std::string &descrizione, bool completata = false);

    std::string getData() const;
    void setScadenza(const Date &data);
    static Date daStringaData(const std::string &dataStr);

    const std::string &getDescrizione() const;
    void setDescrizione(const std::string &desc);

    bool èCompletata() const;
    void cambiaStato();

    void addSubTask(const SubTask& s);
    const std::vector<SubTask>& getSubTasks() const;
    std::vector<SubTask>& getSubTasksMutable();
    void completaSubTask(const std::string& desc);

    bool operator==(const Task &altro) const;

private:
    Date scadenza;
    std::string testo;
    bool completata;
    std::vector<SubTask> subTasks;
};

#endif