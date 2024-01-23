/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:02:46 by asalic            #+#    #+#             */
/*   Updated: 2024/01/23 18:26:56 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_window	*get_window_instance(void)
{
	static t_window	instance;

	return (&instance);
}

void	initializer_audio(t_window *window)
{
	window->sound.init = SDL_Init(SDL_INIT_AUDIO);
	if (window->sound.init < 0)
	{
		ft_printf(RED"Error : music init\n"NC);
		destroy_window(window);
	}
	if (SDL_LoadWAV("./Palladio.wav", &window->sound.wav_spec, \
	&window->sound.wav_buffer, &window->sound.wav_lenght) == NULL)
	{
		ft_printf(RED"Error : music loading\n"NC);
		destroy_window(window);
	}
	window->sound.audio_device = SDL_OpenAudioDevice(NULL, 0, \
	&window->sound.wav_spec, NULL, 0);
	if (window->sound.audio_device == 0)
	{
		ft_printf(RED"Error : music opening\n"NC);
		destroy_window(window);
	}
}

void	play_music(void *data)
{
	t_window	*window;

	window = (t_window *)data;
	while (1)
	{
		if (SDL_QueueAudio(window->sound.audio_device, \
		window->sound.wav_buffer, window->sound.wav_lenght) == -1)
		{
			ft_printf(RED"Error : playlist\n"NC);
			destroy_window(window);
		}
		SDL_PauseAudioDevice(window->sound.audio_device, 0);
		SDL_Delay((window->sound.wav_lenght / (2 * \
		window->sound.wav_spec.channels)) * 1000 / \
		window->sound.wav_spec.freq);
		usleep(2000);
	}
	pthread_exit(NULL);
}
