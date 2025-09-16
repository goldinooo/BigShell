# Minishell - 42 Project

A lightweight shell implementation that mimics bash behavior with parsing, execution, and built-in commands.

## Project Structure

```
BigShell/
├── Makefile                    # Build system with organized compilation
├── includes/
│   └── minishell.h            # Main header with all structures and prototypes
├── src/
│   ├── main.c                 # Entry point and initialization
│   ├── shell_loop.c           # Main REPL (Read-Eval-Print Loop)
│   ├── parsing/               # Input processing and AST generation
│   │   ├── lexer.c           # Tokenization (input → tokens)
│   │   ├── lexer_utils.c     # Token creation helpers
│   │   ├── parser.c          # AST construction (tokens → tree)
│   │   ├── command_parser.c  # Command and redirection parsing
│   │   ├── syntax_validator.c # Input validation
│   │   ├── expander.c        # Variable and quote expansion
│   │   └── ast_utils.c       # AST memory management
│   ├── execution/            # Command execution engine
│   │   ├── executor.c        # Main execution controller
│   │   ├── pipeline.c        # Pipe setup and management
│   │   ├── process.c         # Process creation and waiting
│   │   ├── redirections.c    # File descriptor management
│   │   └── command_resolver.c # PATH resolution and builtin detection
│   ├── builtins/             # Built-in command implementations
│   │   ├── builtin_echo.c    # echo command
│   │   ├── builtin_cd.c      # cd command
│   │   ├── builtin_pwd.c     # pwd command
│   │   ├── builtin_export.c  # export command
│   │   ├── builtin_unset.c   # unset command
│   │   ├── builtin_env.c     # env command
│   │   └── builtin_exit.c    # exit command
│   ├── signals/              # Signal handling
│   │   └── signal_handler.c  # SIGINT, SIGQUIT management
│   └── utils/                # Utility functions
│       ├── string_utils.c    # String manipulation helpers
│       ├── array_utils.c     # Array operations
│       ├── env_utils.c       # Environment variable management
│       ├── error_utils.c     # Error reporting
│       └── memory_utils.c    # Memory cleanup functions
```

## Architecture Overview

### 1. Input Processing Flow

```
User Input → Tokenizer → Parser → AST → Executor → Output
```

### 2. Core Data Structures

- **`t_token`**: Individual lexical elements (words, operators)
- **`t_cmd`**: Single command with arguments and redirections
- **`t_pipeline`**: Sequence of commands connected by pipes
- **`t_ast_node`**: Tree node representing command structure
- **`t_shell`**: Global shell state and environment

### 3. Parsing Strategy

The parser implements **recursive descent** with proper operator precedence:

1. **Logical OR (`||`)** - Lowest precedence, left-associative
2. **Logical AND (`&&`)** - Medium precedence, left-associative  
3. **Pipelines (`|`)** - Highest precedence, left-associative
4. **Parentheses (`()`)** - Grouping, highest priority

### 4. Execution Strategy

Commands execute based on their AST node type:

- **Pipeline**: Set up pipes, fork processes, execute in parallel
- **AND/OR**: Execute left side, check exit code, conditionally execute right
- **Subshell**: Fork and execute in isolated environment

## Development Phases

### Phase 1: Parsing Foundation ✅
- [x] Basic file structure
- [ ] Lexer implementation (tokenization)
- [ ] Syntax validation
- [ ] Simple command parsing
- [ ] Basic AST construction

### Phase 2: Core Execution
- [ ] Command resolution (PATH lookup)
- [ ] Process creation and management
- [ ] Basic redirection handling
- [ ] Simple pipeline execution

### Phase 3: Advanced Features
- [ ] Variable expansion
- [ ] Quote handling
- [ ] Heredoc implementation
- [ ] Signal handling
- [ ] Built-in commands

### Phase 4: Robustness
- [ ] Error handling and reporting
- [ ] Memory leak prevention
- [ ] Edge case handling
- [ ] Comprehensive testing

## Key Algorithms

### Tokenization Process
1. Skip whitespace
2. Identify token type (operator/word/quote)
3. Extract token value
4. Handle special cases (escaped chars, variables)
5. Create token structure and link to list

### AST Construction
1. Parse expressions with operator precedence
2. Handle left-associativity for same-precedence operators
3. Build tree structure representing execution order
4. Validate syntax during parsing

### Pipeline Execution
1. Create pipes for inter-process communication
2. Fork child processes for each command
3. Set up file descriptors (stdin/stdout redirection)
4. Execute commands simultaneously
5. Wait for all processes and collect exit codes

## Testing Strategy

```bash
# Build and test
make test

# Memory leak checking
make valgrind

# Debug build with sanitizers
make debug

# Norminette compliance
make norm
```

## Implementation Tips

1. **Start with lexer**: Get tokenization working first
2. **Test incrementally**: Verify each component before moving on
3. **Handle memory carefully**: Every malloc needs corresponding free
4. **Use valgrind early**: Catch memory issues during development
5. **Follow 42 norms**: Use norminette to check style compliance

## Common Pitfalls to Avoid

- Memory leaks in error paths
- Improper signal handling
- File descriptor leaks
- Incorrect pipe setup
- Zombie processes
- Buffer overflows in string handling

## Resources

- Bash manual for behavior reference
- UNIX process management documentation
- Signal handling best practices
- Memory management guidelines
