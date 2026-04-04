/**
 * ============================================================
 * TIC-TAC-TOE PROGRAMMING ASSIGNMENT
 * ============================================================
 *
 * This file contains the starter code for the Tic-Tac-Toe
 * programming assignment.
 *
 * The purpose of this starter code is to provide the basic
 * infrastructure and program architecture so that students
 * can focus on implementing the core game logic and AI.
 *
 * ------------------------------------------------------------
 * PROVIDED (GIVEN CODE)
 * ------------------------------------------------------------
 *
 * The following components are already implemented and
 * should NOT need modification:
 *
 *   ✔ GameLogger
 *       Logging system for debugging and program output
 *
 *   ✔ Command line argument parser
 *       Handles --judge, --input, --log options
 *
 *   ✔ Game configuration structures
 *       RunConfig, GameSetup, GameResult
 *
 *   ✔ Program architecture
 *       Interaction / Renderer / Engine / Logic / Bot modules
 *
 *   ✔ Game engine structure (skeleton)
 *       startGame(), playGame(), endGame()
 *
 * These parts define the overall program flow.
 *
 * ------------------------------------------------------------
 * REQUIRED IMPLEMENTATION (STUDENTS MUST COMPLETE)
 * ------------------------------------------------------------
 *
 * Students must implement the following core functions:
 *
 *   Game Interaction
 *       validateInput()
 *       getInput()
 *       selectSize()
 *       selectGoal()
 *       selectGameMode()
 *       selectBotLevel()
 *       getPlayerMove()
 *
 *   Game Renderer
 *       displayBoard()
 *       showMove()
 *       showInvalidMove()
 *       showPlayer()
 *       showResult()
 *       printResult()
 *
 *   Game Logic
 *       initBoard()
 *       isValidMove()
 *       makeMove()
 *       isEmptyHead()
 *       checkWin()
 *       checkDraw()
 *
 *   Bot Logic
 *       random_pick()   (EASY bot - REQUIRED)
 *
 *   Game Engine
 *       startGame()
 *       playGame()
 *       endGame()
 *
 * ------------------------------------------------------------
 * OPTIONAL / BONUS TASKS
 * ------------------------------------------------------------
 *
 * Students may optionally implement stronger bot strategies:
 *
 *   simple_heuristic()   (MEDIUM difficulty)
 *   hard_level()         (HARD difficulty)
 *
 * These are not required for a basic passing solution but
 * may receive additional credit depending on the assignment
 * grading policy.
 *
 * ------------------------------------------------------------
 * IMPORTANT
 * ------------------------------------------------------------
 *
 * • Do NOT remove the provided program structure.
 * • You may add helper functions if needed.
 * • You may modify implementation details as long as the
 *   overall program still compiles and runs correctly.
 *
 * Please read the full assignment specification (PDF)
 * before starting the implementation.
 *
 * ============================================================
 */

/* ----------------------------------------------------- */
/* -------------------- [IMPORTING] -------------------- */
/* ----------------------------------------------------- */
/**
 * ============================================================
 * STANDARD LIBRARY HEADERS
 * ============================================================
 *
 * This section includes C++ standard library headers used
 * throughout the starter code.
 *
 * Students are ALLOWED to:
 *   ✔ Add additional headers if needed
 *   ✔ Remove unused headers
 *   ✔ Replace headers with alternatives
 *
 * As long as the program compiles and works correctly.
 *
 * The headers below are provided to support common tasks
 * such as:
 *
 *   - input/output
 *   - random number generation
 *   - timing and benchmarking
 *   - string manipulation
 *   - file input/output
 *
 * Quick overview:
 *
 *   <iostream>   : console input/output
 *   <string>     : string handling
 *   <sstream>    : string stream processing
 *   <iomanip>    : formatted output
 *
 *   <random>     : random number generator (bot moves)
 *
 *   <chrono>     : timing utilities
 *   <thread>     : sleep/delay functions
 *
 *   <fstream>    : file input/output (logging / judge mode)
 *
 *   <functional> : function wrappers / lambdas
 *   <type_traits>: template utilities
 *
 *   <limits>     : numeric limits
 *   <utility>    : std::pair and helper utilities
 *
 *   <ctime>      : timestamp for logging
 *   <format>     : string formatting (C++20)
 *
 * IMPORTANT:
 *   Do NOT use external libraries.
 *   Only C++ standard library is allowed.
 *
 * ============================================================
 */

#include <chrono>
#include <ctime>
#include <format>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <type_traits>
#include <utility>

/* ------------------------------------------------------------ */
/* -------------------- [GLOBAL VARIABLES] -------------------- */
/* ------------------------------------------------------------ */
/**
 * ============================================================
 * GLOBAL CONFIGURATION (MUST READ)
 * ============================================================
 *
 * This section defines global constants, enums, and data
 * structures used throughout the program.
 *
 * Students should read this section carefully to understand
 * the configuration of the game.
 *
 * Most values here should NOT need to be modified.
 * However, you are allowed to adjust them if necessary
 * for experimentation or testing.
 *
 * Contents of this section:
 *
 *   1. Version information
 *   2. Global flags
 *   3. Game constants
 *   4. Random number generator
 *   5. Enumerations (game modes, bot levels, UI types)
 *   6. Data structures used by the game engine
 *
 * ============================================================
 */

// version
/**
 * Current version of the game program.
 * Used mainly for logging and debugging.
 *
 * TODO: Modify <STUDENT_ID> with your id.
 * Example: "0.4.2502xxxx"
 */
const std::string VERSION = "0.4.25022877";

// flag
/**
 * Global feature flags.
 *
 * ALGORITHM_FLAG
 *   Used to enable or disable advanced algorithms.
 *
 * TIME_ENABLED
 *   If true, execution time of certain functions
 *   will be logged (useful for performance testing).
 *
 * RANDOM_SEED
 *   Seed used for random number generation.
 *   Keeping the seed fixed ensures deterministic
 *   behavior for testing and debugging.
 */
const bool ALGORITHM_FLAG = true;
const bool TIME_ENABLED = true;

// Fixed seed ensures deterministic behavior during testing.
// Change the seed if you want different random games.
const int RANDOM_SEED = 2013;

// constants
/**
 * Game-related constants.
 *
 * BOARD_N_MAX
 *   Maximum allowed board size.
 *
 * SLEEP_TIME
 *   Delay (milliseconds) used for bot moves
 *   or UI animations.
 *
 */

// Maximum board dimension allowed by the program.
// Increasing this value may affect performance of bot algorithms.
const int BOARD_N_MAX = 12;
const int SLEEP_TIME = 1500;
const int TEST_GAME = 1;

/**
 * Global random number generator.
 *
 * Used by bot algorithms to generate random moves.
 *
 * std::mt19937 is a high-quality pseudo-random
 * number generator based on the Mersenne Twister algorithm.
 */
std::mt19937 generator(RANDOM_SEED);

/**
 * Bot difficulty levels.
 *
 * EASY
 *   Random move selection (required).
 *
 * MEDIUM
 *   Heuristic-based strategy (optional).
 *
 * HARD
 *   Advanced AI strategy (bonus challenge).
 *
 * INVALID_LV
 *   Used internally to represent invalid input.
 */
enum class BotLevel
{
    EASY,
    MEDIUM,
    HARD,
    INVALID_LV
};

/**
 * Game modes supported by the program.
 *
 * PVP
 *   Player vs Player
 *
 * PVE
 *   Player vs Bot
 *
 * EVE
 *   Bot vs Bot
 *
 * INVALID_MODE
 *   Used when user input is invalid.
 */
enum class GameMode
{
    PVP,
    PVE,
    EVE,
    INVALID_MODE
};

/**
 * UI menu types.
 *
 * Used by showSelectMenu() to determine which
 * menu should be displayed.
 *
 * Example:
 *
 *   showSelectMenu(SelectType::SIZE_UI);
 *
 * will display the board size selection menu.
 */
enum class SelectType
{
    TITLE_UI,
    SIZE_UI,
    GOAL_UI,
    END_RULE_UI,
    GAME_MODE_UI,
    BOT_LEVEL_UI,
    PLAYER_UI,
    MUL_BOT_LEVEL_UI,
    INVALID_UI
};

/**
 * End-point rule for detecting winning sequences.
 *
 * These rules are commonly used in Gomoku-style games
 * to determine whether a line is considered valid.
 *
 * NONE
 *   Ignore endpoint checking.
 *
 * OPEN_ONE
 *   At least one end of the sequence must be open.
 *
 * OPEN_TWO
 *   Both ends must be open.
 *
 * This rule can affect advanced bot evaluation.
 */
enum class EndRule
{
    NONE,
    OPEN_ONE,
    OPEN_TWO
};

/**
 * Alias for a board coordinate.
 *
 * pII stands for:
 *   pair<int, int>
 *
 * Representing:
 *
 *   (row, column)
 */
typedef std::pair<int, int> pII;

/**
 * Runtime configuration for the program.
 *
 * This struct stores options parsed from
 * command line arguments.
 *
 * interactive
 *   true  -> show UI and menus
 *   false -> run in automated mode
 *
 * judge_mode
 *   used for automated grading systems.
 *
 * input_file
 *   path to file used as stdin.
 *
 * to_file
 *   whether logs should be written to file.
 *
 * log_file
 *   path of the log file.
 */
struct RunConfig
{
    bool interactive = true;
    bool judge_mode = false;
    std::string input_file;

    bool to_file = true;
    std::string log_file = "log.txt";
};

/**
 * Stores configuration and current state of the game.
 *
 * board
 *   2D board storing symbols ('X', 'O', '-')
 *
 * size
 *   board dimension
 *
 * goal
 *   number of consecutive symbols required to win
 *
 * mode
 *   game mode (PVP / PVE / EVE)
 *
 * levels
 *   bot difficulty levels for players
 */
struct GameSetup
{
    char board[BOARD_N_MAX][BOARD_N_MAX];
    int size;
    int goal;
    GameMode mode;
    EndRule rule = EndRule::OPEN_TWO;
    BotLevel levels[2];
};

/**
 * Final result returned by the game engine.
 *
 * winner
 *   0  -> Player 1
 *   1  -> Player 2
 *   -1 -> Draw
 *
 * isBot
 *   true  -> winner is a bot
 *   false -> winner is a human
 *
 * turns
 *   total number of turns played.
 */
struct GameResult
{
    int winner;
    bool isBot;
    int turns;
};

constexpr int DRAW_RESULT = -1;

/* -------------------------------------------------------- */
/* -------------------- [DECLARATIONS] -------------------- */
/* -------------------------------------------------------- */
/**
 * ============================================================
 * FUNCTION DECLARATIONS (MUST READ)
 * ============================================================
 *
 * This section lists all function prototypes used in the program.
 *
 * The implementation of these functions appears later in the file.
 *
 * Functions are grouped by module:
 *
 *   1. GameLogger      → logging system
 *   2. RunConfig       → command line arguments
 *   3. GameInteraction → input handling
 *   4. GameRenderer    → console UI
 *   5. GameEngine      → main game flow
 *   6. GameLogic       → board rules
 *   7. BotLogic        → AI move generation
 *   8. Helper          → utility functions
 *
 * You do not need to modify most of these declarations.
 *
 * ============================================================
 */

// Game Logger
/**
 * Logging system used throughout the program.
 *
 * Supports multiple log levels and optional
 * logging to file.
 *
 * Students do NOT need to modify this module.
 */
namespace GameLogger
{
    // Logging Level
    /**
     * Severity level for log messages.
     */
    enum class Level
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        MSG,
    };

    /**
     * Convert logging level to printable string.
     */
    inline std::string levelToString(Level level)
    {
        switch (level)
        {
        case Level::DEBUG:
            return "DEBUG";
        case Level::INFO:
            return "INFO";
        case Level::WARNING:
            return "WARN";
        case Level::ERROR:
            return "ERROR";
        case Level::MSG:
            return "";
        default:
            return "UNKNOWN";
        }
    }
    inline static Level min_level = Level::DEBUG;

    // Level Color
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string CYAN = "\033[36m";

    /**
     * Return terminal color code corresponding to a log level.
     */
    inline std::string getColor(Level level)
    {
        switch (level)
        {
        case Level::DEBUG:
            return BLUE;
        case Level::INFO:
            return GREEN;
        case Level::WARNING:
            return YELLOW;
        case Level::ERROR:
            return RED;
        default:
            return RESET;
        }
    }

    // Static Variables
    inline static std::ofstream log_file;
    inline static bool write_to_file = false;
    inline static bool is_judge_mode = false;

    // Functions
    /**
     * Initialize logging system.
     */
    void init(bool judge_mode, bool to_file = true, const std::string &path = "log.txt");

    /**
     * Print a log message.
     */
    void log(const std::string &msg, Level level = Level::INFO);

    /**
     * Close log file (if used).
     */
    void close();
} // namespace GameLogger

// Run Config
/**
 * Parse command line arguments.
 */
RunConfig parseArgs(int argc, char *argv[]);

// Game Interaction
/**
 * This module handles all input-related operations of the game.
 *
 * Responsibilities:
 *
 *   1. Input redirection
 *      - Read from keyboard (interactive mode)
 *      - Read from file (judge / testing mode)
 *
 *   2. Input validation
 *      - Ensure numeric input is valid
 *      - Prevent program crashes from bad input
 *
 *   3. User selections
 *      - Board size
 *      - Win condition (goal)
 *      - Game mode
 *      - Bot difficulty
 *
 *   4. Player moves
 *      - Read move coordinates (row, col)
 *
 * Notes for students:
 *
 *   • Functions here should ONLY handle input parsing.
 *   • Game rules are checked later in GameLogic.
 *   • Invalid input should return false so the caller
 *     can ask the user again.
 *
 */
namespace GameInteraction
{
    static std::ifstream global_file_in;
}

std::streambuf *initInteraction(const RunConfig &config);
void closeInteraction(std::streambuf *cin_backup);
bool validateInput(std::string &input);
bool getInput(int *val);
bool selectSize(int *size);
bool selectGoal(int *goal, const int size);
bool selectEndRule(EndRule *rule);
bool selectGameMode(GameMode *mode);
bool selectBotLevel(BotLevel *levels, const int index);
bool getPlayerMove(int *row, int *col);

// Game Renderer
/**
 * Responsible for displaying all visual elements in the console.
 *
 * Includes:
 *
 *   • Clearing the screen
 *   • Displaying menus
 *   • Rendering the game board
 *   • Showing player actions
 *   • Showing final results
 *
 * This module does NOT contain game logic.
 * It only prints information to the console.
 *
 */

void clearScreen();
void showSelectMenu(SelectType selectType);
void displayBoard(const char board[][BOARD_N_MAX], const int size);
void showMove(const int row, const int col);
void showInvalidMove();
void showPlayer(const int player, const bool is_bot);
void showResult(const int winner, const bool is_bot);
void printResult(const GameResult &gameResult);

// Game Engine
/**
 * This module controls the overall flow of the game.
 *
 * Responsibilities:
 *
 *   1. Game setup
 *      - read configuration from user
 *      - initialize the board
 *
 *   2. Game loop
 *      - display board
 *      - determine current player
 *      - get move (human or bot)
 *      - apply move
 *      - check win / draw
 *      - switch player
 *
 *   3. Game termination
 *      - show final board
 *      - print result
 *
 * Important:
 *
 *   • The Engine manages WHEN things happen.
 *   • The actual rules of the game are implemented
 *     in the GameLogic module.
 *
 */

void startGame(const RunConfig &config, GameSetup &gameSetup);
GameResult playGame(const RunConfig &config, GameSetup &gameSetup);
void endGame(const RunConfig &config, GameSetup &gameSetup, GameResult &gameResult);

// Game Logic
/**
 * This module implements the rules of the game.
 *
 * Responsibilities:
 *
 *   • Board initialization
 *   • Move validation
 *   • Applying moves to the board
 *   • Checking win conditions
 *   • Detecting draw situations
 *
 * These functions operate directly on the board state.
 *
 * Important:
 *
 *   • GameLogic defines WHAT the rules are.
 *   • GameEngine decides WHEN these rules are checked.
 *
 * Students will mainly implement:
 *
 *   - initBoard()
 *   - isValidMove()
 *   - makeMove()
 *   - isEmptyHead()
 *   - checkWin()
 *   - checkDraw()
 *
 */

void initBoard(char board[][BOARD_N_MAX], const int size);
bool isValidMove(const char board[][BOARD_N_MAX], const int size, const int row, const int col);
void makeMove(char board[][BOARD_N_MAX], const int row, const int col, const char symbol);
bool isEmptyHead(char board[][BOARD_N_MAX], int size, int x, int y, const char symbol);
bool checkWin(char board[][BOARD_N_MAX], const int size, int i, int j, const char symbol, const int goal, EndRule rule = EndRule::OPEN_TWO);
bool checkDraw(char board[][BOARD_N_MAX], const int size);

// Bot Move Logic
/**
 * Generate the AI move for the current board state.
 *
 * This function dispatches to different strategies depending
 * on the selected difficulty level.
 *
 * The internal algorithms are intentionally modular so they can
 * be replaced or extended without affecting the rest of the engine.
 *
 * Developers are encouraged to experiment with their own AI logic
 * (pattern evaluation, Monte Carlo methods, minimax, etc.).
 *
 * @param board  Current board state
 * @param size   Board dimension (NxN)
 * @param goal   Number of consecutive symbols needed to win
 * @param symbol Bot symbol
 * @param level  Difficulty level
 *
 * @return Coordinate of the chosen move
 */
pII botMove(char board[][BOARD_N_MAX], const int size, const int goal, const EndRule rule, const char symbol, const BotLevel level);

// Level 1
/**
 * EASY difficulty.
 *
 * Selects a random valid move from the board.
 *
 * This mode exists mainly for testing and casual gameplay.
 *
 * @return Random empty cell
 */
pII random_pick(char board[][BOARD_N_MAX], const int size);

// Level 2
/**
 * MEDIUM difficulty.
 *
 * Uses a simple heuristic evaluation:
 * - try to win if possible
 * - block opponent winning moves
 * - otherwise choose a reasonable position
 *
 * This function is intentionally lightweight so the engine
 * remains fast even on large boards.
 *
 * @return Heuristically chosen move
 */
pII simple_heuristic(char board[][BOARD_N_MAX], const int size, const int goal, const EndRule rule, const char botSymbol, const char playerSymbol);

/*
 * NOTE FOR DEVELOPERS
 *
 * More advanced AI implementations can be added here if desired.
 *
 * Example approaches include:
 *
 * - Minimax with alpha-beta pruning
 * - Monte Carlo Tree Search (MCTS)
 * - Pattern scoring systems
 * - Hybrid evaluation + search
 *
 * The engine is designed so that new difficulty levels can be
 * implemented without modifying the rest of the game logic.
 */
pII hard_level(char board[][BOARD_N_MAX], const int size, const int goal, const EndRule rule, const char botSymbol, const char playerSymbol);

// Game Helper
/**
 * Utility helper functions used across modules.
 */

template <typename Function>
auto measureExecutionTime(const std::string &label, Function func, bool enabled)
    -> std::invoke_result_t<Function>;

/* ------------------------------------------------------- */
/* -------------------- [DEFINITIONS] -------------------- */
/* ------------------------------------------------------- */
/**
 * ============================================================
 * TODO LIST FOR STUDENTS
 * ============================================================
 *
 * Interaction:
 *   validateInput
 *   getInput
 *   selectSize
 *   selectGoal
 *   selectGameMode
 *   selectBotLevel
 *   getPlayerMove
 *
 * Renderer:
 *   displayBoard
 *   showMove
 *   showInvalidMove
 *   showPlayer
 *   showResult
 *   printResult
 *
 * Game Logic:
 *   initBoard
 *   isValidMove
 *   makeMove
 *   isEmptyHead
 *   checkWin
 *   checkDraw
 *
 * Bot:
 *   random_pick (required)
 *   simple_heuristic (optional)
 *   hard_level (bonus)
 *
 * Game Engine
 *   startGame
 *   playGame
 *   endGame
 *
 * ============================================================
 */

/**
 * ============================================================
 * LOGGER MODULE (GIVEN)
 * ============================================================
 *
 * This module provides a simple logging system used throughout
 * the program.
 *
 * Students DO NOT need to modify this module.
 *
 * Usage examples:
 *
 *   GameLogger::log("Game started");
 *   GameLogger::log("Invalid move", GameLogger::Level::WARNING);
 *
 * Log levels:
 *   DEBUG   : detailed information for debugging
 *   INFO    : normal program information
 *   WARNING : suspicious behaviour
 *   ERROR   : invalid input or unexpected error
 *
 * Logs are printed to console and optionally written to file.
 *
 * ============================================================
 */
void GameLogger::init(bool judge_mode, bool to_file, const std::string &path)
{
    write_to_file = to_file;
    is_judge_mode = judge_mode;

    if (write_to_file)
    {
        // not append
        // log_file.open(path, std::ios::out | std::ios::app);

        // write new log contents
        log_file.open(path, std::ios::out | std::ios::trunc);
        if (!log_file.is_open())
        {
            std::cerr << "[Logger] Cannot open log file: " << path
                      << ". Falling back to console only." << std::endl;
            write_to_file = false; // fallback
        }
    }

    std::string header = "Tic-tac-toe Game (Version: " + std::string(VERSION) + ")\n";
    header += std::string(48, '-');

    if (write_to_file)
    {
        log_file << header << std::endl;
    }

    if (!is_judge_mode)
    {
        std::cout << header << std::endl;
    }
}

void GameLogger::log(const std::string &msg, Level level)
{
    // Only log if current level is important as or more than min_level
    if (static_cast<int>(level) < static_cast<int>(min_level))
    {
        return;
    }

    auto now = std::time(nullptr);

    // NOTE: std::localtime is not thread-safe but acceptable here
    // since the program is single-threaded.
    auto tm = *std::localtime(&now);

    // format: '[Level] - [YYYY-MM-DD HH:MM:SS] Message'
    std::stringstream ss_lv;
    std::string formatted_lv;
    if (level != Level::MSG)
    {
        ss_lv << "[" << levelToString(level) << "]";
        formatted_lv = ss_lv.str();
    }

    std::stringstream ss_msg;
    ss_msg << (formatted_lv.empty() ? "" : " - ")
           << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] ";
    ss_msg << msg;
    std::string formatted_msg = ss_msg.str();

    // to output stream
    if (write_to_file)
    {
        log_file << formatted_lv << formatted_msg << std::endl;
        log_file.flush();
    }

    if (!is_judge_mode)
    {
        std::cout << getColor(level) << formatted_lv;
        std::cout << getColor(Level::MSG) << formatted_msg << RESET << std::endl;
    }
}

void GameLogger::close()
{
    if (log_file.is_open())
    {
        log_file.close();
    }
}

/**
 * ============================================================
 * ARGUMENT PARSER (GIVEN)
 * ============================================================
 *
 * Parse command line arguments for the program.
 *
 * Supported arguments:
 *
 *   --judge, -j
 *       Enable judge mode (no UI, output minimal result)
 *
 *   --input <file>
 *       Read input from file instead of keyboard
 *
 *   --log <file>
 *       Write log output to file
 *
 * Students DO NOT need to modify this function.
 *
 * ============================================================
 */
RunConfig parseArgs(int argc, char *argv[])
{
    RunConfig config;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "-j" || arg == "--judge")
        {
            config.judge_mode = true;
            // auto turn off interactive
            config.interactive = false;
        }
        else if ((arg == "-i" || arg == "--input") && i + 1 < argc)
        {
            config.input_file = argv[++i];
        }
        else if ((arg == "-l" || arg == "--log") && i + 1 < argc)
        {
            config.log_file = argv[++i];
            if (config.log_file == "")
            {
                config.to_file = false;
            }
        }
        else if (arg == "-h" || arg == "--help")
        {
            std::cout << "Tic-tac-toe Game (Version: " << VERSION << " by baluong.87)\n";
            std::cout << "Usage: \n"
                      << "\t" << "--judge, -j" << "\t" << "Enable judge mode (no UI, standard output only)\n"
                      << "\t" << "--input, -i" << "\t" << "Path to input file\n"
                      << "\t" << "--log, -l" << "\t" << "Path to log file (default: log.txt)\n";
            exit(0);
        }
    }

    return config;
}

/* ---------- Game Interaction ---------- */
/**
 * ============================================================
 * INTERACTION MODULE (STUDENT IMPLEMENTATION)
 * ============================================================
 *
 * This module handles all user input operations of the game.
 *
 * Responsibilities:
 *
 *   • Reading input from the console or redirected input file
 *   • Parsing numeric values
 *   • Validating input format
 *   • Handling menu selections
 *   • Reading player moves
 *
 * Important design rule:
 *
 *   The Interaction module ONLY deals with input handling.
 *   It should NOT implement game rules or game logic.
 *
 * Game rule validation such as:
 *
 *   - checking if a move is inside the board
 *   - checking if a cell is empty
 *   - checking win or draw conditions
 *
 * must be handled in the GameLogic module instead.
 *
 * If invalid input is detected:
 *   • the function should return false
 *   • the caller (usually the GameEngine) will ask again
 *
 * Students are responsible for implementing the input
 * parsing and validation functions below.
 *
 * ============================================================
 */

// Given
std::streambuf *initInteraction(const RunConfig &config)
{
    std::streambuf *cin_backup = nullptr;

    if (!config.interactive && !config.input_file.empty())
    {
        GameInteraction::global_file_in.open(config.input_file);
        if (GameInteraction::global_file_in.is_open())
        {
            cin_backup = std::cin.rdbuf();
            std::cin.rdbuf(GameInteraction::global_file_in.rdbuf());

            GameLogger::log("redirected cin to: " + config.input_file);
        }
        else
        {
            GameLogger::log("failed to open input file, using console.", GameLogger::Level::ERROR);
        }
    }
    return cin_backup;
}

// Given
void closeInteraction(std::streambuf *cin_backup)
{
    if (cin_backup)
    {
        std::cin.rdbuf(cin_backup);
        GameLogger::log("fallback using 'std::cin' input stream.");
    }

    if (GameInteraction::global_file_in.is_open())
    {
        GameInteraction::global_file_in.close();
    }
}

/**
 * Validate raw input string.
 *
 * Purpose:
 *   Ensure the input contains only numeric characters
 *   and can be safely converted to an integer.
 *
 * Example:
 *   "12"  -> valid
 *   "3a"  -> invalid
 *   ""    -> invalid
 *
 * Parameters:
 *   input : raw string read from std::cin
 *
 * Return:
 *   true  -> valid numeric input
 *   false -> invalid input
 *
 * Hint:
 *   - Check each character using std::isdigit()
 *   - Only digits 0-9 are allowed.
 *   - Negative numbers are not accepted.
 */
bool validateInput(std::string &input)
{
    if (input.empty())
    {
        return false;
    }

    int dem = 0, chk = 1;
    for (char c : input)
    {
        if (c != ' ' && !std::isdigit(c))
        {
            return false;
        }

        if (std::isdigit(c) && chk)
        {
            dem++;
            chk = 0;
        }
        else if (c == ' ')
        {
            chk = 1;
        }
    }

    if (dem != 1)
    {
        return false;
    }

    return true;
}

bool getInput(int *val)
{

    std::string line;
    std::getline(std::cin, line);

    if (!validateInput(line))
    {
        return false;
    }

    int parsed = 0;
    for (char c : line)
    {
        if (parsed > 1000000000)
        {
            return false;
        }
        if (std::isdigit(c))
        {
            parsed = parsed * 10 + (c - '0');
        }
    }
    *val = parsed;

    return true;
}

bool selectSize(int *size)
{
    int value;
    if (!getInput(&value))
    {
        return false;
    }

    if (value < 3 || value > BOARD_N_MAX)
    {
        return false;
    }

    *size = value;
    return true;
}

bool selectGoal(int *goal, const int size)
{
    int value;
    if (!getInput(&value))
    {
        return false;
    }

    if (value < 3 || value > size)
    {
        return false;
    }

    *goal = value;
    return true;
}

bool selectEndRule(EndRule *rule)
{
    int value;
    if (!getInput(&value))
    {
        return false;
    }

    switch (value)
    {
    case 1:
        *rule = EndRule::NONE;
        return true;
    case 2:
        *rule = EndRule::OPEN_ONE;
        return true;
    case 3:
        *rule = EndRule::OPEN_TWO;
        return true;
    default:
        return false;
    }
}

bool selectGameMode(GameMode *mode)
{
    int value;
    if (!getInput(&value))
    {
        return false;
    }

    switch (value)
    {
    case 1:
        *mode = GameMode::PVP;
        return true;
    case 2:
        *mode = GameMode::PVE;
        return true;
    case 3:
        *mode = GameMode::EVE;
        return true;
    default:
        return false;
    }
}

bool selectBotLevel(BotLevel *levels, const int index)
{
    int value;
    if (!getInput(&value))
    {
        return false;
    }

    switch (value)
    {
    case 1:
        levels[index] = BotLevel::EASY;
        return true;
    case 2:
        levels[index] = BotLevel::MEDIUM;
        return true;
    case 3:
        levels[index] = BotLevel::HARD;
        return true;
    default:
        return false;
    }
}

bool getPlayerMove(int *row, int *col)
{
    std::string line;
    if (!std::getline(std::cin, line))
    {
        return false;
    }

    std::stringstream ss(line);
    int r, c;
    if (!(ss >> r >> c))
    {
        return false;
    }

    *row = r;
    *col = c;
    return true;
}

/* ---------- Game Renderer ---------- */
/**
 * ============================================================
 * RENDERER MODULE (STUDENT IMPLEMENTATION)
 * ============================================================
 *
 * This module is responsible for displaying information
 * to the console.
 *
 * It includes:
 *
 *   • Clearing the screen
 *   • Rendering the game board
 *   • Showing player actions
 *   • Displaying error messages
 *   • Showing the final result
 *
 * Important design rule:
 *
 *   The Renderer should ONLY print output.
 *   It must NOT implement any game logic.
 *
 * Game rules such as:
 *   - validating moves
 *   - checking win conditions
 *   - detecting draws
 *
 * are handled in the GameLogic module.
 *
 * Students need to implement the rendering functions below
 * to produce a clear and readable console interface.
 *
 * ============================================================
 */

/**
 * Clear the console screen. (Given)
 *
 * This function uses ANSI escape sequences to clear
 * the terminal and move the cursor to the top-left.
 *
 * It works on most Unix-like terminals and modern
 * Windows terminals.
 *
 * If the terminal does not support ANSI escape codes,
 * the game will still run but the screen may not clear.
 */
void clearScreen()
{
    std::cout << "\n"
              << "\x1B[2J\x1B[H"
              << "\n";
    return;
}

/**
 * Display a selection menu depending on the UI type.
 *
 * This function prints different menus used during
 * the game setup and interaction phase.
 *
 * Parameters:
 *
 *   selectType : type of menu to display
 *
 * Possible menu types:
 *
 *   TITLE_UI           -> show game title
 *   SIZE_UI            -> ask for board size
 *   GOAL_UI            -> ask for win goal
 *   GAME_MODE_UI       -> select PvP / PvE / EvE
 *   BOT_LEVEL_UI       -> select bot difficulty
 *   PLAYER_UI          -> ask player move input
 *   MUL_BOT_LEVEL_UI   -> select bot levels for EvE
 */
void showSelectMenu(SelectType selectType)
{
    switch (selectType)
    {
    case SelectType::TITLE_UI:
        std::cout << ">----- Tic-tac-toe [Console v" << VERSION << "] -----<\n\n";
        break;

    case SelectType::SIZE_UI:
        std::cout << "Select board size (NxN, 3 <= N <= " << BOARD_N_MAX << "): ";
        break;

    case SelectType::GOAL_UI:
        std::cout << "Select goal (consecutive symbols to win): ";
        break;

    case SelectType::END_RULE_UI:
        std::cout << "Select end-rule: (1) None | (2) One end | (3) Two ends : ";
        break;

    case SelectType::GAME_MODE_UI:
        std::cout << "Select mode: (1) PvP | (2) PvE | (3) EvE : ";
        break;

    case SelectType::BOT_LEVEL_UI:
        std::cout << "Select bot level: (1) EASY | (2) MEDIUM | (3) HARD : ";
        break;

    case SelectType::PLAYER_UI:
        std::cout << "Enter move (row col): ";
        break;

    case SelectType::MUL_BOT_LEVEL_UI:
        std::cout << "Select bot levels for both bots. First bot then second bot.\n";
        break;

    default:
        break;
    }

    return;
}

void displayBoard(const char board[][BOARD_N_MAX], const int size)
{
    std::cout << "    ";
    for (int j = 0; j < size; ++j)
    {
        std::cout << j << " ";
    }
    std::cout << "\n";

    std::cout << "   ";
    for (int j = 0; j < size; ++j)
    {
        std::cout << "--";
    }
    std::cout << "-\n";

    for (int i = 0; i < size; ++i)
    {
        if (i > 9)
        {
            std::cout << i << " |";
        }
        else
        {
            std::cout << " " << i << " |";
        }
        for (int j = 0; j < size; ++j)
        {
            std::cout << board[i][j];
            if (j < size - 1)
                std::cout << " ";
        }
        std::cout << "\n";
    }
}

/**
 * Display which player is taking the turn.
 *
 * Parameters:
 *
 *   player  : player number (1 or 2)
 *   is_bot  : true if the player is controlled by the bot
 *
 * Example output:
 *
 *   Player 1's turn
 *   Bot (Player 2) is thinking...
 */
void showPlayer(int player, bool is_bot)
{
    if (is_bot)
    {
        std::cout << "Bot (Player " << player << ") is thinking...\n";
    }
    else
    {
        std::cout << "Player " << player << "'s turn.\n";
    }
}

void showMove(const int row, const int col)
{
    std::cout << "Move placed at (" << row << ", " << col << ")\n";
}

void showInvalidMove()
{
    std::cout << "Invalid move. Try again.\n";
}

void showResult(const int winner, const bool is_bot)
{
    if (winner == DRAW_RESULT)
    {
        std::cout << "It's a draw!\n";
        return;
    }

    if (is_bot)
    {
        std::cout << "Bot (Player " << winner << ") wins!\n";
    }
    else
    {
        std::cout << "Player " << winner << " wins!\n";
    }
}

void printResult(const GameResult &gameResult)
{
    int winner = gameResult.winner;
    if (gameResult.winner != DRAW_RESULT)
    {
        winner -= 1;
    }
    std::cout << winner << " " << gameResult.turns << '\n';
}

/* ---------- Game Engine ---------- */
/**
 * ============================================================
 * GAME ENGINE MODULE (STUDENT IMPLEMENTATION)
 * ============================================================
 *
 * This module controls the overall flow of the game.
 *
 * Responsibilities:
 *
 *   • Setting up the game configuration
 *   • Running the main game loop
 *   • Coordinating Interaction, Renderer, Logic, and Bot modules
 *   • Producing the final GameResult
 *
 * Important design rule:
 *
 *   The GameEngine decides WHEN actions happen,
 *   but it does NOT implement the game rules itself.
 *
 * Game rules such as:
 *   - move validation
 *   - win detection
 *   - draw detection
 *
 * are handled by the GameLogic module.
 *
 * Students must implement the skeleton functions below
 * to connect all modules together.
 *
 * ============================================================
 */

void startGame(const RunConfig &config, GameSetup &gameSetup)
{
    if (config.interactive)
    {
        clearScreen();
        showSelectMenu(SelectType::TITLE_UI);
    }

    if (config.interactive)
        showSelectMenu(SelectType::SIZE_UI);

    while (!selectSize(&gameSetup.size))
    {
        if (config.interactive)
        {
            std::cout << "Invalid size. Please try again.\n";
        }
    }

    if (config.interactive)
        showSelectMenu(SelectType::GOAL_UI);

    while (!selectGoal(&gameSetup.goal, gameSetup.size))
    {
        if (config.interactive)
        {
            std::cout << "Invalid goal. Please try again.\n";
        }
    }

    // if (config.interactive)
    //     showSelectMenu(SelectType::END_RULE_UI);

    // while (!selectEndRule(&gameSetup.rule))
    // {
    //     if (config.interactive)
    //     {
    //         std::cout << "Invalid end-rule. Please try again.\n";
    //     }
    // }

    if (config.interactive)
        showSelectMenu(SelectType::GAME_MODE_UI);

    while (!selectGameMode(&gameSetup.mode))
    {
        if (config.interactive)
        {
            std::cout << "Invalid mode. Please try again.\n";
        }
    }

    gameSetup.levels[0] = BotLevel::INVALID_LV;
    gameSetup.levels[1] = BotLevel::INVALID_LV;

    if (gameSetup.mode == GameMode::PVE)
    {
        if (config.interactive)
            showSelectMenu(SelectType::BOT_LEVEL_UI);

        while (!selectBotLevel(gameSetup.levels, 1))
        {
            if (config.interactive)
            {
                std::cout << "Invalid bot level. Please try again.\n";
            }
        }
    }
    else if (gameSetup.mode == GameMode::EVE)
    {
        if (config.interactive)
            showSelectMenu(SelectType::MUL_BOT_LEVEL_UI);

        if (config.interactive)
            showSelectMenu(SelectType::BOT_LEVEL_UI);

        while (!selectBotLevel(gameSetup.levels, 0))
        {
            if (config.interactive)
            {
                std::cout << "Invalid bot level. Please try again.\n";
            }
        }

        if (config.interactive)
            showSelectMenu(SelectType::BOT_LEVEL_UI);

        while (!selectBotLevel(gameSetup.levels, 1))
        {
            if (config.interactive)
            {
                std::cout << "Invalid bot level. Please try again.\n";
            }
        }
    }

    initBoard(gameSetup.board, gameSetup.size);
}

/**
 * Core game loop.
 *
 * Responsibilities:
 *
 *   1. Initialize game variables
 *      - current player
 *      - symbol mapping
 *      - turn counter
 *
 *   2. Repeat until game ends:
 *
 *        a) Display board
 *
 *        b) Determine current player type
 *           - human
 *           - bot
 *
 *        c) Get move
 *           - getPlayerMove() or botMove()
 *           - using measureExecutionTime()
 *
 *        d) Validate move
 *
 *        e) Apply move using makeMove()
 *
 *        f) Check win condition
 *           checkWin(...)
 *
 *        g) Check draw condition
 *           checkDraw(...)
 *
 *        h) Switch player
 *
 *   3. Return GameResult
 *
 * Return:
 *   GameResult structure containing:
 *      - winner
 *      - number of turns
 *      - whether winner is bot
 */

long long move_score[BOARD_N_MAX + 3][3][3];

void init_score_value(int goal)
{
    for (int i = 0; i <= goal; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                if (j == 0 || i < 2)
                    move_score[i][j][k] = 0;
                else
                    move_score[i][j][k] = 10 + i + j;
            }
        }
    }

    // none
    move_score[goal][2][0] = pow(10, 5);
    move_score[goal][1][0] = pow(10, 5);
    move_score[goal][0][0] = pow(10, 5);
    move_score[goal - 1][2][0] = pow(10, 4);
    move_score[goal - 1][1][0] = pow(10, 3);
    if (goal > 3)
        move_score[goal - 2][2][0] = pow(10, 2);

    // one end
    move_score[goal][2][1] = pow(10, 5);
    move_score[goal][1][1] = pow(10, 5);
    move_score[goal - 1][2][1] = pow(10, 4);
    move_score[goal - 1][1][1] = pow(10, 3);
    if (goal > 3)
        move_score[goal - 2][2][1] = pow(10, 2);

    // two end
    move_score[goal][2][2] = pow(10, 5);
    move_score[goal][1][2] = pow(10, 3);
    move_score[goal - 1][2][2] = pow(10, 3);
}

GameResult playGame(const RunConfig &config, GameSetup &gameSetup)
{
    GameResult result;
    int currentPlayer = 0;
    char symbols[2] = {'X', 'O'};
    int turns = 0;

    init_score_value(gameSetup.goal);

    while (true)
    {
        if (config.interactive)
        {
            clearScreen();
            displayBoard(gameSetup.board, gameSetup.size);
        }

        bool isBot = (gameSetup.mode == GameMode::EVE) ||
                     (gameSetup.mode == GameMode::PVE && currentPlayer == 1);

        if (config.interactive)
            showPlayer(currentPlayer + 1, isBot);

        int row = -1;
        int col = -1;

        if (isBot)
        {
            pII point = measureExecutionTime(
                "botMove",
                [&]()
                {
                    return botMove(gameSetup.board,
                                   gameSetup.size,
                                   gameSetup.goal,
                                   gameSetup.rule,
                                   symbols[currentPlayer],
                                   gameSetup.levels[currentPlayer]);
                },
                TIME_ENABLED);

            row = point.first;
            col = point.second;
        }
        else
        {
            bool moveParsed = false;
            while (!moveParsed)
            {
                if (config.interactive)
                    showSelectMenu(SelectType::PLAYER_UI);

                if (!getPlayerMove(&row, &col))
                {
                    if (config.interactive)
                        showInvalidMove();
                    continue;
                }

                if (!isValidMove(gameSetup.board, gameSetup.size, row, col))
                {
                    if (config.interactive)
                        showInvalidMove();
                    continue;
                }

                moveParsed = true;
            }
        }

        makeMove(gameSetup.board, row, col, symbols[currentPlayer]);
        if (config.interactive)
            showMove(row, col);

        turns++;

        if (checkWin(gameSetup.board, gameSetup.size, row, col, symbols[currentPlayer], gameSetup.goal, gameSetup.rule))
        {
            result.winner = currentPlayer + 1;
            result.turns = turns;
            result.isBot = isBot;
            return result;
        }

        if (checkDraw(gameSetup.board, gameSetup.size))
        {
            result.winner = DRAW_RESULT;
            result.turns = turns;
            result.isBot = false;
            return result;
        }

        currentPlayer = 1 - currentPlayer;
    }

    return result;
}

void endGame(const RunConfig &config, GameSetup &gameSetup, GameResult &gameResult)
{
    if (config.interactive)
    {
        clearScreen();
        displayBoard(gameSetup.board, gameSetup.size);
        showResult(gameResult.winner, gameResult.isBot);
    }
    else
    {
        printResult(gameResult);
    }

    std::stringstream ss;
    ss << "Game ended: winner=" << gameResult.winner
       << ", turns=" << gameResult.turns
       << ", isBot=" << (gameResult.isBot ? "true" : "false");
    GameLogger::log(ss.str());
}

/* ---------- Game Logic ---------- */
/**
 * ============================================================
 * GAME LOGIC MODULE (STUDENT IMPLEMENTATION)
 * ============================================================
 *
 * This module implements the core rules of the game.
 *
 * Responsibilities:
 *
 *   • Validating player moves
 *   • Updating the game board
 *   • Checking win conditions
 *   • Detecting draw situations
 *   • Determining the current game state
 *
 * Important design rule:
 *
 *   The Logic module defines HOW the game rules work,
 *   but it does NOT control when actions happen.
 *
 * For example:
 *
 *   - GameEngine decides whose turn it is
 *   - Renderer prints the board
 *   - Interaction collects player input
 *   - Bot decides AI moves
 *
 * The Logic module only processes the board state
 * and determines whether moves are valid or if the
 * game has been won or drawn.
 *
 * Typical functions in this module include:
 *
 *   - checking if a move is valid
 *   - placing a move on the board
 *   - scanning the board for winning sequences
 *   - determining if the board is full
 *
 * Students must implement the skeleton functions
 * below to correctly enforce the rules of the game.
 *
 * ============================================================
 */

/**
 * Initialize board cells.
 *
 * All cells should be set to '-'
 * representing an empty cell.
 *
 * Example for size = 3:
 *
 *   - - -
 *   - - -
 *   - - -
 *
 * Hint:
 *   Use nested loops.
 */
void initBoard(char board[][BOARD_N_MAX], const int size)
{
    // TODO: initialize board
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            board[i][j] = '-';
        }
    }
}

bool isValidMove(const char board[][BOARD_N_MAX], const int size, const int row, const int col)
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return false;
    }
    return board[row][col] == '-';
}

void makeMove(char board[][BOARD_N_MAX], const int row, const int col, const char symbol)
{
    board[row][col] = symbol;
}

bool isEmptyHead(char board[][BOARD_N_MAX], int size, int x, int y, const char symbol)
{
    if (x < 0 || x >= size || y < 0 || y >= size)
    {
        return true;
    }
    
    if (board[x][y] == '-' || board[x][y] == symbol)
    {
        return true;
    }
    return false;
}

/**
 * TODO:
 * Determine whether a player wins the game.
 *
 * A player wins if there are 'goal' consecutive symbols
 * in one of the following directions:
 *
 *   → horizontal
 *   ↓ vertical
 *   ↘ main diagonal
 *   ↙ anti diagonal
 *
 * Example (goal = 3):
 *
 *   X X X   -> win
 *
 * Parameters:
 *   board  : current board
 *   size   : board size
 *   symbol : player symbol ('X' or 'O')
 *   goal   : number of consecutive symbols required
 *   rule   : endpoint rule for advanced variants
 *
 * Return:
 *   true  -> player wins
 *   false -> no win detected
 */
bool checkWin(char board[][BOARD_N_MAX], const int size, int i, int j, const char symbol, const int goal, EndRule rule)
{
    const int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

    for (int d = 0; d < 4; ++d)
    {
        int dx = directions[d][0];
        int dy = directions[d][1];
        int count = 1, le = 1, ri = 1;

        for (int k = 1; k < goal; ++k)
        {
            int nx = i + dx * k;
            int ny = j + dy * k;
            if (nx < 0 || nx >= size || ny < 0 || ny >= size || board[nx][ny] != symbol)
            {
                break;
            }
            count++;
            ri++;
        }

        for (int k = 1; k < goal; ++k)
        {
            int nx = i - dx * k;
            int ny = j - dy * k;
            if (nx < 0 || nx >= size || ny < 0 || ny >= size || board[nx][ny] != symbol)
            {
                break;
            }
            count++;
            le++;
        }

        if (count < goal)
            continue;

        if (rule == EndRule::NONE)
        {
            return true;
        }

        int block = 2;
        if(isEmptyHead(board, size, i - dx * le, j - dy * le, symbol)) block--;
        if(isEmptyHead(board, size, i + dx * ri, j + dy * ri, symbol)) block--;

        block -= (count - goal);

        if (rule == EndRule::OPEN_ONE && block <= 1)
        {
            return true;
        }
        if (rule == EndRule::OPEN_TWO && block <= 0)
        {
            return true;
        }
    }

    return false;
}

bool checkDraw(char board[][BOARD_N_MAX], const int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (board[i][j] == '-')
            {
                return false;
            }
        }
    }
    return true;
}

/* ---------- Bot Move Logic ---------- */
/**
 * ============================================================
 * BOT MOVE LOGIC (STUDENT IMPLEMENTATION)
 * ============================================================
 *
 * Students are required to implement bot strategies for different levels.
 *
 * EASY:
 *   - Required.
 *   - Implement a simple random move selection.
 *
 * MEDIUM:
 *   - Optional but recommended.
 *   - Suggested idea: heuristic evaluation.
 *
 * HARD:
 *   - Bonus challenge.
 *   - No restriction on algorithm.
 *   - You may design your own search / evaluation strategy.
 *
 * ============================================================
 */

pII botMove(char board[][BOARD_N_MAX],
            const int size,
            const int goal,
            const EndRule rule,
            const char symbol,
            const BotLevel level)
{
    char opponent = (symbol == 'X') ? 'O' : 'X';

    switch (level)
    {
    case BotLevel::EASY:
        // REQUIRED
        return random_pick(board, size);

    case BotLevel::MEDIUM:
        // OPTIONAL
        // Suggestion:
        // - try winning move
        // - block opponent winning move
        // - otherwise choose a heuristic position

        return simple_heuristic(board, size, goal, rule, symbol, opponent);

    case BotLevel::HARD:
        // BONUS
        // Design your own strategy.
        // Possible approaches:
        //   - search algorithm
        //   - evaluation function
        //   - pattern detection

        return hard_level(board, size, goal, rule, symbol, opponent);

    default:
        return random_pick(board, size);
    }
}

// Level 1
/* ---------- EASY BOT ---------- */
/**
 * TODO (Required)
 *
 * Implement a random move generator.
 *
 * Idea:
 *   1. Scan the board
 *   2. Collect all empty cells
 *   3. Randomly choose one
 *
 * Hint:
 *   board[i][j] == '-' means empty cell
 */

pII random_pick(char board[][BOARD_N_MAX], const int size)
{
    std::vector<pII> emptyCells;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (board[i][j] == '-')
            {
                emptyCells.push_back(std::make_pair(i, j));
            }
        }
    }

    if (emptyCells.empty())
    {
        return std::make_pair(-1, -1);
    }

    std::uniform_int_distribution<int> dist(0, static_cast<int>(emptyCells.size()) - 1);
    int idx = dist(generator);
    return emptyCells[idx];
}

// Level 2
/* ---------- MEDIUM BOT ---------- */
/**
 * TODO (Optional)
 *
 * Implement a heuristic bot.
 *
 * Suggested strategy:
 *
 *   1. If bot has a winning move → play it
 *   2. If opponent has a winning move → block it
 *   3. Otherwise choose a good position
 *
 * Possible heuristics:
 *   - prefer center
 *   - prefer cells near existing pieces
 *   - extend current lines
 */

double cal_score(char board[][BOARD_N_MAX], int size, int x, int y, int dx, int dy, char symbol, int goal, EndRule rule)
{
    int count = 1;
    int block = 0;

    int step = 1;
    while (true)
    {
        int nx = x + dx * step;
        int ny = y + dy * step;

        if (nx < 0 || nx >= size || ny < 0 || ny >= size)
        {
            break;
        }

        if (board[nx][ny] == symbol)
        {
            count++;
            step++;
        }
        else if (board[nx][ny] != '-')
        {
            block++;
            break;
        }
        else
        {
            break;
        }
    }

    step = 1;
    while (true)
    {
        int nx = x - dx * step;
        int ny = y - dy * step;

        if (nx < 0 || nx >= size || ny < 0 || ny >= size)
        {
            break;
        }

        if (board[nx][ny] == symbol)
        {
            count++;
            step++;
        }
        else if (board[nx][ny] != '-')
        {
            block++;
            break;
        }
        else
        {
            break;
        }
    }

    if (count > goal)
    {
        block -= (count - goal);
        count = goal;
    }

    int rule_index = 0;
    if (rule == EndRule::OPEN_ONE)
    {
        rule_index = 1;
    }
    else if (rule == EndRule::OPEN_TWO)
    {
        rule_index = 2;
    }

    double result = move_score[count][2 - block][rule_index] * 1.0;
    if (dx + dy != 1 && count > 1)
    {
        result += 0.1;
    }
    return result;
}

const int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

void update_max_score(double &max_score, pII &best_move, char &pre_char, double score, int x, int y, char current_char, char botSymbol)
{
    std::string max_score_str = std::to_string((int)max_score);
    std::string score_str = std::to_string((int)score);

    if (max_score == -1 || pre_char == current_char || max_score_str.length() != score_str.length())
    {
        if (score > max_score)
        {
            max_score = score;
            best_move = std::make_pair(x, y);
            pre_char = current_char;
        }
    }
    else
    {
        if (current_char == botSymbol)
        {
            max_score = score;
            best_move = std::make_pair(x, y);
            pre_char = current_char;
        }
    }
}

pII find_best_move(char board[][BOARD_N_MAX],
                   const int size,
                   const int goal,
                   const EndRule rule,
                   const char botSymbol,
                   const char playerSymbol)
{
    double max_score = -1;
    pII best_move = std::make_pair(-1, -1);
    char pre_char = '-';

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (board[i][j] != '-')
            {
                continue;
            }

            double bot_score = 0;
            for (int d = 0; d < 4; ++d)
            {
                int dx = directions[d][0];
                int dy = directions[d][1];
                bot_score += cal_score(board, size, i, j, dx, dy, botSymbol, goal, rule);
            }

            update_max_score(max_score, best_move, pre_char, bot_score, i, j, botSymbol, botSymbol);

            double player_score = 0;
            for (int d = 0; d < 4; ++d)
            {
                int dx = directions[d][0];
                int dy = directions[d][1];
                player_score += cal_score(board, size, i, j, dx, dy, playerSymbol, goal, rule);
            }

            update_max_score(max_score, best_move, pre_char, player_score, i, j, playerSymbol, botSymbol);
        }
    }

    return best_move;
}

pII simple_heuristic(char board[][BOARD_N_MAX],
                     const int size,
                     const int goal,
                     const EndRule rule,
                     const char botSymbol,
                     const char playerSymbol)
{

    int chk = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (board[i][j] != '-')
            {
                chk = 1;
                break;
            }
        }
    }

    if (chk == 0)
    {
        return std::make_pair(size / 2, size / 2);
    }

    return find_best_move(board, size, goal, rule, botSymbol, playerSymbol);
}

// Level 3
/* ---------- HARD BOT ---------- */
/**
 * BONUS CHALLENGE
 *
 * Design a stronger AI for the game.
 *
 * There is no restriction on the algorithm.
 *
 * Possible directions:
 *   - search algorithm
 *   - board evaluation
 *   - pattern recognition
 *
 * You may also combine multiple techniques.
 */

struct board_lim
{
    int min_x, min_y, max_x, max_y;
};

struct BMove
{
    int x, y;
    double score;
};

double evaluatePoint(char board[][BOARD_N_MAX], int size, int x, int y, char symbol, int goal, EndRule rule)
{
    double score = 0;

    for (int d = 0; d < 4; ++d)
    {
        int dx = directions[d][0];
        int dy = directions[d][1];
        score += cal_score(board, size, x, y, dx, dy, symbol, goal, rule);
    }

    return score;
}

board_lim update(board_lim lim, int x, int y, int size)
{
    lim.min_x = std::min(lim.min_x, std::max(0, x - 1));
    lim.min_y = std::min(lim.min_y, std::max(0, y - 1));
    lim.max_x = std::max(lim.max_x, std::min(size - 1, x + 1));
    lim.max_y = std::max(lim.max_y, std::min(size - 1, y + 1));
    return lim;
}

BMove minimax(char board[][BOARD_N_MAX],
              int size,
              board_lim lim,
              char botSymbol,
              char playerSymbol,
              int goal,
              EndRule rule,
              int depth,
              bool maximizingPlayer,
              double alpha,
              double beta,
              double score,
              int x, int y)
{

    if (depth == 0)
    {
        return {-1, -1, score};
    }
    else if ((x != -1) && (board[x][y] == botSymbol) && (checkWin(board, size, x, y, botSymbol, goal, rule)))
    {
        return {-1, -1, 1000000};
    }
    else if ((x != -1) && (board[x][y] == playerSymbol) && (checkWin(board, size, x, y, playerSymbol, goal, rule)))
    {
        return {-1, -1, -1000000};
    }
    else if (checkDraw(board, size))
    {
        return {-1, -1, 0};
    }

    BMove bestMove = {-1, -1, maximizingPlayer ? -1e9 : 1e9};

    for (int i = lim.min_x; i <= lim.max_x; ++i)
    {
        for (int j = lim.min_y; j <= lim.max_y; ++j)
        {
            if (board[i][j] == '-')
            {
                if (maximizingPlayer)
                {
                    board[i][j] = botSymbol;
                    double scorePoint = evaluatePoint(board, size, i, j, botSymbol, goal, rule);
                    board_lim nlim = update(lim, i, j, size);
                    BMove move = minimax(board, 
                                         size, 
                                         nlim, 
                                         botSymbol, 
                                         playerSymbol, 
                                         goal, 
                                         rule, 
                                         depth - 1, 
                                         false, 
                                         alpha, 
                                         beta, 
                                         score + scorePoint, 
                                         i, j);
                    board[i][j] = '-';
                    move.x = i;
                    move.y = j;
                    if (move.score > bestMove.score)
                    {
                        bestMove = move;
                    }
                    alpha = std::max(alpha, bestMove.score);
                    if (beta <= alpha)
                        goto done;
                }
                else
                {
                    board[i][j] = playerSymbol;
                    double scorePoint = evaluatePoint(board, size, i, j, playerSymbol, goal, rule);
                    board_lim nlim = update(lim, i, j, size);
                    BMove move = minimax(board, 
                                         size, 
                                         nlim, 
                                         botSymbol, 
                                         playerSymbol, 
                                         goal, 
                                         rule, 
                                         depth - 1, 
                                         true, 
                                         alpha, 
                                         beta, 
                                         score - scorePoint, 
                                         i, j);
                    board[i][j] = '-';
                    move.x = i;
                    move.y = j;
                    if (move.score < bestMove.score)
                    {
                        bestMove = move;
                    }
                    beta = std::min(beta, bestMove.score);
                    if (beta <= alpha)
                        goto done;
                }
            }
        }
    }

    done:;
    return bestMove;
}

pII hard_level(char board[][BOARD_N_MAX],
               const int size,
               const int goal,
               const EndRule rule,
               const char botSymbol,
               const char playerSymbol)
{
    // TODO: optional bonus implementation

    board_lim lim;
    lim.min_x = size;
    lim.min_y = size;
    lim.max_x = -1;
    lim.max_y = -1;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (board[i][j] != '-')
            {
                lim = update(lim, i, j, size);
            }
        }
    }

    if (lim.max_x == -1)
    {
        return std::make_pair(size / 2, size / 2);
    }
    BMove bestMove = minimax(board, 
                             size, 
                             lim, 
                             botSymbol, 
                             playerSymbol, 
                             goal, 
                             rule, 
                             4, 
                             true, 
                             -1e9, 
                             1e9, 
                             0, 
                             -1, -1);

    return {bestMove.x, bestMove.y};
}

/* ---------- Game Helper ---------- */
/**
 * ============================================================
 * HELPER FUNCTION (GIVEN)
 * ============================================================
 *
 * Measure execution time of a function.
 *
 * Example usage:
 *
 *   auto result = measureExecutionTime(
 *       "botMove",
 *       [&]() {
 *           return botMove(...);
 *       },
 *       true
 *   );
 *
 * If 'enabled = true', execution time will be printed to log.
 *
 * Students DO NOT need to modify this function.
 *
 * ============================================================
 */
template <typename Function>
auto measureExecutionTime(const std::string &label, Function func, bool enabled)
    -> std::invoke_result_t<Function>
{
    // Get Return Type
    using ReturnT = std::invoke_result_t<Function>;

    // Exercute func() and Meansure Runtime
    auto start = std::chrono::high_resolution_clock::now();

    if constexpr (std::is_void_v<ReturnT>)
    {
        func();
        auto end = std::chrono::high_resolution_clock::now();

        if (enabled)
        {
            std::chrono::duration<double> duration = end - start;
            std::stringstream msg;
            msg << "execution time of " << "[" << label << "()]" << " = " << duration.count() << "s";
            GameLogger::log(msg.str(), GameLogger::Level::DEBUG);
        }
        return;
    }
    else
    {
        ReturnT result = func();
        auto end = std::chrono::high_resolution_clock::now();

        if (enabled)
        {
            std::chrono::duration<double> duration = end - start;
            std::stringstream msg;
            msg << "execution time of " << "[" << label << "()]" << " = " << duration.count() << "s";
            GameLogger::log(msg.str(), GameLogger::Level::DEBUG);
        }

        return result;
    }
}

/* ----------------------------------------------------- */
/* -------------------- [MAIN GAME] -------------------- */
/* ----------------------------------------------------- */
/**
 * ============================================================
 * MAIN GAME (GIVEN)
 * ============================================================
 *
 * This section contains the main game flow and core control
 * logic of the application.
 *
 * Responsibilities of this section include:
 *
 *   - Initializing the game environment
 *   - Starting the main game loop
 *   - Coordinating interaction between:
 *         + Game Engine
 *         + Game Renderer
 *         + Game Interaction
 *   - Managing turn order (player / bot)
 *   - Determining game state (running, win, draw, exit)
 *
 * The main game loop repeatedly:
 *
 *   1. Render the current board
 *   2. Receive player interaction
 *   3. Update the game state
 *   4. Let the bot perform its move
 *   5. Check win/draw conditions
 *
 * This section acts as the central controller that connects
 * all major modules together.
 *
 * ============================================================
 */
int main(int argc, char *argv[])
{
    RunConfig config = parseArgs(argc, argv);

    GameLogger::init(config.judge_mode, true, config.log_file);
    GameLogger::log("GameLogger initialized!");

    std::streambuf *cin_backup = initInteraction(config);
    GameLogger::log("GameInteraction initialized!");

    GameSetup gameSetup;
    startGame(config, gameSetup);
    GameLogger::log("GameEngine initialized!");

    GameResult gameResult = playGame(config, gameSetup);
    GameLogger::log("GameEngine playing done!");

    endGame(config, gameSetup, gameResult);
    GameLogger::log("GameEngine show endgame done!");

    closeInteraction(cin_backup);
    GameLogger::log("GameInteraction closed!");

    GameLogger::log("GameLogger closing . . .");
    GameLogger::close();

    return 0;
}

/* -------------------- [COMPILE] -------------------- */
/**
 * OPTION 1: Using g++ (>= v15.2.0) installed via MSYS2 (MinGW64)
 *
 * Compile:
 *   g++ -std=c++20 game.cpp -o game.exe
 *
 * (optional) Enable warnings:
 *   g++ -std=c++20 -Wall -Wextra game.cpp -o game.exe
 *
 * (optional) Debug build:
 *   g++ -std=c++20 -Wall -Wextra -g game.cpp -o game.exe
 *
 * OPTION 2: Using "Run Build Task" in VS Code
 *
 * - Create tasks.json (compiler configuration)
 * - (optional) Enable IntelliSense (C++20 compatible):
 *   create c_cpp_properties.json
 *
 * Compile:
 *   Ctrl + Shift + B
 */