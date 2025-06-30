#include "gtest/gtest.h"
#include "../TaskList.h"
#include "../Task.h"
#include "../SubTask.h"

TEST(TaskListTest, CostruttoreAndGetTitolo) {
    TaskList lista("La mia lista");
    EXPECT_EQ(lista.getTitolo(), "La mia lista");

    lista.setTitolo("Titolo nuovo");
    EXPECT_EQ(lista.getTitolo(), "Titolo nuovo");
}

TEST(TaskListTest, AddAndCountTasks) {
    TaskList lista("Prova");
    EXPECT_EQ(lista.getNumeroTotale(), 0);

    Task t1(Date(1,1,2025), "Task 1");
    lista.aggiungiAttivita(t1);

    EXPECT_EQ(lista.getNumeroTotale(), 1);
}

TEST(TaskListTest, RemoveAndClearTasks) {
    TaskList lista("Prova");
    Task t1(Date(1,1,2025), "Task 1");
    Task t2(Date(2,1,2025), "Task 2");

    lista.aggiungiAttivita(t1);
    lista.aggiungiAttivita(t2);

    EXPECT_EQ(lista.getNumeroTotale(), 2);

    lista.rimuoviAttivita("Task 1");
    EXPECT_EQ(lista.getNumeroTotale(), 1);

    lista.svuota();
    EXPECT_EQ(lista.getNumeroTotale(), 0);
}

TEST(TaskListTest, CompletaAttivita) {
    TaskList lista("Prova");

    Task t1(Date(1,1,2025), "Task 1");
    lista.aggiungiAttivita(t1);

    EXPECT_EQ(lista.getIncompleti(), 1);

    lista.completaAttivita("Task 1");
    EXPECT_EQ(lista.getIncompleti(), 0);
}

TEST(TaskListTest, ModificaAttivita) {
    TaskList lista("Prova");
    Task t1(Date(1,1,2025), "Vecchia desc");

    lista.aggiungiAttivita(t1);

    // Prima modifica la descrizione
    lista.modificaAttivita("Vecchia desc", "Nuova desc", Date());

    // Poi modifica la data usando la nuova descrizione come chiave
    lista.modificaAttivita("Nuova desc", "", Date(2,2,2025));

    const auto& attivita = lista.getListaAttivita().front();
    EXPECT_EQ(attivita.getDescrizione(), "Nuova desc");
    EXPECT_EQ(attivita.getData(), "2/2/2025");
}


TEST(TaskListTest, CompletaSottoTask) {
    TaskList lista("Prova");

    Task t1(Date(1,1,2025), "Task 1");
    t1.addSubTask(SubTask("Sub 1"));
    t1.addSubTask(SubTask("Sub 2"));

    lista.aggiungiAttivita(t1);

    lista.completaSottoTask("Task 1", "Sub 1");

    const auto& sottotask = lista.getListaAttivita().front().getSubTasks();
    EXPECT_TRUE(sottotask[0].isCompletato());
    EXPECT_FALSE(sottotask[1].isCompletato());
}

TEST(TaskListTest, CalcolaPercentualeTaskCompletati) {
    TaskList lista("Prova");

    Task t1(Date(1,1,2025), "Task 1");
    t1.addSubTask(SubTask("S1"));
    t1.addSubTask(SubTask("S2"));

    Task t2(Date(2,1,2025), "Task 2");
    t2.addSubTask(SubTask("S1"));
    t2.addSubTask(SubTask("S2"));

    lista.aggiungiAttivita(t1);
    lista.aggiungiAttivita(t2);

    EXPECT_DOUBLE_EQ(lista.calcolaPercentualeTaskCompletati(), 0.0);

    lista.completaSottoTask("Task 1", "S1");
    lista.completaSottoTask("Task 1", "S2");

    EXPECT_NEAR(lista.calcolaPercentualeTaskCompletati(), 50.0, 0.1);

    lista.completaSottoTask("Task 2", "S1");
    lista.completaSottoTask("Task 2", "S2");

    EXPECT_NEAR(lista.calcolaPercentualeTaskCompletati(), 100.0, 0.1);
}

TEST(TaskListTest, CalcolaCompletamentoMedio) {
    TaskList lista("Prova");

    Task t1(Date(1,1,2025), "Task 1");
    t1.addSubTask(SubTask("S1"));
    t1.addSubTask(SubTask("S2"));
    t1.getSubTasksMutable()[0].setCompletato(true);

    Task t2(Date(2,1,2025), "Task 2");
    t2.addSubTask(SubTask("S1"));
    t2.addSubTask(SubTask("S2"));
    t2.getSubTasksMutable()[0].setCompletato(true);

    lista.aggiungiAttivita(t1);
    lista.aggiungiAttivita(t2);

    EXPECT_NEAR(lista.calcolaCompletamentoMedio(), 50.0, 0.1);

    lista.completaSottoTask("Task 1", "S2");
    lista.completaSottoTask("Task 2", "S2");

    EXPECT_DOUBLE_EQ(lista.calcolaCompletamentoMedio(), 100.0);
}
