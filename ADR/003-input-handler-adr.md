# Title
Input handler Class

## Status
Accepted

## Context
The input handler was originally Input() in main.cpp, but was not testable

## Decision
I decided to make an InputHandler class so that I can abstract input handling to unit test

## Consequences

This created two new files while shrinking main.cpp. Also added testability to input handling.