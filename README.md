**Gameboy Classic emulator** project for playing childhood roms
and to learn more about coding virtual machines.

```
- To do list:
  - [ ] main update loop
    - [x] read op byte
    - [x] update timer
    - [ ] update graphics
      - [x] tiles
      - [ ] sprites (done, but need to test more before happy with it)
    - [x] handle interrupts
    - [ ] render wit SDL
      - [x] lcd screen (play area, just make it nice)
      - [ ] debug lcd screen (whole video memory are)
      - [ ] debug window for registers (atm prits in stdout, with step or addr selection)
  - [x] all ops (1.10 2:28)
  - [ ] memory bank controllers (mbc)
    - [ ] 0
    - [1] 1
    - [ ] 2
    - [ ] 3(90%) almost like 1 wit little modifications
    - [ ] 5
  - [ ] gameboy color palette ?
  ```

	![](gameboy_boot_18-36-03.gif)
	
  Testing with MacOS Catalina and Mojave
  Compiling with GCC
