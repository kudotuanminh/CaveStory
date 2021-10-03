#include <game.h>

int main(int argc, char *argv[]) {
    // srand(time(NULL));
    // if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    // 	std::cerr << Mix_GetError();

    // std::string path = "content/music/";
    // std::vector<Mix_Music *> bgMusic;
    // for (int i = 1; i < 7; i++)
    // {
    // 	Mix_Music *temp = Mix_LoadMUS((path + std::to_string(i) +
    // ".mp3").c_str()); 	if (temp == NULL) 		std::cerr << "\nError: Unable
    // to load music\n"; 	bgMusic.push_back(temp);
    // }
    // Mix_PlayMusic(bgMusic[rand() % 6], 1);

    Game game;

    return 0;
}
