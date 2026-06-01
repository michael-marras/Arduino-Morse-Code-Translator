# Title
State Machine Class

## Status

Accepted

## Context

The State Machine was originally implemented in main.cpp as Update() and Action(), but was untestable.

## Decision

I decided to make the State Machine a class so that I can unit test it. 

## Consequences

This added 2 new files, but also shrank main.cpp. This added testability to StateMachine