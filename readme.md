# AI Companion

## Overview

This project is an Unreal Engine-based AI companion that follows the player and can switch between melee and ranged
attacks based on player input. The AI behavior is controlled using a Behavior Tree and Blackboard, with the logic
implemented in C++.

## Features

- **AI Companion**: Follows the player character.
- **Attack Modes**: Switches between melee and ranged attacks based on player input.
- **Behavior Tree and Blackboard**: Used for controlling AI behavior.
- **AI Controller**: Manages the AI's actions and decisions.

## Setup

1. **Open the Project**:
    - Open the `companion.uproject` file in Unreal Engine.

## Implementation Details

### AI Controller

The AI Controller (`FollowerAIController`) manages the AI's actions, including following the player and switching attack
modes.

### Behavior Tree and Blackboard

- **Behavior Tree**: Defines the AI's behavior.
- **Blackboard**: Stores the AI's state, such as the player reference and attack type.

### Player Input

TODO

## Code Structure

TODO

## Dependencies

- Unreal Engine 5.5.3
- C++ Standard Library

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
