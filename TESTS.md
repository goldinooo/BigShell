---
title: "Minishell tests"
author: "Claude sonnet 4.5"
created: "7 Oct 2025 - 4:43 AM"
---

# Minishell Parser Test Cases - Commands & Redirections

## Basic Command Parsing

### Test 1: Simple command
```bash
echo hello
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["hello"]`

### Test 2: Command with multiple arguments
```bash
ls -la /tmp /home
```
**Expected Exit Status:** `0` (if directories exist)
**Parser Should Extract:** Command: `ls`, Args: `["-la", "/tmp", "/home"]`

### Test 3: Command with no arguments
```bash
pwd
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `pwd`, Args: `[]`

---

## Basic Redirections

### Test 4: Output redirection
```bash
echo hello > outfile
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["hello"]`, Redirections: `[{type: OUT, file: "outfile"}]`

### Test 5: Input redirection
```bash
cat < infile
```
**Expected Exit Status:** `0` (if infile exists), `1` (if not)
**Parser Should Extract:** Command: `cat`, Args: `[]`, Redirections: `[{type: IN, file: "infile"}]`

### Test 6: Append redirection
```bash
echo world >> outfile
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["world"]`, Redirections: `[{type: APPEND, file: "outfile"}]`

### Test 7: Heredoc
```bash
cat << EOF
hello
world
EOF
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `cat`, Args: `[]`, Redirections: `[{type: HEREDOC, delimiter: "EOF"}]`

---

## Multiple Redirections

### Test 8: Multiple output redirections (last one wins)
```bash
echo test > file1 > file2 > file3
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["test"]`, Redirections: `[{type: OUT, file: "file1"}, {type: OUT, file: "file2"}, {type: OUT, file: "file3"}]`
**Note:** Only file3 should contain "test"

### Test 9: Input and output redirection
```bash
cat < infile > outfile
```
**Expected Exit Status:** `0` (if infile exists)
**Parser Should Extract:** Command: `cat`, Args: `[]`, Redirections: `[{type: IN, file: "infile"}, {type: OUT, file: "outfile"}]`

### Test 10: Multiple input redirections (last one wins)
```bash
cat < file1 < file2 < file3
```
**Expected Exit Status:** `0` (if file3 exists)
**Parser Should Extract:** Command: `cat`, Args: `[]`, Redirections: `[{type: IN, file: "file1"}, {type: IN, file: "file2"}, {type: IN, file: "file3"}]`

### Test 11: Mixed redirections
```bash
cat < input.txt > output.txt >> append.txt
```
**Expected Exit Status:** `0` (if input.txt exists)
**Parser Should Extract:** Command: `cat`, Args: `[]`, Redirections: `[{type: IN, file: "input.txt"}, {type: OUT, file: "output.txt"}, {type: APPEND, file: "append.txt"}]`

---

## Redirections with Arguments

### Test 12: Redirections interspersed with arguments
```bash
echo hello > out1 world > out2 test
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["hello", "world", "test"]`, Redirections: `[{type: OUT, file: "out1"}, {type: OUT, file: "out2"}]`

### Test 13: Redirection before command
```bash
< input.txt cat
```
**Expected Exit Status:** `0` (if input.txt exists)
**Parser Should Extract:** Command: `cat`, Args: `[]`, Redirections: `[{type: IN, file: "input.txt"}]`

### Test 14: Redirection in the middle
```bash
echo hello > outfile world
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["hello", "world"]`, Redirections: `[{type: OUT, file: "outfile"}]`

### Test 15: Multiple redirections scattered
```bash
> out1 echo < in1 test > out2 message < in2
```
**Expected Exit Status:** `0` (if in2 exists)
**Parser Should Extract:** Command: `echo`, Args: `["test", "message"]`, Redirections: `[{type: OUT, file: "out1"}, {type: IN, file: "in1"}, {type: OUT, file: "out2"}, {type: IN, file: "in2"}]`

---

## Edge Cases with Spaces

### Test 16: No space after redirection operator
```bash
echo hello>outfile
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["hello"]`, Redirections: `[{type: OUT, file: "outfile"}]`

### Test 17: No space before redirection operator
```bash
echo hello> outfile
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["hello"]`, Redirections: `[{type: OUT, file: "outfile"}]`

### Test 18: Multiple spaces around redirection
```bash
echo hello    >     outfile
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["hello"]`, Redirections: `[{type: OUT, file: "outfile"}]`

### Test 19: Tab characters
```bash
echo hello	>	outfile
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["hello"]`, Redirections: `[{type: OUT, file: "outfile"}]`

---

## Quoted Filenames

### Test 20: Single quoted filename
```bash
echo test > 'output file.txt'
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["test"]`, Redirections: `[{type: OUT, file: "output file.txt"}]`

### Test 21: Double quoted filename
```bash
echo test > "output file.txt"
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["test"]`, Redirections: `[{type: OUT, file: "output file.txt"}]`

### Test 22: Filename with special characters in quotes
```bash
echo test > "file$name.txt"
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["test"]`, Redirections: `[{type: OUT, file: "file$name.txt"}]` (or expanded if $name exists)

### Test 23: Empty quoted filename
```bash
echo test > ""
```
**Expected Exit Status:** `1`
**Parser Should Extract:** Should detect ambiguous redirect or empty filename error

### Test 24: Mixed quotes in filename
```bash
echo test > "file'name'.txt"
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["test"]`, Redirections: `[{type: OUT, file: "file'name'.txt"}]`

---

## Heredoc Edge Cases

### Test 25: Heredoc with quoted delimiter
```bash
cat << "EOF"
test $HOME
EOF
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `cat`, Redirections: `[{type: HEREDOC, delimiter: "EOF", quoted: true}]`
**Note:** Variables should NOT be expanded

### Test 26: Heredoc with single quoted delimiter
```bash
cat << 'EOF'
test $HOME
EOF
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `cat`, Redirections: `[{type: HEREDOC, delimiter: "EOF", quoted: true}]`

### Test 27: Heredoc delimiter with no spaces
```bash
cat <<EOF
test
EOF
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `cat`, Redirections: `[{type: HEREDOC, delimiter: "EOF"}]`

### Test 28: Multiple heredocs
```bash
cat << EOF1 << EOF2
first
EOF1
second
EOF2
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `cat`, Redirections: `[{type: HEREDOC, delimiter: "EOF1"}, {type: HEREDOC, delimiter: "EOF2"}]`

---

## Error Cases

### Test 29: Missing filename after redirection
```bash
echo test >
```
**Expected Exit Status:** `2` (syntax error)
**Parser Should Extract:** Syntax error - missing filename

### Test 30: Missing filename after input redirection
```bash
cat <
```
**Expected Exit Status:** `2`
**Parser Should Extract:** Syntax error - missing filename

### Test 31: Missing heredoc delimiter
```bash
cat <<
```
**Expected Exit Status:** `2`
**Parser Should Extract:** Syntax error - missing delimiter

### Test 32: Only redirections, no command
```bash
> outfile
```
**Expected Exit Status:** `0` (creates empty file in bash)
**Parser Should Extract:** Should handle as valid (implicit null command) or error depending on implementation

### Test 33: Multiple redirection operators together
```bash
echo test >> > file
```
**Expected Exit Status:** `2`
**Parser Should Extract:** Syntax error

### Test 34: Invalid redirection operator
```bash
echo test >>> file
```
**Expected Exit Status:** `2`
**Parser Should Extract:** Syntax error or treat third `>` as argument

---

## Complex Scenarios

### Test 35: Long command with many redirections
```bash
echo arg1 > file1 arg2 < input arg3 >> file2 arg4 > file3 arg5
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["arg1", "arg2", "arg3", "arg4", "arg5"]`, Redirections in order

### Test 36: Redirection to /dev/null
```bash
echo test > /dev/null
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `echo`, Args: `["test"]`, Redirections: `[{type: OUT, file: "/dev/null"}]`

### Test 37: Redirection from /dev/null
```bash
cat < /dev/null
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `cat`, Args: `[]`, Redirections: `[{type: IN, file: "/dev/null"}]`

### Test 38: Command with path and redirections
```bash
/bin/echo hello > output
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `/bin/echo`, Args: `["hello"]`, Redirections: `[{type: OUT, file: "output"}]`

### Test 39: Builtin with redirections
```bash
cd /tmp > output
```
**Expected Exit Status:** `0`
**Parser Should Extract:** Command: `cd`, Args: `["/tmp"]`, Redirections: `[{type: OUT, file: "output"}]`

### Test 40: Empty command line with just spaces
```bash

```
**Expected Exit Status:** `0`
**Parser Should Extract:** No command (should be ignored)

---

## Testing Notes

1. **Order matters:** Parser should preserve the order of redirections as they appear
2. **Last wins:** For conflicting redirections (multiple `>` or `<`), the last one takes effect
3. **File creation:** Output redirections should create files even if command fails
4. **Quotes:** Quotes around filenames should be removed but preserved for special characters
5. **Whitespace:** Parser must handle arbitrary whitespace correctly
6. **Syntax errors:** Should be detected during parsing, not execution

## How to Test

For each test:
1. Run in bash and note the exit status: `echo $?`
2. Run in your minishell
3. Compare exit statuses
4. Verify parser extracted correct command, arguments, and redirections
5. Check file contents where applicable
