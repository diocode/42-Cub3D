![so_long_banner-03](https://github.com/diocode/42-So_long/assets/107859177/f2d4d204-c35c-4eef-bb63-09aea6376882)

<p align="center">
	<img src="https://img.shields.io/badge/status-finished-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/badge/evaluated-05%20%2F%2011%20%2F%202024-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/badge/score-110%20%2F%20100-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/github/last-commit/diocode/philosophers?color=%2312bab9&style=flat-square"/>
	<a href='https://www.linkedin.com/in/diogo-gsilva' target="_blank"><img alt='Linkedin' src='https://img.shields.io/badge/LinkedIn-100000?style=flat-square&logo=Linkedin&logoColor=white&labelColor=0A66C2&color=0A66C2'/></a>
</p>

<p align="center">
	<a href="#about">About</a> •
	<a href="#how-to-use">How to use</a> •
	<a href="#examples">Examples</a> •
	<a href="#norminette">Norminette</a>
</p>

## ABOUT ([Subject](/.github/en.subject.pdf))

<br>

<p align="center">
  <img src="https://github.com/diocode/42-So_long/blob/master/.github/so_long.gif" alt="Alt Text">
</p>

<br>

Cub3D is a simple first-person 3D game inspired by Wolfenstein 3D, built using MiniLibX and raycasting techniques. The game renders a maze-like environment where players can move using WASD keys and rotate their view with the arrow keys. Walls are textured based on direction, and floor/ceiling colors are customizable. The game reads a .cub configuration file to define the map, player position, and textures, ensuring proper structure and error handling.

For bonuses, additional features like wall collisions and mouse-based rotation can be added. The project strengthens skills in C programming, graphics rendering, and event handling, offering an introduction to game development fundamentals. 🚀

<a href="/.github/en.subject.pdf">Click here</a> for the subject of this project.

<br>

## HOW TO USE
#### COMPILATION AND EXECUTION
#### 1º - Clone the repository
```bash
$ git clone git@github.com:diocode/42-Cub3D.git
```
> Download the minlibx lib and add it to the libs folder. Then install the dependecies if necessary
```bash
$ sudo apt update
$ sudo apt install libx11-dev libxext-dev libxrandr-dev libxinerama-dev libxcursor-dev libbsd-dev
```

#### 2º - Enter the project folder and run `make` or `make bonus`
```bash
$ ./cd 42-Cub3D
$ ./make
```

#### 3º - Launch the program
> You can use any of the maps inside `maps` folder
#### Mandatory:
```bash
$ ./cub3d [".cub" map file]
```

<br>

#### MAKEFILE COMMANDS
`make` or `make all` - Compile program **mandatory** files.

`make clean` - Delete all .o (object files) files.

`make fclean` - Delete all .o (object file) and .a (executable) files.

`make re` - Use rules `fclean` + `all`.

#### TIPS
- Make sure you have minlibx downloaded.
- Have X11 lib updated.
- Use valgrind to check for leaks:
```bash
$ valgrind -s ./cub3d [".cub" map file]
```

<br>

## EXAMPLES
 > Map suggestions
 ```bash
$ ./cub3d maps/demo.cub
```
<br>

## NORMINETTE
At 42 School, projects are generally expected to adhere to the Norm, the school's coding standard:

```
- No for, do while, switch, case or goto are allowed
- No more than 25 lines per function and 5 functions per file
- No assigns and declarations in the same line (unless static)
- No more than 5 variables in 1 function
... 
```

* [Norminette](https://github.com/42School/norminette) - Tool by 42, to respect the code norm. `GitHub`
* [42 Header](https://github.com/42Paris/42header) - 42 header for Vim. `GitHub`
