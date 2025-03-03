![ASSEMBLY](https://img.shields.io/badge/_-ASM-6E4C13.svg?style=for-the-badge)
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

# General information

This is the final task of the DOS assembler course by [Ilya Dedinsky](https://github.com/ded32).

My course friend, [Egor](https://github.com/4Locker4) and I wrote two CrackMe program and sent them to each other for hacking.
The programs are similar in its idea: the user must enter a password, if its correct, an inscription corresponding to this will appear. The goal is to receive this message without knowing the password.

## Content

- [Egor's program (CRACK.COM)](#Egor's-program-(CRACK.COM))
    - [Vulnerability 1: buffer overflow](#Vulnerability-1:-buffer-overflow)
    - [Vulnerability 2: buffer overflow but more interesting](#Vulnerability-2:-buffer-overflow-but-more-interesting)
- [My program](#My-program)
    - [Vulnerability 1: love jmp](#Vulnerability-1:-love-jmp)
    - [Vulnerability 2: stack overflow](#Vulnerability-2:-stack-overflow)
- [My Patcher](#My-Patcher)

## Egor's program (CRACK.COM)

The program greets the user like this:
![greeting](img/greeting.png)
