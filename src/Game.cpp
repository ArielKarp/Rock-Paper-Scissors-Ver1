/*
 * Game.cpp
 *
 *  Created on: Mar 29, 2018
 *      Author: gasha
 */

#include "Game.h"

Game::Game(int a_N, int a_M, std::vector<std::pair<char, int> >& a_piecesLimit,
		const std::string& a_player1PositionFileName,
		const std::string& a_player1MovesFileName,
		const std::string& a_player2PositionFileName,
		const std::string& a_player2MovesFileName,
		const std::string& a_outPutName) :
		m_piecesLimit(a_piecesLimit) {

	// create games pieces
	m_emptyPiece = new BasicPiece(PieceChar::EMPTY);
	m_lowFlagPiece = new BasicPiece(PieceChar::FLAG, false);
	m_upperFlagPiece = new BasicPiece(PieceChar::FLAG, true);

	m_lowBombPiece = new BasicPiece(PieceChar::BOMB, false);
	m_upperBombPiece = new BasicPiece(PieceChar::BOMB, true);

	m_lowSciPiece = new BasicPiece(PieceChar::SCISSORS, false);
	m_upperSciPiece = new BasicPiece(PieceChar::SCISSORS, true);

	m_lowPaperPiece = new BasicPiece(PieceChar::PAPER, false);
	m_upperPaperPiece = new BasicPiece(PieceChar::PAPER, true);

	m_lowRockPiece = new BasicPiece(PieceChar::ROCK, false);
	m_upperRockPiece = new BasicPiece(PieceChar::ROCK, true);

	m_lowJokerBombPiece = new Joker(PieceChar::JOKER, false);
	m_upperJokerBombPiece = new Joker(PieceChar::JOKER, true);
	m_lowJokerBombPiece->setSymbol(PieceChar::BOMB);
	m_upperJokerBombPiece->setSymbol(PieceChar::BOMB);

	m_lowJokerSciPiece = new Joker(PieceChar::JOKER, false);
	m_upperJokerSciPiece = new Joker(PieceChar::JOKER, true);
	m_lowJokerSciPiece->setSymbol(PieceChar::SCISSORS);
	m_upperJokerSciPiece->setSymbol(PieceChar::SCISSORS);

	m_lowJokerPaperPiece = new Joker(PieceChar::JOKER, false);
	m_upperJokerPaperPiece = new Joker(PieceChar::JOKER, true);
	m_lowJokerPaperPiece->setSymbol(PieceChar::PAPER);
	m_upperJokerPaperPiece->setSymbol(PieceChar::PAPER);

	m_lowJokerRockPiece = new Joker(PieceChar::JOKER, false);
	m_upperJokerRockPiece = new Joker(PieceChar::JOKER, true);
	m_lowJokerRockPiece->setSymbol(PieceChar::ROCK);
	m_upperJokerRockPiece->setSymbol(PieceChar::ROCK);

	// create lower pieces vector, order as defined by basicpiece enum
	std::vector<BasicPiece*> l_lowerPieces = { m_lowFlagPiece,
			m_lowJokerBombPiece, m_lowJokerSciPiece, m_lowJokerPaperPiece,
			m_lowJokerRockPiece, m_lowBombPiece, m_lowSciPiece, m_lowPaperPiece,
			m_lowRockPiece };

	// create lower pieces vector, order as defined by basicpiece enum
	std::vector<BasicPiece*> l_upperPieces = { m_upperFlagPiece,
			m_upperJokerBombPiece, m_upperJokerSciPiece, m_upperJokerPaperPiece,
			m_upperJokerRockPiece, m_upperBombPiece, m_upperSciPiece,
			m_upperPaperPiece, m_upperRockPiece };

	// create players
	int id1 = 1;
	int id2 = 2;
	m_player1 = new Player(id1, a_player1PositionFileName,
			a_player1MovesFileName, l_upperPieces, a_M, a_N, true);
	m_player2 = new Player(id2, a_player2PositionFileName,
			a_player2MovesFileName, l_lowerPieces, a_M, a_N, false);

	// Set current player
	m_current_player = m_player1;

	// create main matrix
	m_piecesMatrix = new std::vector<std::vector<BasicPiece*> >(a_M,
			std::vector<BasicPiece*>(a_N, m_emptyPiece));

	m_status = CONTINUE;

	m_outFileStream = NULL;
	m_outFileName = a_outPutName;
}

Game::~Game() {

	if (m_player1) {
		delete m_player1;
		m_player1 = NULL;
	}
	if (m_player2) {
		delete m_player2;
		m_player2 = NULL;
	}

	m_current_player = NULL;

	if (m_piecesMatrix) {
		delete m_piecesMatrix;
	}

	if (m_outFileStream) {
		delete m_outFileStream;
		m_outFileStream = NULL;
	}

	if (m_emptyPiece) {
		delete m_emptyPiece;
	}
	if (m_lowFlagPiece) {
		delete m_lowFlagPiece;
	}
	if (m_upperFlagPiece) {
		delete m_upperFlagPiece;
	}
	if (m_lowBombPiece) {
		delete m_lowBombPiece;
	}
	if (m_upperBombPiece) {
		delete m_upperBombPiece;
	}
	if (m_lowSciPiece) {
		delete m_lowSciPiece;
	}
	if (m_upperSciPiece) {
		delete m_upperSciPiece;
	}
	if (m_lowPaperPiece) {
		delete m_lowPaperPiece;
	}
	if (m_upperPaperPiece) {
		delete m_upperPaperPiece;
	}
	if (m_lowRockPiece) {
		delete m_lowRockPiece;
	}
	if (m_upperRockPiece) {
		delete m_upperRockPiece;
	}
	if (m_lowJokerBombPiece) {
		delete m_lowJokerBombPiece;
	}
	if (m_upperJokerBombPiece) {
		delete m_upperJokerBombPiece;
	}
	if (m_lowJokerSciPiece) {
		delete m_lowJokerSciPiece;
	}
	if (m_upperJokerSciPiece) {
		delete m_upperJokerSciPiece;
	}
	if (m_lowJokerPaperPiece) {
		delete m_lowJokerPaperPiece;
	}
	if (m_upperJokerPaperPiece) {
		delete m_upperJokerPaperPiece;
	}
	if (m_lowJokerRockPiece) {
		delete m_lowJokerRockPiece;
	}
	if (m_upperJokerRockPiece) {
		delete m_upperJokerRockPiece;
	}

}

GameStatus Game::getStatus() {
	return m_status;
}

void Game::playGame() {
	initBoard();
	if (m_status == OPEN_FAIL_FAILED) {
		return;
	}
	// position files are ok, check moves file and create output
	if (!m_player1->getMoveAnalyzer()->isInpuFileStreamGood()  || !m_player2->getMoveAnalyzer()->isInpuFileStreamGood()) {
		return;
	}
	// create output file
	createOutputFileStream();
	if (m_status != CONTINUE) { // game is done after init
		*m_outFileStream << *this;
	} else { //start moves
		while (m_status == CONTINUE) {
			doNextMove();
		}
		//status is not continue
		*m_outFileStream << *this;
	}
}

void Game::initBoard() {
	int l_player_1_init = m_player1->initPlayer(m_piecesMatrix, m_piecesLimit,
			m_battleToPerform);
	int l_player_2_init = m_player2->initPlayer(m_piecesMatrix, m_piecesLimit,
			m_battleToPerform);
	if ((l_player_1_init == FILE_OPEN_ERROR)
			|| (l_player_2_init == FILE_OPEN_ERROR)) {
		m_status = OPEN_FAIL_FAILED;
	}
	else if ((l_player_1_init != GOOD) && (l_player_2_init != GOOD)) {
		m_status = TIE_BAD_POS;
	} else if ((l_player_1_init == GOOD) && (l_player_2_init != GOOD)) {
		m_status = PLAYER2_LOSE_BAD_POS;
	} else if ((l_player_1_init != GOOD) && (l_player_2_init == GOOD)) {
		m_status = PLAYER1_LOSE_BAD_POS;
	} else {
		performBattles();
		m_status = checkStatusAfterMove();
		m_player1->setLineNum(0);
		m_player2->setLineNum(0);
	}
}

void Game::switchCurrentPlayer() {
	if (m_current_player == m_player1) {
		m_current_player = m_player2;
	} else {
		m_current_player = m_player1;
	}
}

void Game::doNextMove() {
	m_current_player->setLineNum((m_current_player->getLineNum()) + 1);
	MoveCommand l_outCommand;
	FileStatus rc = m_current_player->doNextMove(m_piecesMatrix, l_outCommand);
	if (rc == NO_FILE) {
		m_status = OPEN_FAIL_FAILED;
	} else if (rc == ERROR) {
		if (m_current_player == m_player1) {
			m_status = PLAYER1_LOSE_BAD_MOVE;
		} else {
			m_status = PLAYER2_LOSE_BAD_MOVE;
		}
	} else if (rc == END_OF_FILE) {
		m_current_player->setEOF(true);
		if ((m_player1->getEOF() == true) && (m_player2->getEOF() == true)) {
			m_status = TIE;
		} else {
			switchCurrentPlayer();
		}
	} else if (rc == OK) {
		//make the move!
		if (((*m_piecesMatrix)[l_outCommand.dest_row - 1][l_outCommand.dest_col
				- 1]->getSymbol() == PieceChar::EMPTY)) { // there is no piece
			updatePiecesMatrix(l_outCommand.dest_row - 1,
					l_outCommand.dest_col - 1,
					(*m_piecesMatrix)[l_outCommand.src_row - 1][l_outCommand.src_col
							- 1]);
			removePieceFromMatrix(l_outCommand.src_row - 1,
					l_outCommand.src_col - 1);
		} else { //battle
			BattleRep l_battle_to_add;
			l_battle_to_add.dest_col = l_outCommand.dest_col - 1;
			l_battle_to_add.dest_row = l_outCommand.dest_row - 1;
			l_battle_to_add.pieceToPosition =
					(*m_piecesMatrix)[l_outCommand.src_row - 1][l_outCommand.src_col
							- 1];
			m_battleToPerform.push_back(l_battle_to_add);
			removePieceFromMatrix(l_outCommand.src_row - 1,
					l_outCommand.src_col - 1);
			performBattles();
		}

		if (l_outCommand.j_rep != '_') { //joker rep
			reducePieceCountOfPlayer((*m_piecesMatrix)[l_outCommand.j_row - 1][l_outCommand.j_col - 1]);
			(*m_piecesMatrix)[l_outCommand.j_row - 1][l_outCommand.j_col - 1] =
					m_current_player->getPointerToPiece(JOKER,
							l_outCommand.j_rep);
			increasePieceCountOfPlayer((*m_piecesMatrix)[l_outCommand.j_row - 1][l_outCommand.j_col - 1]);

		}
		m_status = checkStatusAfterMove();
		switchCurrentPlayer();
	}
}

GameStatus Game::checkStatusAfterMove() {
	if ((m_player1->getCountOfPiece(PieceChar::FLAG) == 0)
			&& (m_player2->getCountOfPiece(PieceChar::FLAG) == 0)) {
		return TIE_NO_FLAGS;
	} else if (m_player1->getCountOfPiece(PieceChar::FLAG) == 0) {
		return PLAYER2_WIN_FLAGS;
	} else if (m_player2->getCountOfPiece(PieceChar::FLAG) == 0) {
		return PLAYER1_WIN_FLAGS;
	} else if ((!(m_player1->havePiecestoMove()))
			&& (!(m_player2->havePiecestoMove()))) {
		return TIE_NO_MOVING;
	} else if (!(m_player1->havePiecestoMove())) {
		return PLAYER2_WIN_MOVING_PIECES;
	} else if
			(!(m_player2->havePiecestoMove())) {
		return PLAYER1_WIN_MOVING_PIECES;
	}
	return CONTINUE;
}

void Game::updatePiecesMatrix(int a_row, int a_col, BasicPiece* a_piece) {
	(*m_piecesMatrix)[a_row][a_col] = a_piece;
}

void Game::removePieceFromMatrix(int a_row, int a_col) {
	(*m_piecesMatrix)[a_row][a_col] = m_emptyPiece;
}

void Game::reducePieceCountOfPlayer(const BasicPiece* a_inPiece) {
	if (a_inPiece->getUpper()) {
		m_player1->reducePiecesCount(a_inPiece);
	} else {
		m_player2->reducePiecesCount(a_inPiece);
	}
}

void Game::increasePieceCountOfPlayer(const BasicPiece* a_inPiece) {
	if (a_inPiece->getUpper()) {
		m_player1->increasePiecesCount(a_inPiece);
	} else {
		m_player2->increasePiecesCount(a_inPiece);
	}
}

void Game::commenceBattle(const BattleRep& a_inBattle) {
	int l_colLocation = a_inBattle.dest_col;
	int l_rowLocation = a_inBattle.dest_row;

	BasicPiece* l_boardPiece = (*m_piecesMatrix)[l_rowLocation][l_colLocation];
	BasicPiece* l_battlePiece = a_inBattle.pieceToPosition;
	if (l_boardPiece->getSymbol() == PieceChar::BOMB
			|| l_battlePiece->getSymbol() == PieceChar::BOMB) {
		removePieceFromMatrix(l_rowLocation, l_colLocation);
		reducePieceCountOfPlayer(l_boardPiece);
		reducePieceCountOfPlayer(l_battlePiece);

	} else if (*l_boardPiece == *l_battlePiece) {
		removePieceFromMatrix(l_rowLocation, l_colLocation);
		reducePieceCountOfPlayer(l_boardPiece);
		reducePieceCountOfPlayer(l_battlePiece);

	} else if (*l_boardPiece < *l_battlePiece) {
		updatePiecesMatrix(l_rowLocation, l_colLocation, l_battlePiece);
		reducePieceCountOfPlayer(l_boardPiece);
	} else {
		reducePieceCountOfPlayer(l_battlePiece);

	}
}

void Game::performBattles() {
	std::vector<BattleRep>::const_iterator it = m_battleToPerform.begin();
	for (; it != m_battleToPerform.end(); ++it) {
		commenceBattle(*it);
	}
	// clear vector battles
	m_battleToPerform.clear();
	m_battleToPerform.shrink_to_fit();
}

int Game::winnerNumByStatus() const {
	switch (m_status) {
	case PLAYER1_WIN_FLAGS:
		return 1;
	case PLAYER2_WIN_FLAGS:
		return 2;
	case PLAYER1_WIN_MOVING_PIECES:
		return 1;
	case PLAYER2_WIN_MOVING_PIECES:
		return 2;
	case TIE:
		return 0;
	case TIE_NO_FLAGS:
		return 0;
	case PLAYER1_LOSE_BAD_POS:
		return 2;
	case PLAYER2_LOSE_BAD_POS:
		return 1;
	case TIE_BAD_POS:
		return 0;
	case PLAYER1_LOSE_BAD_MOVE:
		return 2;
	case PLAYER2_LOSE_BAD_MOVE:
		return 1;
	case OPEN_FAIL_FAILED:
		return 0;
	case TIE_NO_MOVING:
		return 0;
	case CONTINUE:
		return 0;

	}
	return 0;
}

std::string Game::reasonByStatus() const {
	switch (m_status) {
	case PLAYER1_WIN_FLAGS:
		return "All flags of the opponent are captured";
	case PLAYER2_WIN_FLAGS:
		return "All flags of the opponent are captured";
	case PLAYER1_WIN_MOVING_PIECES:
		return "All moving PIECEs of the opponent are eaten";
	case PLAYER2_WIN_MOVING_PIECES:
		return "All moving PIECEs of the opponent are eaten";
	case TIE:
		return "A tie - both Moves input files done without a winner";
	case TIE_NO_MOVING:
		return "A tie - all moving pieces are eaten";
	case TIE_NO_FLAGS:
		return "A tie - all flags are eaten by both players in the position files";
	case PLAYER1_LOSE_BAD_POS:
		return "Bad Positioning input file for player 1 - line "
				+ std::to_string(m_player1->getLineNum());
	case PLAYER2_LOSE_BAD_POS:
		return "Bad Positioning input file for player 2 - line "
				+ std::to_string(m_player2->getLineNum());
	case TIE_BAD_POS:
		return "Bad Positioning input file for both players - player 1: line "
				+ std::to_string(m_player1->getLineNum()) + ", player 2: line "
				+ std::to_string(m_player2->getLineNum());
	case PLAYER1_LOSE_BAD_MOVE:
		return "Bad Moves input file for player 1 - line "
				+ std::to_string(m_player1->getLineNum());
	case PLAYER2_LOSE_BAD_MOVE:
		return "Bad Moves input file for player 2 - line "
				+ std::to_string(m_player2->getLineNum());
	case OPEN_FAIL_FAILED:
		return "Fail to open file !!!";
	default:  // default handling - shouldn't get here
		return "This is default";
	}
	return NULL;
}

std::ostream& operator<<(std::ostream& os, const Game& a_game) {
	int winner = a_game.winnerNumByStatus();
	std::string reason = a_game.reasonByStatus();
	os << "Winner: " << winner << std::endl;
	os << "Reason: " << reason << std::endl;
	os << std::endl;
	std::vector<std::vector<BasicPiece*> >::const_iterator l_outer_it =
			a_game.m_piecesMatrix->begin();
	for (; l_outer_it != a_game.m_piecesMatrix->end(); ++l_outer_it) {
		std::vector<BasicPiece*>::const_iterator l_inner_it =
				(*l_outer_it).begin();
		for (; l_inner_it != (*l_outer_it).end(); ++l_inner_it) {
			os << (**l_inner_it);
		}
		if (!((l_outer_it != a_game.m_piecesMatrix->end()) && (next(l_outer_it) == a_game.m_piecesMatrix->end()))) {
			os << std::endl;
		}
	}
	return os;
}


bool Game::createOutputFileStream() {
	if (m_outFileStream) {
		return true;  // output stream is created
	}

	// output stream is null
	m_outFileStream = new std::ofstream(m_outFileName);
	if (!m_outFileStream || !m_outFileStream->good()) {
		return false;
	}
	return true; // created and status is good
}
