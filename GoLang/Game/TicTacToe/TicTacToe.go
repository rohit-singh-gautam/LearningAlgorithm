package main

import (
	"bytes"
	"fmt"
	"math/rand"
	"os"
)

type Game struct {
	board  [3][3]rune // 3x3 board
	player rune       // current player
}

type Move struct {
	X, Y int
}

func (g *Game) play(x, y int) {
	if g.board[x][y] == 0 {
		g.board[x][y] = g.player
		g.player = 'X' - g.player + 'O'
	} else {
		// Reverting move
		g.board[x][y] = 0
		g.player = 'X' - g.player + 'O'
	}
}

func (g *Game) playMove(move Move) {
	x, y := move.X, move.Y
	if g.board[x][y] == 0 {
		g.board[x][y] = g.player
		g.player = 'X' - g.player + 'O'
	} else {
		// Reverting move
		g.board[x][y] = 0
		g.player = 'X' - g.player + 'O'
	}
}

func (g *Game) winner() rune {
	for i := 0; i < 3; i++ {
		if g.board[0][i] != 0 && g.board[0][i] == g.board[1][i] && g.board[1][i] == g.board[2][i] {
			return g.board[0][i]
		}
		if g.board[i][0] != 0 && g.board[i][0] == g.board[i][1] && g.board[i][1] == g.board[i][2] {
			return g.board[i][0]
		}
	}

	if g.board[0][0] != 0 && g.board[0][0] == g.board[1][1] && g.board[1][1] == g.board[2][2] {
		return g.board[1][1]
	}

	if g.board[0][2] != 0 && g.board[0][2] == g.board[1][1] && g.board[1][1] == g.board[2][0] {
		return g.board[1][1]
	}

	return 0
}

func (g *Game) GetMoves() []Move {
	moves := []Move{}
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			if g.board[i][j] == 0 {
				moves = append(moves, Move{i, j})
			}
		}
	}
	return moves
}

func (g *Game) IsOver() bool {
	return g.winner() != 0 || len(g.GetMoves()) == 0
}

func (g *Game) MinMax() int {
	allMoves := g.GetMoves()
	moveLeft := len(allMoves)
	if w := g.winner(); w != 0 {
		return -moveLeft - 1
	}
	if moveLeft == 0 {
		return 0
	}

	bestScore := -1000
	for _, move := range allMoves {
		g.playMove(move)
		score := -g.MinMax()
		g.playMove(move)
		if score > bestScore {
			bestScore = score
		}
	}
	return bestScore
}

func (g *Game) BestMove() Move {
	if g.player == 0 {
		g.player = 'X'
	}
	bestScore := -1000
	var bestMoves []Move
	for _, move := range g.GetMoves() {
		g.playMove(move)
		score := -g.MinMax()
		g.playMove(move)
		if score == bestScore {
			bestMoves = append(bestMoves, move)
		} else if score > bestScore {
			bestScore = score
			bestMoves = []Move{move}
		}
	}
	bestMovesLen := len(bestMoves)
	return bestMoves[rand.Intn(bestMovesLen)]
}

func (g *Game) String() string {
	var b bytes.Buffer
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			if g.board[i][j] == 0 {
				b.WriteRune('.')
			} else {
				b.WriteRune(g.board[i][j])
			}
		}
		b.WriteRune('\n')
	}
	return b.String()
}

func (g *Game) CheckAndPrint() bool {
	fmt.Println(g)
	if g.winner() != 0 {
		fmt.Printf("%c wins!\n", g.winner())
		return true
	}
	if len(g.GetMoves()) == 0 {
		fmt.Println("Draw!")
		return true
	}
	return false
}

func (g *Game) MakeMove(humanPlayer bool) bool {
	if humanPlayer {
		for {
			var x, y int
			fmt.Print("Enter x y: ")
			fmt.Scanf("%d %d", &x, &y)
			if x < 0 || x >= 3 || y < 0 || y >= 3 || g.board[x][y] != 0 {
				fmt.Println("Invalid move enter again")
			} else {
				g.play(x, y)
				break
			}
		}
	} else {
		move := g.BestMove()
		g.playMove(move)
	}
	return g.CheckAndPrint()
}

func main() {
	if len(os.Args) != 3 {
		fmt.Println("Usage: ", os.Args[0], " (first player [computer|human]) (second player [computer|human])")
		fmt.Println("Example: ", os.Args[0], " human computer")
		return
	}
	if os.Args[1] != "human" && os.Args[1] != "computer" {
		fmt.Println("Invalid first player")
		return
	}
	if os.Args[2] != "human" && os.Args[2] != "computer" {
		fmt.Println("Invalid second player")
		return
	}
	var firstPlayerHuman bool = os.Args[1] == "human"
	var secondPlayerHuman bool = os.Args[2] == "human"

	var g Game
	g.player = 'X'
	for {
		if g.MakeMove(firstPlayerHuman) {
			break
		}
		if g.MakeMove(secondPlayerHuman) {
			break
		}
	}
}
