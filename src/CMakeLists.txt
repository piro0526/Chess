# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
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
    Interface.cpp
    StateChecker.cpp
    Action.cpp
    Interpreter.cpp
)
