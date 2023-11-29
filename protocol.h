#pragma once

enum class MessageType {
    CHOICE_REQUEST,  // 서버가 클라이언트에게 선택 요청
    CHOICE_RESPONSE, // 클라이언트가 서버에게 선택 응답
    GAME_RESULT,     // 게임 결과
    STATS_REQUEST,   // 서버에게 승률을 요청
    STATS_RESPONSE,  // 서버가 클라이언트에게 승률을 응답
    EXIT_REQUEST     // 클라이언트가 종료 요청
};

struct MessageHeader {
    MessageType messageType;
    size_t messageSize;
    // 추가적인 옵션
    int option;
};

enum class GameType {
    ROCK_PAPER_SCISSORS,
    MUK_CHI_PPA
};

struct GameData {
    GameType gameType;
    int attack;  // 0: 서버 승, 1: 클라이언트 승
    int win;     // 0: 묵찌빠 서버 승, 1: 묵찌빠 클라이언트 승
    float winRate;
    int statsRequest; // 0: 기본값, 1: 승률 요청
    int exitRequest;  // 0: 기본값, 1: 종료 요청
};
