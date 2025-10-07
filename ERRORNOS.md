---
title: "Errornos"
author: "Claude sonnet 4.5"
created: "7 Oct 2025 - 4:48 AM"
---

# Minishell Exit Status Codes Reference

## Standard Exit Codes (Bash Conventions)

### Success
| Code | Name | Description | When to Use |
|------|------|-------------|-------------|
| `0` | `EXIT_SUCCESS` | Command completed successfully | Any successful operation |

---

## General Errors (1-2)

### Exit Code 1 - General Errors
| Code | Name | Description | When to Use |
|------|------|-------------|-------------|
| `1` | `EXIT_GENERAL_ERROR` | General catchall error | Default error for most failures |

**Common uses for exit code 1:**
- File not found for input redirection: `cat < nonexistent`
- Permission denied: `cat < /root/file`
- Directory errors: `cat < /tmp` (is a directory)
- Builtin command failures: `cd /nonexistent`, `export 123VAR=value`
- Command execution failures (non-specific)
- Failed to open/create file for redirection
- Invalid arguments to builtins

### Exit Code 2 - Syntax Errors
| Code | Name | Description | When to Use |
|------|------|-------------|-------------|
| `2` | `EXIT_SYNTAX_ERROR` | Misuse of shell builtins or syntax error | All parsing and syntax errors |

**When to return exit code 2:**
- Missing filename after redirection: `echo test >`
- Missing filename after input redirect: `cat <`
- Missing heredoc delimiter: `cat <<`
- Unexpected token: `echo |`, `| cat`
- Invalid redirection operators: `echo >>>file`
- Unclosed quotes: `echo "hello`
- Invalid pipe syntax: `echo | | cat`
- Multiple operators together: `echo >> > file`
- Misuse of shell syntax

---

## Command Execution Errors (126-127)

### Exit Code 126 - Command Not Executable
| Code | Name | Description | When to Use |
|------|------|-------------|-------------|
| `126` | `EXIT_CMD_NOT_EXECUTABLE` | Command found but not executable | File exists but lacks execute permission |

**Examples:**
```bash
./script.txt          # File exists but no execute permission
/bin/ls               # If ls exists but not executable (rare)
```

### Exit Code 127 - Command Not Found
| Code | Name | Description | When to Use |
|------|------|-------------|-------------|
| `127` | `EXIT_CMD_NOT_FOUND` | Command not found in PATH | Command doesn't exist in PATH or as file |

**Examples:**
```bash
nonexistentcmd        # Command doesn't exist
./nonexistent.sh      # File doesn't exist
/path/to/nothing      # Path doesn't exist
```

---

## Signal-Related Exit Codes (128+)

When a process is terminated by a signal, the exit code is `128 + signal_number`

### Common Signal Exit Codes
| Code | Signal | Name | Description | When to Use |
|------|--------|------|-------------|-------------|
| `130` | `SIGINT` (2) | `EXIT_CTRL_C` | Terminated by Ctrl+C | User pressed Ctrl+C |
| `131` | `SIGQUIT` (3) | `EXIT_CTRL_BACKSLASH` | Terminated by Ctrl+\ | User pressed Ctrl+\ |
| `143` | `SIGTERM` (15) | - | Terminated by SIGTERM | Process received SIGTERM |

**Formula:** `exit_code = 128 + signal_number`

**Examples:**
```bash
# User presses Ctrl+C during cat
cat                   # Exit: 130 (128 + 2)

# User presses Ctrl+\ during sleep
sleep 100            # Exit: 131 (128 + 3)
```

### Exit Code 255 - Out of Range
| Code | Name | Description | When to Use |
|------|------|-------------|-------------|
| `255` | `EXIT_OUT_OF_RANGE` | Exit status out of range | When exit() called with value > 255 |

**Note:** Exit codes are modulo 256, so `exit(256)` becomes `0`, `exit(257)` becomes `1`, etc.

---

## Parsing Error Details

These help categorize what type of parsing error occurred internally:

### Syntax Errors (Return 2)
| Type | Description | Example |
|------|-------------|---------|
| Unexpected token | Token appears in wrong context | `\| cat`, `echo \|\|` |
| Missing filename | Redirect without target file | `echo >`, `cat <` |
| Missing delimiter | Heredoc without delimiter | `cat <<` |
| Invalid operator | Malformed redirect operators | `echo >>>file` |

### Lexical Errors (Return 1 or 2)
| Type | Description | Example | Exit Code |
|------|-------------|---------|-----------|
| Unclosed quote | Quote never closed | `echo "hello` | 2 |
| Invalid token | Unrecognized token | Usually caught as unexpected | 2 |

---

## Redirection Error Details

All redirection errors typically return exit code **1**:

| Error Type | Description | Example |
|------------|-------------|---------|
| No such file | Input file doesn't exist | `cat < nonexistent` |
| Permission denied | Cannot read/write file | `cat < /root/file` |
| Is a directory | Target is a directory | `cat < /tmp` |
| Failed to open | Generic open failure | Various reasons |
| Failed to create | Cannot create output file | Permission issues |

---

## Builtin-Specific Exit Codes

### `cd` Command
| Exit Code | Error | Example |
|-----------|-------|---------|
| `0` | Success | `cd /tmp` |
| `1` | Directory doesn't exist | `cd /nonexistent` |
| `1` | Not a directory | `cd /etc/passwd` |
| `1` | Permission denied | `cd /root` |
| `1` | HOME not set | `cd` (when HOME unset) |
| `1` | OLDPWD not set | `cd -` (when OLDPWD unset) |

### `export` Command
| Exit Code | Error | Example |
|-----------|-------|---------|
| `0` | Success | `export VAR=value` |
| `1` | Invalid identifier | `export 123VAR=value` |
| `1` | Invalid identifier | `export VAR-NAME=value` |

### `unset` Command
| Exit Code | Error | Example |
|-----------|-------|---------|
| `0` | Success | `unset VAR` |
| `1` | Invalid identifier | `unset 123VAR` |

### `exit` Command
| Exit Code | Error | Example |
|-----------|-------|---------|
| `0` | Success (default) | `exit` |
| `N` | Specified value | `exit 42` returns 42 |
| `2` | Too many arguments | `exit 1 2 3` |
| `2` | Non-numeric argument | `exit abc` (bash behavior) |

### `echo` Command
| Exit Code | Error | Example |
|-----------|-------|---------|
| `0` | Always success | `echo hello` |
| `1` | Write error | `echo test` (if stdout write fails) |

### `pwd` Command
| Exit Code | Error | Example |
|-----------|-------|---------|
| `0` | Success | `pwd` |
| `1` | Cannot determine pwd | Current directory deleted |

### `env` Command
| Exit Code | Error | Example |
|-----------|-------|---------|
| `0` | Success | `env` |

---

## Summary Table - When to Use Each Code

| Exit Code | Primary Use Cases |
|-----------|------------------|
| `0` | Success, command completed normally |
| `1` | File errors, permission errors, builtin failures, general errors |
| `2` | Syntax errors, parsing errors, misuse of shell constructs |
| `126` | Command exists but is not executable |
| `127` | Command not found |
| `130` | Interrupted by Ctrl+C (SIGINT) |
| `131` | Interrupted by Ctrl+\ (SIGQUIT) |
| `255` | Exit code overflow (> 255) |

---

## Testing Exit Codes in Bash

To verify any exit code in bash:
```bash
# Run command
your_command_here

# Check exit status
echo $?
```

**Examples:**
```bash
echo test > /root/cant_write    # Check: echo $? → 1
cat < nonexistent               # Check: echo $? → 1
echo test >                      # Check: echo $? → 2
nonexistent_cmd                 # Check: echo $? → 127
./no_execute_permission         # Check: echo $? → 126
```

---

## Header File Definition Example

```c
#define EXIT_SUCCESS                0
#define EXIT_GENERAL_ERROR          1
#define EXIT_SYNTAX_ERROR           2
#define EXIT_CMD_NOT_EXECUTABLE     126
#define EXIT_CMD_NOT_FOUND          127
#define EXIT_SIGNAL_BASE            128
#define EXIT_CTRL_C                 130
#define EXIT_CTRL_BACKSLASH         131
#define EXIT_OUT_OF_RANGE           255
```
