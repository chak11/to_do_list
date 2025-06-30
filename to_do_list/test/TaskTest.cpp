#include "gtest/gtest.h"
#include "../Task.h"
#include "../SubTask.h"
#include "../Date.h"

TEST(TaskTest, ConstructorAndGetters) {
    Date d(5, 6, 2025);
    Task t(d, "Prova descrizione");

    EXPECT_EQ(t.getDescrizione(), "Prova descrizione");
    EXPECT_EQ(t.getData(), "5/6/2025");
    EXPECT_FALSE(t.èCompletata());
}

TEST(TaskTest, SetDescrizione) {
    Task t(Date(1, 1, 2025), "Old desc");
    t.setDescrizione("New desc");

    EXPECT_EQ(t.getDescrizione(), "New desc");
}

TEST(TaskTest, SetScadenza) {
    Task t(Date(1, 1, 2025), "Task");
    t.setScadenza(Date(2, 2, 2026));

    EXPECT_EQ(t.getData(), "2/2/2026");
}

TEST(TaskTest, DaStringaData) {
    Date d = Task::daStringaData("15/8/2024");

    EXPECT_EQ(d.getGiorno(), 15);
    EXPECT_EQ(d.getMese(), 8);
    EXPECT_EQ(d.getAnno(), 2024);
}

TEST(TaskTest, CambiaStato) {
    Task t(Date(1, 1, 2025), "Task");

    EXPECT_FALSE(t.èCompletata());
    t.cambiaStato();
    EXPECT_TRUE(t.èCompletata());
    t.cambiaStato();
    EXPECT_FALSE(t.èCompletata());
}

TEST(TaskTest, AddAndGetSubTasks) {
    Task t(Date(1,1,2025), "Task con subtasks");

    SubTask s1("Sub 1");
    SubTask s2("Sub 2");

    t.addSubTask(s1);
    t.addSubTask(s2);

    const auto& subs = t.getSubTasks();
    ASSERT_EQ(subs.size(), 2);
    EXPECT_EQ(subs[0].getDescrizione(), "Sub 1");
    EXPECT_FALSE(subs[0].isCompletato());
}

TEST(TaskTest, GetSubTasksMutable) {
    Task t(Date(1,1,2025), "Task");

    t.addSubTask(SubTask("Sub 1"));
    t.addSubTask(SubTask("Sub 2"));

    auto& subs = t.getSubTasksMutable();
    subs[0].setCompletato(true);

    EXPECT_TRUE(t.getSubTasks()[0].isCompletato());
}

TEST(TaskTest, CompletaSubTask) {
    Task t(Date(1,1,2025), "Task");

    t.addSubTask(SubTask("Sub 1"));
    t.addSubTask(SubTask("Sub 2"));

    t.completaSubTask("Sub 1");

    const auto& subs = t.getSubTasks();
    EXPECT_TRUE(subs[0].isCompletato());
    EXPECT_FALSE(subs[1].isCompletato());
}

TEST(TaskTest, ECompletataWithSubTasks) {
    Task t(Date(1,1,2025), "Task");

    t.addSubTask(SubTask("Sub 1"));
    t.addSubTask(SubTask("Sub 2"));

    EXPECT_FALSE(t.èCompletata());

    t.getSubTasksMutable()[0].setCompletato(true);
    EXPECT_FALSE(t.èCompletata());

    t.getSubTasksMutable()[1].setCompletato(true);
    EXPECT_TRUE(t.èCompletata());
}

TEST(TaskTest, OperatorEquality) {
    Task t1(Date(1,1,2025), "Descrizione");
    Task t2(Date(1,1,2025), "Descrizione");
    Task t3(Date(2,2,2026), "Altra descrizione");

    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);
}

