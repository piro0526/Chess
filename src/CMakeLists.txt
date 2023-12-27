# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)
# プロジェクト名と使用する言語を設定
project(chess CXX)
# a.outという実行ファイルをmain.cppとhello.cppから作成
add_executable(
    main
    Board.cpp
    ChessGame.cpp
    GameStateCheck.cpp
    main.cpp
    Move.cpp
    MoveHandler.cpp
    MoveValidator.cpp
    Piece.cpp
    PieceFactory.cpp
    PieceMetadata.cpp
    Player.cpp
    StateChecker.cpp
)
