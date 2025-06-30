#include "gtest/gtest.h"
#include "../Task.h"
#include "../SubTask.h"

TEST(TaskTest, AddAndGetSubTasks) {
    Task mainTask(Date(1,1,2025), "Task principale");

    SubTask sub1("SubTask 1");
    SubTask sub2("SubTask 2");

    mainTask.aggiungiSubTask(sub1);
    mainTask.aggiungiSubTask(sub2);

    const auto& subs = mainTask.getSubTasks();
    ASSERT_EQ(subs.size(), 2);
    EXPECT_EQ(subs[0].getDescrizione(), "SubTask 1");
    EXPECT_FALSE(subs[0].isCompletata());
}

TEST(TaskTest, CompleteSubTasksAndCheckCompletion) {
    Task mainTask(Date(1,1,2025), "Task principale");

    mainTask.aggiungiSubTask(SubTask("SubTask 1"));
    mainTask.aggiungiSubTask(SubTask("SubTask 2"));

    EXPECT_FALSE(mainTask.isCompletata());  // Nessuno completato


    mainTask.getSubTasks().at(0).completa();
    EXPECT_FALSE(mainTask.isCompletata());


    mainTask.getSubTasks().at(1).completa();
    EXPECT_TRUE(mainTask.isCompletata());
}

TEST(TaskTest, PercentualeCompletamento) {
    Task mainTask(Date(1,1,2025), "Task principale");

    mainTask.aggiungiSubTask(SubTask("SubTask 1"));
    mainTask.aggiungiSubTask(SubTask("SubTask 2"));
    mainTask.aggiungiSubTask(SubTask("SubTask 3"));

    EXPECT_DOUBLE_EQ(mainTask.percentualeCompletamento(), 0.0);

    mainTask.getSubTasks().at(0).completa();
    EXPECT_NEAR(mainTask.percentualeCompletamento(), 33.33, 0.5);

    mainTask.getSubTasks().at(1).completa();
    EXPECT_NEAR(mainTask.percentualeCompletamento(), 66.66, 0.5);

    mainTask.getSubTasks().at(2).completa();
    EXPECT_DOUBLE_EQ(mainTask.percentualeCompletamento(), 100.0);
}
