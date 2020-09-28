**Gameboy Classic emulator** project for playing childhood roms
and to learn more about coding virtual machines.

```
- To do list:
  - [ ] main update loop
    - [x] read op byte
    - [x] update timer
    - [ ] update graphics
      - [x] tiles
      - [ ] sprites
    - [x] handle interrupts
    - [ ] render wit SDL
      - [x] lcd screen (play area, just make it nice)
      - [ ] debug lcd screen (whole video memory are)
      - [ ] debug window for registers
  - [ ] all ops (25.9 511 / 512)
  - [ ] memory bank controllers (mbc)
    - [ ] 0 started
    - [ ] 1 started
    - [ ] 2
    - [x] 3 (because of pokemon red uses mbc3)
    - [ ] 5
  - [ ] gameboy color palette ?
  ```
  Testing with MacOS Catalina and Mojave
  Compiling with GCC
