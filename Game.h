#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

class Game {
public:
	Game() {
	}
	~Game() {
	}
	bool Init();
	void HandleEvents();
	bool LoadMedia();
	static void Close();
	void Render();
};

#endif // GAME_H_INCLUDED
