#include <gtest/gtest.h>
#include "StateMachine.hpp"

StateMachine stateMachine;

TEST(ConstructorTest, Default) {
    EXPECT_EQ(stateMachine.GetCurrentState(), states::RECEIVING);
}

TEST(GetBufferTest, Default) {
    EXPECT_EQ(*stateMachine.GetBuffer(), '\0');
}

TEST(TransitionTest, TransmitButtonPressed) {
    Input inputTransmit = Input(StateMachine::PRESSED, StateMachine::NO_SERIAL_INPUT);

    stateMachine.Transition(inputTransmit);
    EXPECT_EQ(stateMachine.GetCurrentState(), states::TRANSMITTING);
}

TEST(TransitionTest, TransmitButtonUnpressed) {
    Input inputReceive  = Input(StateMachine::UNPRESSED, StateMachine::NO_SERIAL_INPUT);

    stateMachine.Transition(inputReceive);
    EXPECT_EQ(stateMachine.GetCurrentState(), states::RECEIVING);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}