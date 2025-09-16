# Connect4 AI for MIŠKO3 (STM32G474)

This repository contains a Connect4 game project where you can play against an AI model. The AI is trained in Python and deployed on the **MIŠKO3** development board (STM32G474).

---

## Table of Contents
- [Overview](#overview)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Gameplay](#gameplay)
- [License](#license)

---

## Overview

The repository is split into two main folders:

1. **Python_Model** – Contains the code to train the AI model using Python.  
2. **STM32_MISKO3** – Contains the C code for the STM32 controller to deploy the trained model.  

Each folder has its own README.md with more details about its usage and setup.

---

## Hardware Requirements

- **MIŠKO3 development board** (STM32G474)  
- More details about the board can be found here: [MIŠKO3 Repository](https://github.com/mjankovec/MiSKo3)

---

## Software Requirements

- **STM32CubeIDE** for building STM32 projects  
- **ARM GCC toolchain** (`arm-none-eabi-gcc`)  
- **ST X-CUBE-AI library** for AI deployment  
- **Python 3.10+** (for AI model training, see the Python_Model folder)  
- Libraries: HAL driver, CMSIS, UGUI  

---

## Gameplay

- **Objective:** Place 4 pieces in a row (horizontally, vertically, or diagonally) before the AI.  
- **Controls:**  
  - Use **Left/Right buttons** on MIŠKO3 to move your piece.  
  - Press **OK button** to place your piece.  
- **Pre-move:** The game shows where your piece will land before placement.  
- **AI Player:** Yellow pieces  
- **Human Player:** Red pieces  

Depending on the game outcome, different end screens are displayed:  
- AI Wins  
- Human Wins  
- Draw  

*(Insert screenshots for each screen here)*

---

## License

This project is **open-source** and free to use, modify, and distribute.
