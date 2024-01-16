/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:00:56 by asalic            #+#    #+#             */
/*   Updated: 2024/01/16 19:01:46 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Test audio 
 * Documentation library SDL.h
 * Test a la norme sur une fenetre simple de la mlx
 * Test sans leaks */

#include "main.h"
SDL_AudioDeviceID audioDevice;
Uint8 *wavBuffer;

void cleanup()
{
    SDL_CloseAudioDevice(audioDevice);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();
}

int	close_wndow(t_data *data)
{
	int	i;

	i = 0;
	mlx_destroy_window(data->ptr, data->window);
	printf("La fenetre se ferme.");
	mlx_destroy_display(data->ptr);
	free(data->ptr);
	atexit(cleanup);
	exit (EXIT_FAILURE);
}

int main()
{
	t_data 		data;

	data.ptr = mlx_init();
	if (!data.ptr)
		return (0);
	data.window = mlx_new_window(data.ptr, WIDTH, HEIGHT, "test audio");
	if (!data.window)
	{
		mlx_destroy_display(data.ptr);
		free(data.ptr);
		return (0);
	}
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
        fprintf(stderr, "Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;

    if (SDL_LoadWAV("Palladio.wav", &wavSpec, &wavBuffer, &wavLength) == NULL)
	{
        fprintf(stderr, "Erreur lors du chargement du fichier audio : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    audioDevice = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (audioDevice == 0)
	{
        fprintf(stderr, "Erreur lors de l'ouverture du périphérique audio : %s\n", SDL_GetError());
        SDL_FreeWAV(wavBuffer);
        SDL_Quit();
        return 1;
    }
	printf("lancement\n");
	// while (data.ptr)
	// {
		SDL_QueueAudio(audioDevice, wavBuffer, wavLength);
    	SDL_PauseAudioDevice(audioDevice, 0);
		SDL_Delay((wavLength / (2 * wavSpec.channels)) * 1000 / wavSpec.freq);
	// }
	mlx_hook(data.window, 17, 0, close_wndow, &data);
	mlx_loop(data.ptr);
    return 0;
}
