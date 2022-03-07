# fdf (42 project)

## Description

Draw 3d wireframes from 2d maps using the [Minilibx](https://github.com/42Paris/minilibx-linux) graphical engine

### Example of raw map:

```0 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```

### Its wireframe:

<img src="fdf2.png" width="500">

## Description

Graphical

## Instructions and usage

-   `make`
-   Usage : `./fdf [map.fdf] <filename> [ case_size z_size ]` where _case_size_ param is the square width and _z-size_ is the proportion and orientation of z-axis.
