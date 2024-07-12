#include <iostream>
#include <vector>
#include <memory>
#include <string>

enum class Color { WHITE, BLACK };

class Piece {
public:
    Piece(Color color) : color(color) {}
    virtual ~Piece() = default;
    virtual char getSymbol() const = 0;
    Color getColor() const { return color; }
    virtual bool isValidMove(int sx, int sy, int dx, int dy, const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const = 0;

protected:
    Color color;
};

class Pawn : public Piece {
public:
    Pawn(Color color) : Piece(color) {}
    char getSymbol() const override { return color == Color::WHITE ? 'P' : 'p'; }
    bool isValidMove(int sx, int sy, int dx, int dy, const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const override {
        int direction = (color == Color::WHITE) ? -1 : 1;
        if (dx == sx + direction && sy == dy && !board[dx][dy]) {
            return true; // Move forward
        }
        if (dx == sx + direction && (dy == sy - 1 || dy == sy + 1) && board[dx][dy] && board[dx][dy]->getColor() != color) {
            return true; // Capture
        }
        return false;
    }
};

class Board {
public:
    Board() {
        board.resize(8, std::vector<std::shared_ptr<Piece>>(8, nullptr));
        setupBoard();
    }

    void setupBoard() {
        for (int i = 0; i < 8; ++i) {
            board[1][i] = std::make_shared<Pawn>(Color::BLACK);
            board[6][i] = std::make_shared<Pawn>(Color::WHITE);
        }
    }

    void printBoard() const {
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if (board[row][col]) {
                    std::cout << board[row][col]->getSymbol() << ' ';
                } else {
                    std::cout << ". ";
                }
            }
            std::cout << std::endl;
        }
    }

    bool movePiece(int sx, int sy, int dx, int dy) {
        if (sx < 0 || sx >= 8 || sy < 0 || sy >= 8 || dx < 0 || dx >= 8 || dy < 0 || dy >= 8) {
            return false;
        }
        if (board[sx][sy] && board[sx][sy]->isValidMove(sx, sy, dx, dy, board)) {
            board[dx][dy] = board[sx][sy];
            board[sx][sy] = nullptr;
            return true;
        }
        return false;
    }

    std::shared_ptr<Piece> getPiece(int x, int y) const {
        if (x < 0 || x >= 8 || y < 0 || y >= 8) return nullptr;
        return board[x][y];
    }

private:
    std::vector<std::vector<std::shared_ptr<Piece>>> board;
};

class Game {
public:
    Game() : currentPlayer(Color::WHITE), board() {}

    void run() {
        while (true) {
            board.printBoard();
            std::cout << (currentPlayer == Color::WHITE ? "White" : "Black") << "'s turn. Enter move (e.g., e2 e4): ";
            std::string move;
            std::getline(std::cin, move);
            if (processMove(move)) {
                currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
            } else {
                std::cout << "Invalid move. Try again." << std::endl;
            }
        }
    }

private:
    bool processMove(const std::string& move) {
        if (move.size() != 5 || move[2] != ' ') return false;

        int sy = move[0] - 'a';
        int sx = move[1] - '1';
        int dy = move[3] - 'a';
        int dx = move[4] - '1';

        if (sx < 0 || sx >= 8 || sy < 0 || sy >= 8 || dx < 0 || dx >= 8 || dy < 0 || dy >= 8) {
            return false;
        }

        auto piece = board.getPiece(sx, sy);
        if (!piece || piece->getColor() != currentPlayer) {
            return false;
        }

        return board.movePiece(sx, sy, dx, dy);
    }

    Color currentPlayer;
    Board board;
};

int main() {
    Game game;
    game.run();
    return 0;
}
