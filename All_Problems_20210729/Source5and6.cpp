#include <iostream>
#include <regex>
#include <Windows.h>
#include <windot11.h>
#include <chrono>
#include <mutex>
#include <cstring>
#include <thread>
#include <future>
#include <random>
#include <fstream>
using namespace std;
#define N 5
void introMusic() {
	PlaySound(L"SnapInsta_Start.wav", NULL, SND_ASYNC);

}
void gamePlayMusic() {
	//PlaySound(L"Spice Opera.wav", NULL, SND_ASYNC );
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	PlaySound(L"SnapInsta.wav", NULL, SND_ASYNC);
}
void lodaingMusic() {
	PlaySound(L"SnapInsta_loading.wav", NULL, SND_ASYNC);
}
void wnningSoundEffect() {
	PlaySound(L"SnapInsta_Winer.wav", NULL, SND_ASYNC);

}
void threadFunction(std::future<void> futureObj)
{
	std::cout << "Starting the thread" << std::endl;
	while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
	{
		std::cout << "work done" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	std::cout << "Ending Thread" << std::endl;
}
int good_move = 0;
class TheGame {
private:
	char board[N][N];
public:
	int miniMax(char brd[N][N], int depth, bool isMaximizing) {
		int res = isWiner(brd);
		if (res != 0 || depth == 20) {
			return res;
		}
		if (isMaximizing) {
			int final_score = -10000;
			for (size_t move = 1; move < N - 1; move++) {
				for (size_t i = 0; i < N - 1; i++) {
					if (brd[move][i] == 26) {
						if (brd[move][i + 1] == 25) {
							if (i + 2 < N && brd[move][i + 2] == 22) {
								brd[move][i + 2] = 26;
								brd[move][i] = 22;
								int	score = miniMax(brd, depth + 1, false);
								brd[move][i + 2] = 22;
								brd[move][i] = 26;
								if (score > final_score) {
									final_score = score;
									good_move = move;
								}
							}
						}
						else if (brd[move][i + 1] == 22) {
							brd[move][i + 1] = 26;
							brd[move][i] = 22;
							int	score = miniMax(brd, depth + 1, false);
							brd[move][i + 1] = 22;
							brd[move][i] = 26;
							if (score > final_score) {
								final_score = score;
								good_move = move;
							}
						}
					}
				}
			}
			if (final_score == -10000) {
				return 5;
			}
			return final_score;
		}
		if (!isMaximizing) {
			int final_score = 10000;
			for (size_t move = 1; move < N - 1; move++) {
				for (size_t i = 0; i < N - 1; i++) {
					if (brd[i][move] == 25) {
						if (brd[i + 1][move] == 22) {
							brd[i + 1][move] = 25;
							brd[i][move] = 22;
							int score = miniMax(brd, depth + 1, true);
							brd[i + 1][move] = 22;
							brd[i][move] = 25;
							if (score < final_score) {
								final_score = score;
								good_move = move;
							}
						}
						else if (brd[i + 1][move] == 26) {
							if (i + 2 < N && brd[i + 2][move] == 22) {
								brd[i + 2][move] = 25;
								brd[i][move] = 22;
								int score = miniMax(brd, depth + 1, true);
								brd[i + 2][move] = 22;
								brd[i][move] = 25;
								if (score < final_score) {
									final_score = score;
									good_move = move;
								}
							}
						}
					}
				}
			}
			if (final_score == 10000) {
				return 5;
			}
			return final_score;
		}
	}
	int isWiner(char brd[N][N]) {
		int i = 1;
		if (board[N - 1][i] == 25 && board[N - 1][i + 1] == 25 && board[N - 1][i + 2] == 25) {
			return -1;
		}
		else if (board[i][N - 1] == 26 && board[i + 1][N - 1] == 26 && board[i + 2][N - 1] == 26) {
			return 1;
		}
		return 0;
	}
	void load() {
		system("cls");
		ifstream file("ascii-art.txt");
		string s;
		while (file)
		{
			getline(file, s);
			cout << s << endl;
		}
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<> distr(10, 50);
		cout << "Loading " << distr(gen) << " %.   ";
		Sleep(1500/2);
		cout << "\b\b\b\b..  ";
		Sleep(1000 / 2);
		cout << "\b\b\b\b... ";
		Sleep(1400 / 2);
		cout << "\b\b\b\b.   ";
		Sleep(1000 / 2);
		cout << "\b\b\b\b..  ";
		Sleep(1400 / 2);
		cout << "\b\b\b\b... ";
		Sleep(1000 / 2);
		cout << "\b\b\b\b\b\b\b\b";

		std::uniform_int_distribution<> distr2(51, 95);
		cout << distr2(gen) << " %.   ";
		Sleep(1400 / 2);
		cout << "\b\b\b\b..  ";
		Sleep(1000 / 2);
		cout << "\b\b\b\b... ";
		Sleep(1400 / 2);
		cout << "\b\b\b\b.   ";
		Sleep(1000 / 2);
		cout << "\b\b\b\b..  ";
		Sleep(1000 / 2);
		cout << "\b\b\b\b... ";
		Sleep(1000 / 2);
		cout << "\b\b\b\b\b\b\b\b";
		cout << "100%   ";
		Sleep(1000 / 2);

	}
	bool isValidNumber(string s) {
		regex valid("^[0-1]$");
		return regex_match(s, valid);
	}
	bool isValidMove(string s) {
		regex valid("^[1-N]$");
		return regex_match(s, valid);
	}
	void printBoard(char brd[N][N])
	{
		//cout << "\x1b[" << 1 << ";" << 1 << "H";
		//cout << "\x1b[?25l";
		system("cls");
		cout << "\n";
		for (size_t i = 0; i < N; i++)
		{
			if (i == 0 || i == N - 1)
				cout << "     ";
			else
				cout << "\x1b[42m" << i << "  " << "\x1b[0m";
		}
		cout << "\b\b\b\b\b\b\b.      \n";
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (j == 0) {
					if (i != 0 && i != N - 1)
						cout << "\x1b[46m" << i << "\x1b[0m" << " ";
					else
						cout << "  ";
				}
				if (board[i][j] == 25)
					cout << "\x1b[32m" << board[i][j] << "\x1b[0m" << "  ";

				else if (board[i][j] == 26)
					cout << "\x1b[36m" << board[i][j] << "\x1b[0m" << "  ";

				else
					cout << board[i][j] << "  ";
			}cout << "\n";
		}
		cout << "\n\n";
	}
	void fillBoard() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (j == 0 && i != 0 && i != N - 1)
					board[i][j] = char(26);
				else if (i == 0 && j != 0 && j != N - 1)
					board[i][j] = char(25);
				else
					board[i][j] = char(22);
			}
		}
		board[0][0] = char(254);
		board[0][N - 1] = char(254);
		board[N - 1][0] = char(254);
		board[N - 1][N - 1] = char(254);
	}
	bool updateBoard(char brd[N][N], int player, int move) {
		if (player == 1) {
			for (size_t i = 0; i < N - 1; i++)
			{
				if (brd[i][move] == 25) {
					if (brd[i + 1][move] == 22) {
						brd[i + 1][move] = 25;
						brd[i][move] = 22;
						return 1;
					}
					else if (brd[i + 1][move] == 26) {
						if (i + 2 < N && brd[i + 2][move] == 22) {
							brd[i + 2][move] = 25;
							brd[i][move] = 22;
							return 1;
						}
					}
				}
			}
		}
		if (player == 2) {
			for (size_t i = 0; i < N - 1; i++)
			{
				if (brd[move][i] == 26) {
					if (brd[move][i + 1] == 22) {
						brd[move][i + 1] = 26;
						brd[move][i] = 22;
						return 1;
					}
					else if (brd[move][i + 1] == 25) {
						if (i + 2 < N && brd[move][i + 2] == 22) {
							brd[move][i + 2] = 26;
							brd[move][i] = 22;
							return 1;
						}
					}
				}
			}
		}
		return 0;

	}
	void run() {
		std::thread this_thread(introMusic);
		fillBoard();
		/*cout << "												\n";
		cout << "		       ⣀⣠⣤⣶⣶⣶⣶⣶⣶⣦⣤⣄⡀					\n";
		cout << "	                ⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦					\n";
		cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀ ⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀";
		cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⣿⢿⣿⣿⣿⣿⢹⣿⣿⣿⠀⢰⣶⠀⠀⢹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀";
		cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⠸⣦⣌⣉⡉⢁⣾⠏⠀⢿⣆⠀⢀⣀⣤⡾⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
		cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡿⠏⡙⠷⣿⣿⣤⣤⣼⣿⣷⠶⠏⠻⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⠀\n⠀";
		cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣧⡁⠸⣤⢠⣄⢠⣤⢠⠄⠲⣠⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀";
		cout << "⠀⢀⣤⣤⣄⡀⠀⠀⣀⠀⢐⠛⢿⣦⣈⠛⠻⠿⣶⣬⣥⣬⣭⣬⡶⠿⠟⠋⣴⡾⠓⠩⠀⢠⣤⠀⣀⣤⣴⣶⡦   \n⠀";
		cout << "⠀⠀⠘⠟⡿⣿⡷⡞⠋⣠⠂⠀⠀⠀⠙⠣⣀⡀⠀⢄⣀⣀⡤⠀⠀⠀⡠⣼⠋⠀⠀⠀⠙⣄⠈⠟⠻⠛⡏⠉⠀⠀  \n⠀"⠀;
		cout << "⠀⠀⠀⠀⢣⠀⠀⠀⠈⠇⠀⠀⢹⠀⠀⠀⡏⠉⡗⢈⣙⡛⠃⢲⢛⠉⠁⠀⠀⢈⠀⠀⠀⠃⠀⠀⠀⡰⠀⠀⠀⠀ ⠀\n⠀";
		cout << "⠀⠀⠀⠀⠀⢇⠀⠀⠀⠀⠀⠀⢸⣆⠶⠖⠋⡉⢃⢸⣿⣿⡇⡟⢹⠀⢀⣰⠾⠹⠀⠀⠀⠀⠀⠀⡰⠁⠀⠀⠀⠀ ⠀\n⠀⠀";
		cout << "⠀⠀⠀⠀⠀⠀⠑⠠⢀⣀⣠⠤⡊⠀⠀⠀⢨⡗⣹⢸⣿⣿⡇⣇⡹⣀⠇⠀⠀⠀⠍⠲⠤⠤⠐⠊⠀⠀⠀⠀⠀⠀⠀ \n⠀"⠀;
		cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⠀⠀⠀⠀⢰⢸⡘⠛⠛⠃⣇⡗⠉⠀⠀⠀⢀⡜⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⠀\n⠀";
		cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⠷⠤⠄⠤⠜⠛⠛⠀⠁⠀⠘⠓⠒⠒⠒⠒⠿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀"⠀;
		cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡆⠀⠀⠰⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⠀\n⠀";
		cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢸⡇⠀⠀⠀⠀⢰⢱⠀⠀⠀⢸⣧⠀⠀⠀⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀\n⠀⠀";
		cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡆⠐⣏⠀⠀⠀⠀⠀⡼⠀⡆⠀⠀⠸⣿⠂⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀\n⠀⠀";
		cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠧⠬⠗⣀⠀⣀⣀⣀⠇⠀⠇⣀⣀⣀⣿⣥⡀⠤⠼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ \n "⠀;
		cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡀⠀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⣄⣀⣀⣀⠀⢀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ \n " ;
		cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣎⢛⡀⠀⠀⠀⠀⠀⠀⣘⣛⣛⠋⣵⣾⣿⣿⣿⡷⠀⠀⠀⠀⠀⠀⠀⠀  \n  ";*/

		cout << "Hello Welcome to \x1b[41mRocket Game\x1b[0m.\nPleace choose to play against another \x1b[32mhuman\x1b[0m  or against \x1b[36mcomputer\x1b[0m\nEnter \x1b[32m0\x1b[0m  to play against another \x1b[32mhuman\x1b[0m\nEnter \x1b[36m1\x1b[0m to play against \x1b[36mcomputer aka VMD's Ai\x1b[0m\n";
		string num;
		getline(cin, num);
		Beep(223, 200);
		while (!isValidNumber(num)) {
			cout << "\x1b[31mInvalid Input\x1b[0m\nPlease choose a Number 1 or 0 : \n";
			Beep(223, 500);
			getline(cin, num);
			Beep(223, 200);
		}
		std::thread this_thread2(lodaingMusic);
		load();
		system("cls");
		std::thread this_thread3(gamePlayMusic);
		while (true)
		{
			switch (stoi(num))
			{
			case 0:
				cout << "Humen\n";
				while (true)
				{
					static int player = 1;
					printBoard(board);
					if (isWiner(board)) {
						if (player == 1)
							cout << "\x1b[46mPlayer 2 Win\x1b[0m \n";
						if (player == 2)
							cout << "\x1b[42mPlayer 1 Win\x1b[0m\n";

						std::thread this_thread(wnningSoundEffect);
						while (true) {}
					}
					string move;
					while (true) {
						if (player == 1)
							cout << "\x1b[32mPlayer 1\x1b[0m";
						else if (player == 2)
							cout << "\x1b[36mPlayer 2\x1b[0m";

						cout << " Enter yor move : ";
						getline(cin, move);

						Beep(223, 200);
						while (!isValidMove(move)) {
							cout << "\x1b[31mInvalid Input\x1b[0m\nPlease choice a Number form 1 to " << N - 2 << "\n";
							Beep(223, 500);
							getline(cin, move);
							Beep(223, 200);
						}

						if (updateBoard(board, player, stoi(move)))
							break;
					}

					player = player % 2 + 1;

				}
				break;
			case 1:
				cout << "Ai\n";
				while (true)
				{
					static int player = 1;
					printBoard(board);
					if (isWiner(board)) {
						if (player == 1)
							cout << "\x1b[46mPlayer 2 Win\x1b[0m \n";
						if (player == 2)
							cout << "\x1b[42mPlayer 1 Win\x1b[0m\n";

						std::thread this_thread(wnningSoundEffect);
						while (true) {}
					}
					string move;
					while (true) {
						if (player == 1) {
							cout << "\x1b[32mPlayer 1\x1b[0m";
							cout << " Enter yor move : ";
							getline(cin, move);

							Beep(223, 200);
							while (!isValidMove(move)) {
								cout << "\x1b[31mInvalid Input\x1b[0m\nPlease choice a Number form 1 to " << N - 2 << "\n";
								Beep(223, 500);
								Beep(223, 500);
								getline(cin, move);
								Beep(223, 200);
							}
							if (updateBoard(board, player, stoi(move)))
								break;
						}
						else if (player == 2) {
							cout << "hello mf: " << good_move << endl;
							int draw = miniMax(board, 0, true);
							/*if (draw == 5) {
								cout << "Drwo\n";
								break;
							}*/
							if (updateBoard(board, player, good_move)) {
								cout << "\x1b[36mPlayer 2\x1b[0m";
								cout << " Ai move : " << good_move;
								break;
							}
							else {
								cout << "Drwo\n";
								break;
							}


						}
					}

					player = player % 2 + 1;

				}

			}
			break;
		}
	}
};
int main() {
	TheGame master;
	master.run();
}