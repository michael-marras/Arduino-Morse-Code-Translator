# Morse ADR

## Status

Accepted

## Context

I need a way to translate english to morse code in my program. I need something that takes in a string, and makes the arduino board flash the message in morse each loop iteration

## Decision

I'm proposing to make Morse class that will translate and store a morse message. This class will also be responsible for displaying the morse message through the arudino led circuit

## Consequences

Only need 1 place where the more code message is translated stored and displayed