#include "gtest/gtest.h"
#include "../TaskList.h"
#include "../Task.h"
#include "../SubTask.h"

TEST(TaskListTest, AddAndCountTasks) {
    TaskList lista("Prova");
    EXPECT_EQ(lista.getNumeroTotale(), 0);

    Task t1(Date(1,1,2025), "Task 1");
    lista.aggiungiAttivita(t1);

    EXPECT_EQ(lista.getNumeroTotale(), 1);
}

TEST(TaskListTest, PercentualeTaskCompletati) {
    TaskList lista("Prova");

    Task t1(Date(1,1,2025), "Task 1");
    t1.aggiungiSubTask(SubTask("S1"));
    t1.aggiungiSubTask(SubTask("S2"));

    Task t2(Date(2,1,2025), "Task 2");
    t2.aggiungiSubTask(SubTask("S1"));
    t2.aggiungiSubTask(SubTask("S2"));

    lista.aggiungiAttivita(t1);
    lista.aggiungiAttivita(t2);

    EXPECT_DOUBLE_EQ(lista.percentualeTaskCompletati(), 0.0);

    for (auto& sub : t1.getSubTasks()) sub.completa();
    lista.modificaAttivita("Task 1", t1.getDescrizione(), t1.getScadenza());

    EXPECT_DOUBLE_EQ(lista.percentualeTaskCompletati(), 50.0);

    for (auto& sub : t2.getSubTasks()) sub.completa();
    lista.modificaAttivita("Task 2", t2.getDescrizione(), t2.getScadenza());

    EXPECT_DOUBLE_EQ(lista.percentualeTaskCompletati(), 100.0);
}

TEST(TaskListTest, CompletamentoMedio) {
    TaskList lista("Prova");

    Task t1(Date(1,1,2025), "Task 1");
    t1.aggiungiSubTask(SubTask("S1"));
    t1.aggiungiSubTask(SubTask("S2"));
    t1.getSubTasks()[0].completa();

    Task t2(Date(2,1,2025), "Task 2");
    t2.aggiungiSubTask(SubTask("S1"));
    t2.aggiungiSubTask(SubTask("S2"));
    t2.getSubTasks()[0].completa();

    lista.aggiungiAttivita(t1);
    lista.aggiungiAttivita(t2);

    EXPECT_NEAR(lista.completamentoMedio(), 50.0, 0.1);

    t1.getSubTasks()[1].completa();
    t2.getSubTasks()[1].completa();
    lista.modificaAttivita("Task 1", t1.getDescrizione(), t1.getScadenza());
    lista.modificaAttivita("Task 2", t2.getDescrizione(), t2.getScadenza());

    EXPECT_DOUBLE_EQ(lista.completamentoMedio(), 100.0);
}
