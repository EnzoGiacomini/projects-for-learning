# projects-for-learning

A personal sandbox of small programs written while learning new languages. Each
folder is a self-contained project — no shared build system, no dependencies to
install. Pick one, compile it, run it.

## 📁 Structure

```
.
├── C/
│   └── TicTacToe-Terminal/       Tic-Tac-Toe with a Minimax AI
├── C++/
│   ├── simple-calculator-cpp/    Four-operation calculator
│   └── morse-code-translator/    Bidirectional Morse translator
└── Java/
    ├── word-guesser-game/        Word guessing game
    ├── caesar-cipher/            Caesar cipher encryptor
    └── weather-converter/        Fahrenheit → Celsius GUI converter
```

One folder per language, one folder per project inside it. New languages get
their own top-level directory following the same pattern.

## 🗂️ Projects

### C — [Tic-Tac-Toe](C/TicTacToe-Terminal)

The largest project here. Terminal Tic-Tac-Toe split across modular translation
units, with local multiplayer and three AI difficulties — the hardest one runs a
full Minimax search and cannot be beaten. See its
[README](C/TicTacToe-Terminal/README.md) for the details.

```bash
gcc C/TicTacToe-Terminal/*.c -o tictactoe -lm && ./tictactoe
```

### C++ — [Simple Calculator](C++/simple-calculator-cpp)

Checkpoint project for the Codédex C++ course. Reads two integers and an
operator, dispatches to one of four functions, and guards against division by
zero.

```bash
g++ C++/simple-calculator-cpp/calculator.cpp -o calculator && ./calculator
```

### C++ — [Morse Code Translator](C++/morse-code-translator)

Translates in both directions using two `std::map`s built at startup. Letters are
separated by spaces, words by `/`.

```bash
g++ C++/morse-code-translator/morse-translator.cpp -o morse-translator && ./morse-translator
```

### Java — [Word Guesser](Java/word-guesser-game)

Guess the secret word in five attempts. First Java project in the repo.

```bash
javac -d out Java/word-guesser-game/WordGuesser.java && java -cp out WordGuesser
```

### Java — [Caesar Cipher](Java/caesar-cipher)

Encrypts text with a classic Caesar shift, wrapping letters within the
alphabet while leaving non-letter characters untouched.

```bash
javac -d out Java/caesar-cipher/CaesarCipher.java && java -cp out CaesarCipher
```

### Java — [Weather Converter](Java/weather-converter)

Small Swing GUI that converts a Fahrenheit input into Celsius.

```bash
javac -d out Java/weather-converter/WeatherConverter.java && java -cp out WeatherConverter
```

## 🛠️ Requirements

| Language | Toolchain           | Notes                                       |
|----------|---------------------|---------------------------------------------|
| C        | `gcc`               | Link with `-lm` for the math functions       |
| C++      | `g++`               | No flags needed                             |
| Java     | Any modern JDK      | Tested on JDK 26                            |

## 💡 Opening in IntelliJ IDEA

The `.idea/` folder is git-ignored, so each clone keeps its own local project
settings. When you open the repo or add a new Java project, right-click its
folder and pick **Mark Directory as → Sources Root** — without that, IntelliJ
won't show the ▶ run icon next to `main`.

Note that Java requires the file name to match its public class name exactly, so
hyphenated file names like `word-guesser.java` won't compile.

## 📌 Conventions

* Project folders use `kebab-case`; Java files use `PascalCase` to match the class.
* Compiled output goes to `out/` or a named binary, both git-ignored.
* Commit messages are prefixed with `feat:` when a project is added.
