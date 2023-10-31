# one-kiece-board
a keyboard for one-hand use.
The circuit uses an Arduino Pro Micro.


1. General description: The keyboard consists of 20 keys, including 15 character keys and 5 function keys. It is designed to be used with one hand, compact in size, and can assist in typing most of the existing characters.

2. Objective: The keyboard is aimed at people with disabilities who have only one hand or one set of fingers for typing.

3. Usage:

I designed a similar keyboard with 15 character keys and 4 function keys.

The 15 character keys are divided into 6 typing groups:

-Alphabet group (groups 1, 2):
Group 1 (black letters on the top left) includes: {'p', 'w', 'r', 'a', 'f', 'd', 't', 'h', 'e', 'o', 'y', 's', 'n', 'i', 'u'}
Group 2 (blue letters below and on the left) includes: {'j', 'm', 'b', ''', KEY_TAB, 'v', 'c', 'l', 'z', 'q', 'x', 'g', 'k'}

-Character group (groups 3, 4):
Group 3 (black characters on the top right) includes: {';', ':', '*', '&', '?', '_', '@', '-', '!', '/', '{', '[', '(', '<', '"'}
Group 4 (blue characters below and on the right) includes: {'#', '$', '=', '+', KEY_TAB, '^', '~', '|', '%', '}', ']', ')', '>', '`'}

-Number group (groups 5, 6):
Group 5 (black numbers and symbols at the bottom right) includes: {'-', '7', '8', '9', '*', '+', '4', '5', '6', '/', '0', '1', '2', '3', '-'}
Group 6 (yellow function keys at the bottom left) includes: {PAGE_UP, PAUSE, END, HOME, ESC, PAGE_DOWN, UP_ARROW, LEFT_ALT, LEFT_CTRL, INSERT, LEFT_ARROW, DOWN_ARROW, RIGHT_ARROW, BACKSPACE, DELETE}

4. Tuturial
To type the desired character, you need to determine which group it belongs to. Groups 1, 3, and 5 are the main groups, while groups 2, 4, and 6 are supplementary groups.

You start with the alphabet group:

Typing 15 character keys will input characters from group 1.
Holding down the Space key while typing 15 character keys will input characters from group 2.
When you press and release the Symbol key, it switches to the character group:

Typing 15 character keys will input characters from group 3.
Holding down the Space key while typing 15 character keys will input characters from group 4.
Pressing the Symbol key again and releasing it will switch back to the alphabet group.
When you press the Number key, it switches to the number group:

Typing 15 character keys will input numbers from group 5.
Holding down the Space key while typing 15 character keys will input characters from group 6.
Pressing the Number key again and releasing it will switch back to the alphabet group.
To type capital letters, you can hold the Shift key while typing alphabet characters or press the Shift key twice to activate Caps Lock, and press it twice again to turn off Caps Lock.

To type supplementary characters without holding the Space key, press the Shift key twice to activate the supplementary group and press it twice again to turn it off.

5. Requirements Phase:
-Story, defining the purpose of creating the product.
-Identifying the basic requirements for the keyboard: Who is it for? What are the main features?
-Finalize basic requirements.
-Design Phase:
+Design detailed documentation (including a visual description of each key and its functionality).
+Design principles, block diagrams.
+Refine the system logic and prepare coding plans.
+Output: Completed documentation, system diagrams, implementation plans.
-Implementation Phase: (Circuit design using Altium.)
+Design and manufacture of hardware components (frame, keys, etc.).
+Coding based on the logic diagram created in the design phase, using Arduino IDE and C/C++.
-Verification Phase:
Testing the keyboard and addressing any bugs.
