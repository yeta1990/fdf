#include <OpenGL/gl3.h>
#include <stdlib.h>
#include "mlx_int.h"

void	free_mlx_ptr(void *mlx)
{
	free(((mlx_ptr_t *)(mlx))->font->buffer);
	free(((mlx_ptr_t *)(mlx))->font);
	free(mlx);
}
