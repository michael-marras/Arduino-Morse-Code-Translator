#include <gtest/gtest.h>
#include "StateMachine.hpp"

StateMachine stateMachine;

TEST(ConstructorTest, Default) {
    EXPECT_EQ(stateMachine.GetCurrentState(), states::RECEIVING);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}